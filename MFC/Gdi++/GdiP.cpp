#include "StdAfx.h"
#include "GdiP.h"

#pragma comment(lib,"gdiplus.lib")


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

ULONG_PTR GdiP::m_mdiplusToken =0;
GdiP::GdiP(void)
{
}


GdiP::~GdiP(void)
{
}

void GdiP::Startup()
{
	//启动GDI+服务
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_mdiplusToken, &gdiplusStartupInput, NULL);
}

void GdiP::Shutdown()
{
	//关闭GDI+服务
	Gdiplus::GdiplusShutdown(m_mdiplusToken);
}

BOOL GdiP::LoadBitmap( Gdiplus::Bitmap ** bm,const CString & strFileName )
{
	WCHAR *filename=new WCHAR[MAX_PATH];
	memset(filename,0,sizeof(WCHAR)*MAX_PATH);
	CharToWChar(filename,strFileName,MAX_PATH);
	Gdiplus::Bitmap* b = Gdiplus::Bitmap::FromFile(filename);
	if (b)
	{
		*bm = b;

		delete[] filename;
		
		return TRUE;
	}
	delete[] filename;
	return FALSE;
}
