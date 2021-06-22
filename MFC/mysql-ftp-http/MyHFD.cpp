// MyHFD.cpp: implementation of the CMyHFD class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展

#include "MyHFD.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyHFD::CMyHFD()
{

}

CMyHFD::~CMyHFD()
{

}

typedef CMyHFD* (NewMyHFDInterface)(CWnd*);
typedef void (DelMyHFDInterface)(CMyHFD*);

HINSTANCE g_hMyHFDInstance=NULL;
NewMyHFDInterface* g_pNewMyHFD=NULL;
DelMyHFDInterface* g_pDelMyHFD=NULL;
bool LoadMyHFD(const char*pstrFile,unsigned short nVer)
{
	ReleaseMyHFD();
	
	g_hMyHFDInstance = ::LoadLibrary(pstrFile);
	if (g_hMyHFDInstance)
	{
		typedef unsigned short (GetVerInterface)();
		GetVerInterface* pGetVer=NULL;
		pGetVer = (GetVerInterface*)GetProcAddress(g_hMyHFDInstance, "GetVerInterface");
		if (pGetVer && pGetVer()>=nVer)
		{
			g_pNewMyHFD=(NewMyHFDInterface*)GetProcAddress(g_hMyHFDInstance, "NewMyHFDInterface");;
			g_pDelMyHFD=(DelMyHFDInterface*)GetProcAddress(g_hMyHFDInstance, "DelMyHFDInterface");
			return true;
		}
		ReleaseMyHFD();
	}
	return false;
}
CMyHFD*	NewMyHFD(CWnd * pWnd)
{	
	if (g_hMyHFDInstance&&g_pNewMyHFD)
		return g_pNewMyHFD(pWnd);
	return NULL;
}
void	DelMyHFD(CMyHFD* pMyHFD)
{
	
	if (g_hMyHFDInstance&&g_pDelMyHFD)
		g_pDelMyHFD(pMyHFD);
}
void ReleaseMyHFD()
{
	if (g_hMyHFDInstance)
		::FreeLibrary(g_hMyHFDInstance);
	g_hMyHFDInstance=NULL;
	g_pNewMyHFD=NULL;
	g_pDelMyHFD=NULL;
}
