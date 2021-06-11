/******************************************************************
 模块名称：数据库操作类；
 实现功能：提供接口，实现数据的索引，和操作。

 预先操作：
 【1】在主进程的InitInstance()中添加
         if(!AfxOleInit())
        {
         AfxMessageBox("OLE初始化错误");
         return FALSE;
         }


*********************************************************************/
#pragma once

#pragma warning( disable : 4146 )   // unary minus operator applied to unsigned type, result still unsigned.
#pragma warning( disable : 4310 )   // cast truncates constant value.

#include <afxdisp.h>

#import ".\msado60_Backcompat.tlb" rename_namespace("ADOCG") rename("EOF","EndOfFile")

using namespace ADOCG;

//#include <icrsint.h>

struct CADOFieldInfo
{
	char m_strName[30]; 
	short m_nType;
	long m_lSize; 
	long m_lDefinedSize;
	long m_lAttributes;
	short m_nOrdinalPosition;
	BOOL m_bRequired;   
	BOOL m_bAllowZeroLength; 
	long m_lCollatingOrder;  
};

CString IntToStr(int nVal);

CString LongToStr(long lVal);

class CADODatabase
{
public:
	bool Execute(LPCTSTR lpstrExec);
	CADODatabase();	
	~CADODatabase();

	bool Open(LPCTSTR lpstrConnection = _T(""), LPCTSTR lpstrUserID = _T(""), LPCTSTR lpstrPassword = _T(""));
	bool IsOpen();
	void Close();

	DWORD GetRecordCount(_RecordsetPtr m_pRs);
	_ConnectionPtr GetActiveConnection() 
	{
		return m_pConnection;
	};
	long BeginTransaction() 
	{
		return m_pConnection->BeginTrans();
	};
	long CommitTransaction() 
	{
		return m_pConnection->CommitTrans();
	};
	long RollbackTransaction() 
	{
		return m_pConnection->RollbackTrans();
	};
	void SetConnectionString(LPCTSTR lpstrConnection)
	{
		m_strConnection = lpstrConnection;
	};
	CString GetConnectionString()
	{
		return m_strConnection;
	};
	CString GetLastError() 
	{
		return m_strLastError;
	};
protected:
	void dump_com_error(_com_error &e);

protected:
	_ConnectionPtr m_pConnection;
	CString m_strConnection;
	CString m_strLastError;
};

class CADORecordset
{
public:
	enum cadoOpenEnum
	{
		openUnknown = 0,
		openQuery = 1,
		openTable = 2,
		openStoredProc = 3
	};

	enum cadoEditEnum
	{
		dbEditNone = 0,
		dbEditNew = 1,
		dbEdit = 2
	};

	enum cadoPositionEnum
	{
		positionUnknown = -1,
		positionBOF = -2,
		positionEOF = -3
	};

	enum cadoSearchEnum
	{	
		searchForward = 1,
		searchBackward = -1
	};

	enum cadoCursorLocationEnum
	{
		useNone = 1,
		useServer = 2,
		useClient = 3,
		useClientBatch = 3
	};

	enum cadoCursorTypeEnum
	{
		cursorUnspecified = -1,
		cursorForwardOnly = 0,
		cursorKeyset = 1,
		cursorDynamic = 2,
		cursorStatic = 3
	};

	enum cadoLockTypeEnum
	{
		lockUnspecified = -1,
		lockReadOnly = 1,
		lockPessimistic = 2,
		lockOptimistic = 3,
		lockBatchOptimistic = 4
	};

