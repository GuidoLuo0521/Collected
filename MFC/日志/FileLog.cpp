#include "stdafx.h"
#include "FileLog.h"
#include <Shlwapi.h>

#include "AutoLock.h"

FileLog::FileLog(const TCHAR *pathToLogFile, bool createBackup)
: Log(),
  m_file(INVALID_HANDLE_VALUE),
  m_createBackup(createBackup),
  m_filename(pathToLogFile),
  m_backupIsCreated(false),
  m_logLevel(0)
{
}

FileLog::~FileLog()
{
  if (isFileOpened()) {
    closeFile();
  }
}

void FileLog::changeLevel(int level)
{
  level = max(0, min(level, 9));

  {
    AutoLock l(m_llMutex);

    m_logLevel = level;
  }

  AutoLock l(m_fMutex);

  if (m_filename.IsEmpty()) {
    return;
  }

  if ((level > 0) && (m_createBackup) && (!m_backupIsCreated)) {
    backupLogFile(m_filename);

    m_backupIsCreated = true;
  }

  if ((level == 0) && isFileOpened()) {
    closeFile();
  }

  if ((level > 0) && !isFileOpened()) {
    openFile();
  }
}

int FileLog::getLevel()
{
  AutoLock l(m_llMutex);

  return m_logLevel;
}

void FileLog::changeFilename(const TCHAR *pathToLogFile)
{
  {
    AutoLock l(m_fMutex);

    if (m_filename==CString(pathToLogFile)) {
      return;
    }

    m_filename = pathToLogFile;

    m_backupIsCreated = false;

    closeFile();
  }

  changeLevel(getLevel());
}

void FileLog::backupLogFile(const TCHAR *pathToLogFile, int currentBackupIndex)
{
  if (currentBackupIndex >= MAX_BACKUP_COUNT) {
    return;
  }

  CString backupPath;
  getBackupFileName(pathToLogFile, currentBackupIndex, &backupPath);
  const TCHAR *backupPathString = backupPath;

  if (PathFileExists(backupPathString)) {
    FileLog::backupLogFile(backupPathString, currentBackupIndex + 1);
  }

  bool wasError = MoveFile(pathToLogFile, backupPathString) == 0;
  if (wasError && GetLastError() == ERROR_ALREADY_EXISTS) {
    DeleteFile(backupPathString);
    MoveFile(pathToLogFile, backupPathString);
  }
}

void FileLog::getBackupFileName(const TCHAR *pathToLogFile, int backupNumber,
                                CString *pathToBackup)
{
  CString oldFile(pathToLogFile);

  CString ext;
  CString path;
  CString fileName;

  int pos = oldFile.ReverseFind('\\');
  path = oldFile.Left(pos);

  fileName = oldFile.Right(oldFile.GetLength()-pos);

  int n = fileName.Find('.');
  ext = fileName.Right(fileName.GetLength()-n-1);
  fileName = fileName.Left(n);


  if (ext.IsEmpty()) {
    pathToBackup->Format(_T("%s.%d"), path, backupNumber);
  } else {
   /* path = path.Mid( 0, path.GetLength() - fileName.GetLength() - 1);
    fileName = fileName.Mid( 0, fileName.Find(_T('.')) - 1);*/
    pathToBackup->Format(_T("%s\\%s_%d.%s"), path, fileName, backupNumber, ext);
  }
}

bool FileLog::isFileOpened() const
{
  return m_file != INVALID_HANDLE_VALUE;
}

void FileLog::openFile()
{
  m_file = CreateFile(m_filename,
                      GENERIC_WRITE,
                      FILE_SHARE_READ | FILE_SHARE_WRITE,
                      NULL,
                      OPEN_ALWAYS,
                      FILE_ATTRIBUTE_NORMAL,
                      NULL);

  if (!isFileOpened()) {
    return ;
  }

  SetEndOfFile(m_file);
}

void FileLog::closeFile()
{
  CloseHandle(m_file);

  m_file = INVALID_HANDLE_VALUE;
}

void FileLog::flushLine(int logLevel, const TCHAR *line)
{
  if (logLevel > getLevel() || !isFileOpened()) {
    return;
  }

  DWORD written = 0;

  AutoLock l(m_fMutex);

  WriteFile(m_file, line, _tcslen(line) * sizeof(TCHAR),
            &written, NULL);
  FlushFileBuffers(m_file);
}
