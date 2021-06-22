// MyHFD.h: interface for the CMyHFD class.
//
//////////////////////////////////////////////////////////////////////

#pragma once
#include <stdlib.h>
#include <stdio.h>
#define DOWN_FILE_LENGTH				(WM_USER+0x100)
//通知下载数据进度
//wParam  CMyHFD*
//lParam  当前已经下载数据
//ON_MESSAGE(DOWN_FILE_LENGTH,OnDownFileLength)
//afx_msg LRESULT OnDownFileLength(WPARAM wParam, LPARAM lParam);
class CMyHFD  
{
public:
	CMyHFD();
	virtual ~CMyHFD();
public:	
	//下载状态
	//1-打开链接错误
	//2-链接指向不能下载
	//3-下载异常
	//4-开始下载
	//5-取得续下载长度,正在下载
	//6-下载数据过程结束
	//7-成功下载
	//8-下载异常
	//9-下载文件重命名异常
	virtual int		GetState(){return 0;}
	//返回多久没有接收到数据超时间隔
	//单位毫秒
	virtual unsigned long GetTimeTimeout(){return 0;}
	//下载文件
	//strURL			下载文件链接
	//pHttpParam		参数数据
	//nHttpParamLen		参数数据长度
	//strPath			下载文件保存路径,该路径必须存在或上级路径存在,否则下载保存在当前路径下	
	virtual bool DownFile(const char* pstrURL,char* pHttpParam=NULL,int nHttpParamLen=0,const char* pstrPath=NULL){return 0;}
	//返回DownFile中的pHttpParam和nHttpParamLen
	virtual	char*	GetHttpParam(int* nHttpParamLen=NULL){return NULL;}
	//停止下载
	virtual void StopDown(){}
	//取得下载文件总长度
	virtual unsigned long	GetFileLengthTotal(){return 0;}
	//取得未下载数据长度
	virtual unsigned long	GetLength(){return 0;}
	//取得当前下载速度
	virtual float	GetSpeed(){return 0;}
	//取得总耗时
	virtual unsigned long	GetTotalDtm(){return 0;}
	//取得下载文件总长度
	virtual ULONGLONG	GetLengthTotal(){return 0;}
	//取得未下载数据长度
	virtual ULONGLONG	GetRemainLength(){return 0;}
};
//加载
bool	LoadMyHFD(const char*pstrFile="wbHttpFileDown.dll",unsigned short nVer=0x1001);
CMyHFD*	NewMyHFD(CWnd * pWnd=NULL);
void	DelMyHFD(CMyHFD* pMyHFD);
void	ReleaseMyHFD();