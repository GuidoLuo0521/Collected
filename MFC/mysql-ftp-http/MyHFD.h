// MyHFD.h: interface for the CMyHFD class.
//
//////////////////////////////////////////////////////////////////////

#pragma once
#include <stdlib.h>
#include <stdio.h>
#define DOWN_FILE_LENGTH				(WM_USER+0x100)
//֪ͨ�������ݽ���
//wParam  CMyHFD*
//lParam  ��ǰ�Ѿ���������
//ON_MESSAGE(DOWN_FILE_LENGTH,OnDownFileLength)
//afx_msg LRESULT OnDownFileLength(WPARAM wParam, LPARAM lParam);
class CMyHFD  
{
public:
	CMyHFD();
	virtual ~CMyHFD();
public:	
	//����״̬
	//1-�����Ӵ���
	//2-����ָ��������
	//3-�����쳣
	//4-��ʼ����
	//5-ȡ�������س���,��������
	//6-�������ݹ��̽���
	//7-�ɹ�����
	//8-�����쳣
	//9-�����ļ��������쳣
	virtual int		GetState(){return 0;}
	//���ض��û�н��յ����ݳ�ʱ���
	//��λ����
	virtual unsigned long GetTimeTimeout(){return 0;}
	//�����ļ�
	//strURL			�����ļ�����
	//pHttpParam		��������
	//nHttpParamLen		�������ݳ���
	//strPath			�����ļ�����·��,��·��������ڻ��ϼ�·������,�������ر����ڵ�ǰ·����	
	virtual bool DownFile(const char* pstrURL,char* pHttpParam=NULL,int nHttpParamLen=0,const char* pstrPath=NULL){return 0;}
	//����DownFile�е�pHttpParam��nHttpParamLen
	virtual	char*	GetHttpParam(int* nHttpParamLen=NULL){return NULL;}
	//ֹͣ����
	virtual void StopDown(){}
	//ȡ�������ļ��ܳ���
	virtual unsigned long	GetFileLengthTotal(){return 0;}
	//ȡ��δ�������ݳ���
	virtual unsigned long	GetLength(){return 0;}
	//ȡ�õ�ǰ�����ٶ�
	virtual float	GetSpeed(){return 0;}
	//ȡ���ܺ�ʱ
	virtual unsigned long	GetTotalDtm(){return 0;}
	//ȡ�������ļ��ܳ���
	virtual ULONGLONG	GetLengthTotal(){return 0;}
	//ȡ��δ�������ݳ���
	virtual ULONGLONG	GetRemainLength(){return 0;}
};
//����
bool	LoadMyHFD(const char*pstrFile="wbHttpFileDown.dll",unsigned short nVer=0x1001);
CMyHFD*	NewMyHFD(CWnd * pWnd=NULL);
void	DelMyHFD(CMyHFD* pMyHFD);
void	ReleaseMyHFD();