// MyDB.h: interface for the CMyDB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYDB_H__308387B2_48E2_4DE5_AB0D_D2502AA52E26__INCLUDED_)
#define AFX_MYDB_H__308387B2_48E2_4DE5_AB0D_D2502AA52E26__INCLUDED_

#pragma pack(push,1)
#ifndef  DataBase
#define DataBase
struct Data_Param			//���ݿ��������
{
	char *db_name;			//���ݿ���
	char *tab_name;			//����
	char *col_name;			//����
	char *select_exp;		//ѡ����ʽ
	char *where_def;		//ѡ���޶�����
	char *insert_val;		//����ֵ
	char *set_exp;			//�������ݿ����ݵı��ʽ
};
struct Database_Param			//���ݿ����
{
	const char *host;					//������
	const char *user;					//�û���
	const char *password;				//����
	const char *db;					//���ݿ���
	unsigned int port;			//�˿ڣ�һ��Ϊ0
	const char *unix_socket;			//�׽��֣�һ��ΪNULL
	unsigned int client_flag;	//һ��Ϊ0
};
#endif
#pragma pack(pop,1)

class CMyDB  
{
public:
	CMyDB();
	virtual ~CMyDB();
	virtual BOOL IsConnecting(){return 0;}					//�Ƿ񻹴���������
	virtual BOOL UnLockTable(){return 0;}					//����
	virtual BOOL LockTable(char* TableName,char* PRIORITY){return 0;} //����
	virtual BOOL Reload(){return 0;}						//���µ�½������ʱ���ش�����Ϣ
	virtual const char* GetState(){return "";}				//������״̬
	virtual const char* GetServerInfo(){return "";}			//��������Ϣ
	virtual int GetProtocolInfo(){return 0;}				//Э����Ϣ
	virtual const char* GetHostInfo(){return "";}			//������Ϣ
	virtual const char* GetClientInfo(){return "";}			//�ͻ�����Ϣ
	virtual char* GetFieldName(int nFieldNum){return "";}	//�ֶ���
	//virtual BOOL IsEnd(){return 0;}						//�Ƿ����
	//int DropDB(char *db);									//ɾ�����ݿ�,���ش�����Ϣ
	virtual void SeekData(int offset){}						//����ָ������
	//int CreateDB(char *db);								//�������ݿ⣬���ش�����Ϣ
	virtual void FreeRecord(){}								//�ͷŽ����
	virtual unsigned int GetFieldNum(){return 0;}			//�õ��ֶ���
	virtual BOOL ConnectDB(Database_Param *p){return 0;}	//�������ݿ�
	virtual void Disconnect(){}								//�Ͽ����ݿ�����
	virtual int GetRecord(){return 0;}						//�õ������һ����¼��
	virtual long GetRowNum(){return 0;}						//�õ���¼��
	virtual BOOL SelectDB(Data_Param *para){return 0;}		//ѡ�����ݿ�
	virtual BOOL UpdateRecord(Data_Param *para){return 0;}	//���¼�¼
	virtual BOOL UpdateRecord(Data_Param *para,char* cpdata,int nLen){return 0;}
	virtual BOOL UpdateRecord(char* cpQuery,char* cpdata,int nLen){return 0;}
															//ֻ�ܸ���һ����¼�����һ���ֶεĶ���������
	virtual BOOL SelectRecord(Data_Param *para){return 0;}	//ѡ���¼
	virtual BOOL InsertRecord(Data_Param *para){return 0;}	//�����¼
	virtual BOOL DelRecord(Data_Param *para){return 0;}		//ɾ����¼
	virtual BOOL SelectAll(Data_Param *para){return 0;}		//ѡ�����м�¼
	virtual const char * OutErrors(){return "";}			//���������Ϣ
	virtual char* GetFieldValue(char* cpName,int* npLen=NULL){return "";}	
															//��ȡ�����ֶε�ֵ,�������ݼ������ݳ���
	virtual BOOL Query(char* cpQuery){return 0;}			//��ѯ���---�޼�¼��
	virtual BOOL Exec(char* cpQuery){return 0;}				//ִ�����---�м�¼��
	
};
//����
bool	LoadMyDB(const char*pstrFile="wbMySQL.dll",unsigned short nVer=0x1007);
CMyDB*	NewMyDB();
void	DelMyDB(CMyDB* pMyDB);
void	ReleaseMyDB();
#endif // !defined(AFX_MYDB_H__308387B2_48E2_4DE5_AB0D_D2502AA52E26__INCLUDED_)