	enum cadoFilterEnum
	{
		filterNone = 0,
		filterPendingRecords = 1,
		filterAffectedRecords = 2,
		filterFetchedRecords = 3,
		filterPredicate = 4,
		filterConflictingRecords = 5
	};
	//////////////////////////////////////////////////////////////////////////
	enum cadoFileTypeEnum
	{
		ADO_FIELD_IMAGE = 0,
		ADO_FIELD_TEXT	= 1
	};
	//////////////////////////////////////////////////////////////////////////
	bool SetFieldValue(int nIndex, CString strValue);
	bool SetFieldValue(LPCTSTR lpFieldName, CString strValue);
	bool SetFieldValue(int nIndex, int nValue);
	bool SetFieldValue(LPCTSTR lpFieldName, int nValue);
	bool SetFieldValue(int nIndex, long lValue);
	bool SetFieldValue(LPCTSTR lpFieldName, long lValue);
	bool SetFieldValue(int nIndex, double dblValue);
	bool SetFieldValue(LPCTSTR lpFieldName, double dblValue);
	bool SetFieldValue(int nIndex, COleDateTime time);
	bool SetFieldValue(LPCTSTR lpFieldName, COleDateTime time);
	bool SetFieldValue(LPCTSTR lpFieldName, BYTE *pBlob, UINT uLen);
	bool SetFieldValue(int nIndex, BYTE *pBlob, UINT uLen);
	//////////////////////////////////////////////////////////////////////////
	bool SetFieldValue(int nIndex, int nFileType, CString strFileName);				//for image/text type
	bool SetFieldValue(LPCTSTR lpFieldName, int nFileType, CString strFileName);
	//////////////////////////////////////////////////////////////////////////
	void CancelUpdate();
	bool Update();
	void Edit();
	bool AddNew();

	bool Find(LPCTSTR lpFind, int nSearchDirection = CADORecordset::searchForward);
	bool FindFirst(LPCTSTR lpFind);
	bool FindNext();

	CADORecordset()
	{

		m_pRecordset = NULL;
		m_pCmd = NULL;
		m_strQuery = _T("");
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		m_pCmd.CreateInstance(__uuidof(Command));

		m_nEditStatus		= CADORecordset::dbEditNone;
		m_nSearchDirection	= CADORecordset::searchForward;
		m_nCursorLocation	= CADORecordset::useNone;
		m_nCursorType		= CADORecordset::cursorUnspecified;
		m_nLockType			= CADORecordset::lockUnspecified;
	}

	CADORecordset(CADODatabase* pAdoDatabase);

	~CADORecordset()
	{
		try { Close(); } catch (...) { }
		try { m_pRecordset.Release(); } catch (...) { }
		try { m_pCmd.Release(); } catch (...) { }

		m_pRecordset = NULL;
		m_pCmd = NULL;

		m_strQuery = _T("");
		m_nEditStatus = dbEditNone;
	}

	CString GetQuery() 
	{return m_strQuery;};
	void SetQuery(LPCSTR strQuery) 
	{m_strQuery = strQuery;};
	//bool RecordBinding(CADORecordBinding &pAdoRecordBinding);
	DWORD GetRecordCount();
	bool IsOpen();
	void Close();
	bool Open(_ConnectionPtr mpdb, LPCTSTR lpstrExec = _T(""), int nOption = CADORecordset::openUnknown);
	bool Open(LPCTSTR lpstrExec = _T(""), int nOption = CADORecordset::openUnknown);
	bool GetFieldValue(LPCTSTR lpFieldName, double& dbValue);
	bool GetFieldValue(int nIndex, double& dbValue);
	bool GetFieldValue(LPCTSTR lpFieldName, long& lValue);
	bool GetFieldValue(int nIndex, long& lValue);
	bool GetFieldValue(LPCTSTR lpFieldName, BYTE& byValue);
	bool GetFieldValue(int nIndex, BYTE& byValue);
	bool GetFieldValue(LPCTSTR lpFieldName, int& nValue);
	bool GetFieldValue(int nIndex, int& nValue);
	bool GetFieldValue(LPCTSTR lpFieldName, CString& strValue);
	bool GetFieldValue(int nIndex, CString& strValue);
	bool GetFieldValue(LPCTSTR lpFieldName, COleDateTime& time);
	bool GetFieldValue(int nIndex, COleDateTime& time);
	bool GetFieldValue(LPCTSTR lpFieldName, CString& strValue,  UINT *puLen);
	//
	bool GetFieldValue(LPCTSTR lpFieldName, char* sValue);
	bool GetFieldValue(int nIndex, char* sValue);
	//////////////////////////////////////////////////////////////////////////
	bool GetFieldValue(int nIndex, HBITMAP &hBitmap, CDC* pDC);				//for image type
	bool GetFieldValue(LPCTSTR lpFieldName, HBITMAP &hBitmap, CDC* pDC);
	bool GetFieldValue(int nIndex, CString *pText);					//for text type
	bool GetFieldValue(LPCTSTR lpFieldName,  CString *pText);
	//////////////////////////////////////////////////////////////////////////
	bool IsFieldNull(LPCTSTR lpFieldName);
	bool IsFieldNull(int nIndex);
	bool IsFieldEmpty(LPCTSTR lpFieldName);
	bool IsFieldEmpty(int nIndex);	

