#include "stdafx.h"

#include "Shell.h"

Shell::Shell()
{
}

void Shell::runAsAdmin(const TCHAR *pathToFile, const TCHAR *parameters)
{
  SHELLEXECUTEINFO sei;

  ZeroMemory(&sei, sizeof(sei));

  sei.cbSize = sizeof(SHELLEXECUTEINFOW);
  sei.hwnd = 0;
  sei.fMask = SEE_MASK_FLAG_NO_UI | SEE_MASK_NOCLOSEPROCESS;
  sei.lpVerb = _T("runas");
  sei.lpFile = pathToFile;
  sei.lpParameters = parameters;
  sei.nShow = SW_SHOWNORMAL;

  if (ShellExecuteEx(&sei) == FALSE) {
    ASSERT(FALSE);
  }

  WaitForSingleObject(sei.hProcess, INFINITE);

  CloseHandle(sei.hProcess);
}

void Shell::open(const TCHAR *file, const TCHAR *parameters, const TCHAR *workDirectory)
{
  int ret = (int)ShellExecute(0, _T("open"), file, parameters, workDirectory, SW_SHOW);

  if (ret <= 32) {
    ASSERT(FALSE);
  }
}
DWORD Shell::WaitForObject(DWORD dwMill,bool * object)
{
	if (!object)
	{
		return -1;
	}

	DWORD dwStart = GetTickCount();

	while((GetTickCount()-dwStart)<dwMill)
	{
		MSG message;
		while(::PeekMessage(&message,NULL,0,0,PM_REMOVE))
		{
			::TranslateMessage(&message);
			::DispatchMessage(&message);
		}

		if ((*object)==true)
		{
			return 1;
		}

		Sleep(10);
	}

	return 0;
}


BOOL Shell::XZSHOpenFolderAndSelectItems(ITEMIDLIST* pidlFolder) {
	HRESULT(WINAPI * gpfSHOpenFolderAndSelectItems)(LPCITEMIDLIST * pidlFolder, UINT   cidl, LPCITEMIDLIST * apidl, DWORD   dwFlags); 
	HINSTANCE ghShell32; 
	ghShell32 = LoadLibrary(_T("Shell32.DLL")); 
	if(ghShell32 == NULL) {
		return   FALSE; 
	}
	gpfSHOpenFolderAndSelectItems = (HRESULT(WINAPI *)(LPCITEMIDLIST *, UINT, LPCITEMIDLIST *, DWORD)) 
		GetProcAddress(ghShell32, "SHOpenFolderAndSelectItems"); 
	if(gpfSHOpenFolderAndSelectItems != NULL) {
		if(SUCCEEDED(gpfSHOpenFolderAndSelectItems((LPCITEMIDLIST *) pidlFolder, 0, (LPCITEMIDLIST *) NULL, 0))) {
			FreeLibrary(ghShell32); 
			return   TRUE;
		} 
		FreeLibrary(ghShell32); 
		return   FALSE;
	} 
	FreeLibrary(ghShell32); 
	return   FALSE;
} 

void Shell::FindTarget(LPCTSTR    str) {
	HRESULT hres;   
	IShellLink* psl;   
	ITEMIDLIST* pidl; 
	IPersistFile* ppf;   
	CoInitialize(NULL); 
	hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID *) &psl);   
	if(SUCCEEDED(hres)) {
		psl-> SetPath(str); 
		psl-> GetIDList(&pidl); 
		hres = psl-> QueryInterface(IID_IPersistFile, (void * *) &ppf);   
		if(SUCCEEDED(hres)) {
			WCHAR wsz[MAX_PATH];
			MultiByteToWideChar(CP_ACP, 0, str, -1, wsz, MAX_PATH);   
			//   Load   the   shortcut.   
			hres = ppf-> Load(wsz, STGM_READ);   
			if(SUCCEEDED(hres)) {
				psl-> GetIDList(&pidl);
			} 
			ppf-> Release();
		} 
		XZSHOpenFolderAndSelectItems(pidl); 
		psl-> Release();
	} 
	CoUninitialize();
}
