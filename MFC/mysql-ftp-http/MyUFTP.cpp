// MyUFTP.cpp: implementation of the CMyUFTP class.
//
//////////////////////////////////////////////////////////////////////

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展
#include "MyUFTP.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyUFTP::CMyUFTP()
{
	
}

CMyUFTP::~CMyUFTP()
{

}

typedef CMyUFTP* (NewMyUFTPInterfaceActive)();
typedef CMyUFTP* (NewMyUFTPInterfaceDown)();
typedef CMyUFTP* (NewMyTFTPInterfaceUp)();
typedef void (DelMyUFTPInterface)(CMyUFTP*);

HINSTANCE g_hMyUFTPInstance=NULL;
NewMyUFTPInterfaceActive*	g_pNewMyUFTPActive	=NULL;
NewMyUFTPInterfaceDown*		g_pNewMyUFTPDown	=NULL;
NewMyTFTPInterfaceUp*		g_pNewMyTFTPUp		=NULL;
DelMyUFTPInterface*			g_pDelMyUFTP		=NULL;

bool LoadMyUFTP(const char*pstrFile,unsigned short nVer)
{
	ReleaseMyUFTP();

	g_hMyUFTPInstance = ::LoadLibrary(pstrFile);
	if (g_hMyUFTPInstance)
	{
		typedef unsigned short (GetVerInterface)();
		GetVerInterface* pGetVer=NULL;
		pGetVer = (GetVerInterface*)GetProcAddress(g_hMyUFTPInstance, "GetVerInterface");
		if (pGetVer && pGetVer()==nVer)
		{
			g_pNewMyUFTPActive	=(NewMyUFTPInterfaceActive*)GetProcAddress(g_hMyUFTPInstance, "NewMyUFTPInterfaceActive");;
			g_pNewMyUFTPDown	=(NewMyUFTPInterfaceDown*)	GetProcAddress(g_hMyUFTPInstance, "NewMyUFTPInterfaceDown");
			g_pNewMyTFTPUp		=(NewMyTFTPInterfaceUp*)	GetProcAddress(g_hMyUFTPInstance, "NewMyTFTPInterfaceUp");
			g_pDelMyUFTP		=(DelMyUFTPInterface*)		GetProcAddress(g_hMyUFTPInstance, "DelMyUFTPInterface");
			return true;
		}
		else
		{
			OutputDebugString("version mismatch");
		}
		ReleaseMyUFTP();
	}
	return false;
}
CMyUFTP*	NewMyUFTPActive()
{	
	if (g_hMyUFTPInstance && g_pNewMyUFTPActive)
		return g_pNewMyUFTPActive();
	return NULL;
}
CMyUFTP*	NewMyUFTPDown()
{
	if (g_hMyUFTPInstance && g_pNewMyUFTPDown)
		return g_pNewMyUFTPDown();
	return NULL;
}

CMyUFTP*	NewMyTFTPUp()
{	
	if (g_hMyUFTPInstance && g_pNewMyTFTPUp)
		return g_pNewMyTFTPUp();
	return NULL;
}
void	DelMyUFTP(CMyUFTP* pMyUFTP)
{
	if (g_hMyUFTPInstance && g_pDelMyUFTP)
		g_pDelMyUFTP(pMyUFTP);
}
void ReleaseMyUFTP()
{
	if (g_hMyUFTPInstance)
	{
		::FreeLibrary(g_hMyUFTPInstance);
	}
	g_hMyUFTPInstance=NULL;
	g_pNewMyUFTPActive=NULL;
	g_pNewMyUFTPDown=NULL;
	g_pDelMyUFTP=NULL;
}