	bool IsField(LPCTSTR lpFieldName);
	//////////////////////////////////////////////////////////////////////////
	bool IsEof()		{return m_pRecordset->EndOfFile == VARIANT_TRUE;};
	bool IsEOF()		{return m_pRecordset->EndOfFile == VARIANT_TRUE;};
	bool IsBof()		{return m_pRecordset->BOF == VARIANT_TRUE;};
	bool IsBOF()		{return m_pRecordset->BOF == VARIANT_TRUE;};
	//////////////////////////////////////////////////////////////////////////
	void MoveFirst() 
	{
		try
		{
			m_pRecordset->MoveFirst();
		}
		catch (...)
		{
		}
	};
	void MoveNext() 		{m_pRecordset->MoveNext();};
	void MovePrevious() 	{m_pRecordset->MovePrevious();};
	void MoveLast() 
	{
		try
		{
			m_pRecordset->MoveLast();
		}
		catch (...)
		{
		}
	};
	long GetAbsolutePage()
	{return m_pRecordset->GetAbsolutePage();};
	void SetAbsolutePage(int nPage)
	{m_pRecordset->PutAbsolutePage((enum PositionEnum)nPage);};
	long GetPageCount()
	{return m_pRecordset->GetPageCount();};
	long GetPageSize()
	{return m_pRecordset->GetPageSize();};
	void SetPageSize(int nSize)
	{m_pRecordset->PutPageSize(nSize);};
	long GetAbsolutePosition()
	{return m_pRecordset->GetAbsolutePosition();};
	void SetAbsolutePosition(int nPosition)
	{m_pRecordset->PutAbsolutePosition((enum PositionEnum)nPosition);};
	bool GetFieldInfo(LPCTSTR lpFieldName, CADOFieldInfo* fldInfo);
	bool GetFieldInfo(int nIndex, CADOFieldInfo* fldInfo);
	bool GetChunk(LPCTSTR lpFieldName, CString& strValue);
	CString GetString(LPCTSTR lpCols, LPCTSTR lpRows, LPCTSTR lpNull, long numRows = 0);
	CString GetLastError() {return m_strLastError;};
	void GetBookmark()
	{m_varBookmark = m_pRecordset->Bookmark;};
	bool SetBookmark();
	bool Delete();

	_RecordsetPtr GetRecordset()
	{return m_pRecordset;};
	_ConnectionPtr GetActiveConnection() 
	{return m_pRecordset->GetActiveConnection();};

	bool Supports(int nCursorOption);
	bool CanAppend();
	bool CanBookmark();
	bool CanResync();
	bool CanUpdate();
	bool Requery();
	bool Resync();

	int GetCursorLocation();
	void SetCursorLocation(int nCursorLocation);

	int GetCursorType();
	void SetCursorType(int nCursorType);

	int GetLockType();
	void SetLockType(int nLockType);

	void SetFilter(CString strFilter);
	void SetFilter(int nFilterType);

	void SetSortOrder(CString strSort);

	bool NextRecordset();

	long GetMaxRecords()
	{return m_pRecordset->GetMaxRecords();};
	void SetMaxRecords(long lMaxRecords)
	{m_pRecordset->PutMaxRecords(lMaxRecords);};

protected:
	_ConnectionPtr m_pConnection;
	int m_nSearchDirection;
	CString m_strFind;
	_variant_t m_varBookFind;
	_variant_t m_varBookmark;
	int m_nEditStatus;
	CString m_strLastError;
	void dump_com_error(_com_error &e);
	_RecordsetPtr m_pRecordset;
	_CommandPtr m_pCmd;
	int m_nCursorLocation;
	int m_nCursorType;
	int m_nLockType;
	CString m_strQuery;
};
