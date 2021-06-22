// MyDB.cpp: implementation of the CMyDB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyDB.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyDB::CMyDB()
{

}

CMyDB::~CMyDB()
{

}

typedef CMyDB* (NewMyDBInterface)();
typedef void (DelMyDBInterface)(CMyDB*);

HINSTANCE g_hMyDBInstance=NULL;
NewMyDBInterface* g_pNewMyDB=NULL;
DelMyDBInterface* g_pDelMyDB=NULL;
bool LoadMyDB(const char*pstrFile,unsigned short nVer)
{
	ReleaseMyDB();
	
	g_hMyDBInstance = ::LoadLibrary(pstrFile);
	if (g_hMyDBInstance)
	{
		typedef unsigned short (GetVerInterface)();
		GetVerInterface* pGetVer=NULL;
		pGetVer = (GetVerInterface*)GetProcAddress(g_hMyDBInstance, "GetVerInterface");
		if (pGetVer && pGetVer()>=nVer)
		{
			g_pNewMyDB=(NewMyDBInterface*)GetProcAddress(g_hMyDBInstance, "NewMyDBInterface");;
			g_pDelMyDB=(DelMyDBInterface*)GetProcAddress(g_hMyDBInstance, "DelMyDBInterface");
			return true;
		}
		else
		{
			OutputDebugString("Load wbMySQL failed\r\n");
		}
		ReleaseMyDB();
	}
	return false;
}
CMyDB*	NewMyDB()
{	
	if (g_hMyDBInstance&&g_pNewMyDB)
		return g_pNewMyDB();
	return NULL;
}
void	DelMyDB(CMyDB* pMyDB)
{
	if (g_hMyDBInstance&&g_pDelMyDB)
		g_pDelMyDB(pMyDB);
}
void ReleaseMyDB()
{
	if (g_hMyDBInstance)
		::FreeLibrary(g_hMyDBInstance);
	g_hMyDBInstance=NULL;
	g_pNewMyDB=NULL;
	g_pDelMyDB=NULL;
}
