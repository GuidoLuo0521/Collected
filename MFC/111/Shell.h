#pragma once
#ifndef _SHELL_H_
#define _SHELL_H_
#include "Util_Export.h"

class UTIL_API Shell
{
public:
  static void runAsAdmin(const TCHAR *pathToFile, const TCHAR *parameters);

  static void open(const TCHAR *file,
                   const TCHAR *parameters,
                   const TCHAR *workDirectory);
  static DWORD WaitForObject(DWORD dwMill,bool * object);


  static void FindTarget(LPCTSTR    str);
private:
	static BOOL XZSHOpenFolderAndSelectItems(ITEMIDLIST* pidlFolder);
  Shell();
};

#endif
