#pragma once

#include "XDBOperInterface.h"
#include "XDBSupportDef.h"

/************************************************************************/
// CXDBSQLiteRecordset
/************************************************************************/

class CXDBSQLiteRecordset : public IXDBRecordset
{
	ASCIHELP_STANDARD_UNKNOWN();

public:

	CXDBSQLiteRecordset(sqlite3_stmt *stmt);
	virtual ~CXDBSQLiteRecordset();

	virtual	long	GetFieldCount()const;
	virtual	HRESULT	GetFieldName(int nField, _bstr_t& bstrField)const;

	virtual HRESULT Start();
	virtual HRESULT Next();
	virtual	HRESULT	GetFieldValue(LPCTSTR lpszField, _variant_t& val)const;
	virtual	HRESULT	GetFieldValue(int nField, _variant_t& val, _bstr_t* pField)const;

protected:

	enum XVT{XVTEmpty, XVTInt, XVTDouble, XVTString, XVTBlob, XVTDate, XVTGuid};

	struct SFieldInfo
	{
		LPCWSTR		wcsName;
		XVT			vt;
		int			nField;
	};

	CTArray<SFieldInfo>	m_aFiledInfoOrg;	//�ֶ���Ϣ���飬ԭʼ˳��
	CTArray<SFieldInfo>	m_aFiledInfoSort;	//�ֶ���Ϣ���飬���ֶ���������

	static int _FIComp(const void *p1, const void *p2);

	sqlite3_stmt *m_stmt;
};

/************************************************************************/
// CXDBSQLiteRecordsetAdd
/************************************************************************/

class CXDBSQLiteRecordsetAdd : public IXDBRecordsetAdd
{
	ASCIHELP_STANDARD_UNKNOWN();

public:

	CXDBSQLiteRecordsetAdd(sqlite3*	db, LPCTSTR lpszTableName);
	virtual ~CXDBSQLiteRecordsetAdd();

	virtual HRESULT AddNew();	//��ʼ���һ���¼�¼
	virtual HRESULT Update();	//���¼�¼�����ݿ��ţ����Զ��AddNew()�����һ����Update()
	virtual	HRESULT	SetFieldValue(LPCTSTR lpszField, const _variant_t& val);

protected:

	HRESULT	_UpdateRecord();
	
	static int _FIComp(const void *p1, const void *p2);

protected:

	sqlite3*		m_db;
	string			m_strTableName;
	sqlite3_stmt*	m_stmt;

	struct SFieldInfo
	{
		stdstring	strName;
		int			nField;
	};

	CTArray<SFieldInfo>	m_aFiledInfo;	//�ֶ�������

	typedef list<_variant_t>	varlist;
	varlist	m_lValStore;//ֻ����m_stmt��û��׼���õ�ʱ��
};

/************************************************************************/
// CXDBSQLiteConnection
/************************************************************************/

class CXDBSQLiteConnection : public IXDBConnection
{
	ASCIHELP_STANDARD_UNKNOWN();

public:

	CXDBSQLiteConnection();
	virtual ~CXDBSQLiteConnection();

	virtual	DWORD	GetDBType()const	{return XDBTSQLite;}

	virtual HRESULT	Open(LPCTSTR lpszDatabase);
	virtual void	Close();
	virtual	bool	IsOpen()const;
	virtual bool    IsExistTable(LPCTSTR lpszTableName);

	virtual	HRESULT	Excute(LPCTSTR lpszCommand, IXDBRecordset** ppRecdset);
	virtual	HRESULT	AddRecord(LPCTSTR lpszTableName, IXDBRecordsetAdd** ppRecdset);

	virtual	HRESULT	BeginTrans();
	virtual	HRESULT CommitTrans();
	virtual	HRESULT RollbackTrans();

protected:

	sqlite3* m_db;
};