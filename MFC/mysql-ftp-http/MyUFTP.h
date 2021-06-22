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
	//��������---�����ṩ�ļ����صĿͻ��˼���
	//pServerName	���ķ�������ַȺ
	//nSize			��������ַȺ����
	//wPort			�������˿�
	//nTime			����ʱ��
	//tClientType	�ͻ�������
	//tAccountType	�ʺ�����
	//spAccount		�ʺ�
	//spPassword	����
	//
	//hNewNotify	���ڻص�����֪ͨ
	virtual BOOL StartActive(const char*	pServerName[],int nSize,WORD wPort,\
		__int64 nTime,BYTE tClientType,BYTE tAccountType,\
		const char* spAccount,const char* spPassword,unsigned long addr=0/*INADDR_ANY*/,HANDLE	hNewNotify=NULL){return FALSE;}
	//////////////////////////////////////////////////////////////////////////
	virtual void NewDataNotify(BYTE	tType,char*	sAccount){}
	//////////////////////////////////////////////////////////////////////////
	//��������---������Ҫ�����ļ��Ŀͻ���
	//spFileName	�����ļ�����
	//tClientType	
	//tAccountType	�ʺ�����
	//spAccount		�ʺ�
	//pServerName	���ķ�������ַ
	//wPort			�˿�
	//pUFTPParam	�Զ������
	//nUFTPParamLen	�Զ����������
	//pstrPath		���ݴ洢·��,��Ҫ�Լ�Ԥ�ȴ�����·��
	//tDownType		���ش�������
	//hNewNotify	֪ͨ��Ϣ
	virtual BOOL StartDownFile(const char* spFileName,\
		BYTE tClientType,BYTE tAccountType,const char* spAccount,\
		const char* pServerName,WORD wPort,\
		char* pUFTPParam=NULL,int nUFTPParamLen=0,const char* pstrPath=NULL,const char* spMac=NULL,\
		unsigned long addr=0/*INADDR_ANY*/,BYTE tDownType=1,HANDLE	hNewNotify=NULL){return FALSE;}
	//����״̬
	//1-����������
	//2-�յ�������֪ͨ,����Ŀͻ�������
	//3-�յ�������֪ͨ,��������
	//4-�յ�������֪ͨ,�ͻ��˲�����
	//5-�յ�������֪ͨ,�ͻ��˲����ڸ������ļ�
	//6-�յ��ͻ���֪ͨ,������������..
	//7-����������
	//8-ȡ���ļ�����
	//9-�����������ؽ���
	//10-�������ݳɹ�
	//11-�����ļ��������쳣
	//12-�����ļ��ɹ�����
	//13-���ص��ļ�CRC32����
	///////////////////
	//�ϴ�״̬
	//0-���ش��ļ�ʧ��
	//1-���ӷ�����
	//2-�����ϴ���
	//3-������������
	//4-�ȴ���Ӧ
	//5-��Ӧ���ݴ���
	//6-�����ϴ�
	//7-�ϴ���
	//8-���������ļ�ʧ��,�Ժ��ϴ�
	//9-�������ļ����ϴ��ļ�һ��,ֹͣ�ϴ�
	//10-�������յ��ļ����ϴ��ļ�һ��,�ϴ��ɹ�
	//11-�������յ��ļ����ϴ��ļ���һ��,�ϴ�ʧ��
	virtual int		GetState(){return 0;}
	//���ض��û�н��յ����ݳ�ʱ���
	//��λ����
	virtual unsigned long GetTimeTimeout(){return 0;}
	//����StartDownFile�е�pUFTPParam��nUFTPParamLen
	virtual	char*	GetUFTPParam(int* nUFTPParamLen=NULL){return NULL;}
	//ȡ�������ļ��ܳ���
	virtual unsigned long	GetFileLengthTotal(){return 0;}
	//ȡ��δ�������ݳ���
	virtual unsigned long	GetLength(){return 0;}
	//ȡ�õ�ǰ�����ٶ�
	virtual float	GetSpeed(){return 0;}
	//ȡ���ܺ�ʱ
	virtual unsigned long	GetTotalDtm(){return 0;}
	//////////////////////////////////////////////////////////////////////////
	//��������---�������ķ�����
	virtual BOOL StartListen(WORD wUdpPort=0,unsigned long addr=0/*INADDR_ANY*/,WORD wTcpPort=0,HANDLE	hNewNotify=NULL){return FALSE;}
	virtual BOOL StartUpFile(const char* spFileName,\
		const char* pServerName,WORD wPort=0,\
		char* pUFTPParam=NULL,int nUFTPParamLen=0,const char* pstrPath=NULL){return FALSE;}
};
//����
bool	LoadMyUFTP(const char*pstrFile="wbUFTP.dll",unsigned short nVer=0x1005);
CMyUFTP*	NewMyUFTPActive();
CMyUFTP*	NewMyUFTPDown();
CMyUFTP*	NewMyUFTPListen();
CMyUFTP*	NewMyTFTPUp();
void	DelMyUFTP(CMyUFTP* pMyUFTP);
void	ReleaseMyUFTP();
