#pragma once
#ifndef _FILE_LOG_H_
#define _FILE_LOG_H_
#include "Util_Export.h"
#include "Log.h"
#include "LocalMutex.h"

class UTIL_API FileLog : public Log
{
public:
  static const int MAX_BACKUP_COUNT = 5;

public:
  FileLog(const TCHAR *pathToLogFile = 0, bool createBackup = true);
  virtual ~FileLog();

  void changeFilename(const TCHAR *pathToLogFile);

  void changeLevel(int level);

  int getLevel();

  static void getBackupFileName(const TCHAR *pathToLogFile, int backupNumber,
                                CString *pathToBackup);

protected:
  virtual void flushLine(int logLevel, const TCHAR *line);

  bool isFileOpened() const;
  void openFile();
  void closeFile();

  static void backupLogFile(const TCHAR *pathToLogFile, int currentBackupIndex = 0);

private:
  HANDLE m_file;
  bool m_createBackup;
  bool m_backupIsCreated;
  CString m_filename;
  int m_logLevel;
  LocalMutex m_fMutex;
  LocalMutex m_llMutex;
};

#endif
