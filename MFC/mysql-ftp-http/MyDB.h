// MyDB.h: interface for the CMyDB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYDB_H__308387B2_48E2_4DE5_AB0D_D2502AA52E26__INCLUDED_)
#define AFX_MYDB_H__308387B2_48E2_4DE5_AB0D_D2502AA52E26__INCLUDED_

#pragma pack(push,1)
#ifndef  DataBase
#define DataBase
struct Data_Param			//数据库操作参数
{
	char *db_name;			//数据库名
	char *tab_name;			//表名
	char *col_name;			//列名
	char *select_exp;		//选择表达式
	char *where_def;		//选择限定条件
	char *insert_val;		//插入值
	char *set_exp;			//更新数据库内容的表达式
};
struct Database_Param			//数据库参数
{
	const char *host;					//主机名
	const char *user;					//用户名
	const char *password;				//密码
	const char *db;					//数据库名
	unsigned int port;			//端口，一般为0
	const char *unix_socket;			//套接字，一般为NULL
	unsigned int client_flag;	//一般为0
};
#endif
#pragma pack(pop,1)

class CMyDB  
{
public:
	CMyDB();
	virtual ~CMyDB();
	virtual BOOL IsConnecting(){return 0;}					//是否还处于连接中
	virtual BOOL UnLockTable(){return 0;}					//解锁
	virtual BOOL LockTable(char* TableName,char* PRIORITY){return 0;} //加锁
	virtual BOOL Reload(){return 0;}						//重新登陆，非零时返回错误信息
	virtual const char* GetState(){return "";}				//服务器状态
	virtual const char* GetServerInfo(){return "";}			//服务器信息
	virtual int GetProtocolInfo(){return 0;}				//协议信息
	virtual const char* GetHostInfo(){return "";}			//主机信息
	virtual const char* GetClientInfo(){return "";}			//客户机信息
	virtual char* GetFieldName(int nFieldNum){return "";}	//字段名
	//virtual BOOL IsEnd(){return 0;}						//是否最后
	//int DropDB(char *db);									//删除数据库,返回错误信息
	virtual void SeekData(int offset){}						//查找指定数据
	//int CreateDB(char *db);								//创建数据库，返回错误信息
	virtual void FreeRecord(){}								//释放结果集
	virtual unsigned int GetFieldNum(){return 0;}			//得到字段数
	virtual BOOL ConnectDB(Database_Param *p){return 0;}	//连接数据库
	virtual void Disconnect(){}								//断开数据库链接
	virtual int GetRecord(){return 0;}						//得到结果（一个记录）
	virtual long GetRowNum(){return 0;}						//得到记录数
	virtual BOOL SelectDB(Data_Param *para){return 0;}		//选择数据库
	virtual BOOL UpdateRecord(Data_Param *para){return 0;}	//更新记录
	virtual BOOL UpdateRecord(Data_Param *para,char* cpdata,int nLen){return 0;}
	virtual BOOL UpdateRecord(char* cpQuery,char* cpdata,int nLen){return 0;}
															//只能更新一个记录里面的一个字段的二进制数据
	virtual BOOL SelectRecord(Data_Param *para){return 0;}	//选择记录
	virtual BOOL InsertRecord(Data_Param *para){return 0;}	//插入记录
	virtual BOOL DelRecord(Data_Param *para){return 0;}		//删除记录
	virtual BOOL SelectAll(Data_Param *para){return 0;}		//选择所有记录
	virtual const char * OutErrors(){return "";}			//输出错误信息
	virtual char* GetFieldValue(char* cpName,int* npLen=NULL){return "";}	
															//获取传入字段的值,返回数据及其数据长度
	virtual BOOL Query(char* cpQuery){return 0;}			//查询语句---无记录集
	virtual BOOL Exec(char* cpQuery){return 0;}				//执行语句---有记录集
	
};
//加载
bool	LoadMyDB(const char*pstrFile="wbMySQL.dll",unsigned short nVer=0x1007);
CMyDB*	NewMyDB();
void	DelMyDB(CMyDB* pMyDB);
void	ReleaseMyDB();
#endif // !defined(AFX_MYDB_H__308387B2_48E2_4DE5_AB0D_D2502AA52E26__INCLUDED_)
