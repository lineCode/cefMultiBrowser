#if !defined(__H_SQLITE3EX_DEFINE_INCLUDE_H__)
#define __H_SQLITE3EX_DEFINE_INCLUDE_H__

//////////////////////////////////////////////////////////////////////////
//	Sqlite3ExDefine.h����װ�����ݿ�����������ݱ�����࣬���߿��Լ̳�ʹ��
//
//	CSqlite3Database��Sqlite3���ݿ�������
//		Sqlite3���ݿ��ļ���׺һ��Ϊ.db���ڴ����ݿ��ļ�ʱ������ļ������ڣ�
//		���Զ�������
//
//	CSqlite3DBAccessor��Sqlite3���ݱ���ʻ��࣬ʹ��ʱ��ֱ�ӴӸ���̳м���
//		
//////////////////////////////////////////////////////////////////////////

#include "CppSQLite3.h"

// Sqlite3���ݿ�������
class SQLITE3EX_CLASS CSqlite3Database
{
public:
	CSqlite3Database();
	virtual ~CSqlite3Database();

public:
	// SQLite3�汾
	CString GetSQLiteVersion();

	// �����ݿ�
	BOOL OpenDatabase(CString strDBFile)throw (CppSQLite3Exception&);

	// ��ȡ���ݿ�·��
	CString GetDatabasePath();

	// �ر����ݿ�
	void CloseDatabase();

	// 
	CppSQLite3DB& GetSqlite3DB();

	//
	BOOL IsDBOpen();

	//���ݿ�������ز���
	bool BeginTrans();

	bool CommitTrans();

	bool Rollback();


private:
	CppSQLite3DB	m_sqliteDB;
	BOOL			m_bDBOpen;
	CString			m_strDBFilePath;
};

// Sqlite3���ݿ������
class SQLITE3EX_CLASS CSqlite3DBAccessor
{
public:
	CSqlite3DBAccessor();
	CSqlite3DBAccessor(const CppSQLite3DB& sqlite3DB);
	virtual ~CSqlite3DBAccessor();

	// ��������ж�
	BOOL IsTableExist(CString strTableName);

	// ��ͼ�Ƿ����
	bool IsExistView(CString strViewName);

	// ����Sqlite3DB
	void SetSqlite3DB(const CppSQLite3DB& sqlite3DB);

	// �������ݱ�
	// ����ֵ��TRUE-�ɹ���FALSE-ʧ��
	BOOL CreateTable(CString strTableName, CString strSQL);

	// ɾ����
	BOOL DropTable(CString strTableName);

	// ��ѯ����
	// ����CppSQLite3Query������Եõ��������������
	void QueryData(IN CString strSQL, OUT CppSQLite3Query& query);

	// �ж�ָ�����ݿ�����Ƿ����ָ���ֶ�
	BOOL IsExistField(CString strTableName, CString strFieldName);

	// ��ȡ��������к�
	long GetLastInsertRowID();

	// ִ��SQL
	// ����ֵ��Ӱ������
	int Execute(CString strSQL);

	CppSQLite3Statement CompileStatement(const char* pData);

private:
	CppSQLite3DB	m_sqliteDB;
};

#endif // __H_SQLITE3EX_DEFINE_INCLUDE_H__