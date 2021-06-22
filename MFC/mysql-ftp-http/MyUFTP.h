// UFTP.h: interface for the CMyUFTP class.
//
//////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>

#pragma once


class CMyUFTP  
{
public:
	CMyUFTP();
	virtual ~CMyUFTP();
public:
	//////////////////////////////////////////////////////////////////////////
	//启动激活---用于提供文件下载的客户端激活
	//pServerName	中心服务器地址群
	//nSize			服务器地址群数量
	//wPort			服务器端口
	//nTime			开启时间
	//tClientType	客户端类型
	//tAccountType	帐号类型
	//spAccount		帐号
	//spPassword	密码
	//
	//hNewNotify	用于回调的新通知
	virtual BOOL StartActive(const char*	pServerName[],int nSize,WORD wPort,\
		__int64 nTime,BYTE tClientType,BYTE tAccountType,\
		const char* spAccount,const char* spPassword,unsigned long addr=0/*INADDR_ANY*/,HANDLE	hNewNotify=NULL){return FALSE;}
	//////////////////////////////////////////////////////////////////////////
	virtual void NewDataNotify(BYTE	tType,char*	sAccount){}
	//////////////////////////////////////////////////////////////////////////
	//启动下载---用于需要下载文件的客户端
	//spFileName	下载文件名称
	//tClientType	
	//tAccountType	帐号类型
	//spAccount		帐号
	//pServerName	中心服务器地址
	//wPort			端口
	//pUFTPParam	自定义参数
	//nUFTPParamLen	自定义参数长度
	//pstrPath		数据存储路径,需要自己预先创建该路径
	//tDownType		下载传输类型
	//hNewNotify	通知消息
	virtual BOOL StartDownFile(const char* spFileName,\
		BYTE tClientType,BYTE tAccountType,const char* spAccount,\
		const char* pServerName,WORD wPort,\
		char* pUFTPParam=NULL,int nUFTPParamLen=0,const char* pstrPath=NULL,const char* spMac=NULL,\
		unsigned long addr=0/*INADDR_ANY*/,BYTE tDownType=1,HANDLE	hNewNotify=NULL){return FALSE;}
	//下载状态
	//1-请求下载中
	//2-收到服务器通知,请求的客户端在线
	//3-收到服务器通知,可以下载
	//4-收到服务器通知,客户端不在线
	//5-收到服务器通知,客户端不存在该请求文件
	//6-收到客户端通知,可以启动下载..
	//7-数据下载中
	//8-取得文件长度
	//9-接收数据下载结束
	//10-下载数据成功
	//11-下载文件重命名异常
	//12-下载文件成功结束
	//13-下载的文件CRC32错误
	///////////////////
	//上传状态
	//0-本地打开文件失败
	//1-连接服务器
	//2-请求上传中
	//3-服务器不在线
	//4-等待响应
	//5-响应数据错误
	//6-可以上传
	//7-上传中
	//8-服务器打开文件失败,稍后上传
	//9-服务器文件与上传文件一致,停止上传
	//10-服务器收到文件与上传文件一致,上传成功
	//11-服务器收到文件与上传文件不一致,上传失败
	virtual int		GetState(){return 0;}
	//返回多久没有接收到数据超时间隔
	//单位毫秒
	virtual unsigned long GetTimeTimeout(){return 0;}
	//返回StartDownFile中的pUFTPParam和nUFTPParamLen
	virtual	char*	GetUFTPParam(int* nUFTPParamLen=NULL){return NULL;}
	//取得下载文件总长度
	virtual unsigned long	GetFileLengthTotal(){return 0;}
	//取得未下载数据长度
	virtual unsigned long	GetLength(){return 0;}
	//取得当前下载速度
	virtual float	GetSpeed(){return 0;}
	//取得总耗时
	virtual unsigned long	GetTotalDtm(){return 0;}
	//////////////////////////////////////////////////////////////////////////
	//启动监听---用于中心服务器
	virtual BOOL StartListen(WORD wUdpPort=0,unsigned long addr=0/*INADDR_ANY*/,WORD wTcpPort=0,HANDLE	hNewNotify=NULL){return FALSE;}
	virtual BOOL StartUpFile(const char* spFileName,\
		const char* pServerName,WORD wPort=0,\
		char* pUFTPParam=NULL,int nUFTPParamLen=0,const char* pstrPath=NULL){return FALSE;}
};
//加载
bool	LoadMyUFTP(const char*pstrFile="wbUFTP.dll",unsigned short nVer=0x1005);
CMyUFTP*	NewMyUFTPActive();
CMyUFTP*	NewMyUFTPDown();
CMyUFTP*	NewMyUFTPListen();
CMyUFTP*	NewMyTFTPUp();
void	DelMyUFTP(CMyUFTP* pMyUFTP);
void	ReleaseMyUFTP();
