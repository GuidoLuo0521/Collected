#pragma once
#include <GdiPlus.h>
#include "Util_Export.h"


#define CharToWChar(wcText,tcText,maxsize) MultiByteToWideChar(CP_OEMCP,0,tcText,-1,wcText,maxsize)
#define WCharToChar(tcText,wcText,maxsize) WideCharToMultiByte(CP_OEMCP,0,wcText,-1,tcText,maxsize,NULL,FALSE)

class UTIL_API GdiP
{
public:
	GdiP(void);
	~GdiP(void);
public:
	static void		Startup();
	static void		Shutdown();
public:
	static BOOL		LoadBitmap(Gdiplus::Bitmap ** bm,const CString & strFileName);
private:
	static ULONG_PTR m_mdiplusToken ;
};

