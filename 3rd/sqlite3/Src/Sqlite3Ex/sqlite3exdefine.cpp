#pragma once

#include "stdafx.h"
#include "..\..\Include\Sqlite3ExDefine.h"
#include <map>

static int g_nTranCounter = 0; 	// �����¼��
static void PrintExceptionMsg(CppSQLite3Exception& e)
{
	CString str;
	str.Format(_T("ErrorCode: %d, ErrorMessage: %s\n"), e.errorCode(), e.errorMessage());
	OutputDebugString(str);
}

static std::map<UINT, CString> g_mapPtr2File;

//////////////////////////////////////////////////////////////////////////
// Sqlite3���ݿ�������
CSqlite3Database::CSqlite3Database()
:	m_bDBOpen(FALSE)
{
	m_strDBFilePath = _T("");
}

CSqlite3Database::~CSqlite3Database()
{
	m_bDBOpen = FALSE;
	m_strDBFilePath = _T("");
}

// SQLite3�汾
CString CSqlite3Database::GetSQLiteVersion()
{
	return TransUTF8ToUnicode(m_sqliteDB.SQLiteVersion());
}

// �����ݿ�
BOOL CSqlite3Database::OpenDatabase(CString strDBFile)
{
	try
	{
		m_sqliteDB.open(TransUnicodeToUTF8(strDBFile).c_str());
	}
	catch (CppSQLite3Exception e)
	{
		PrintExceptionMsg(e);
		throw e;
		return FALSE;
	}

	m_bDBOpen = TRUE;
	m_strDBFilePath = strDBFile;

// 	DWORD dwPid = GetCurrentProcessId();
// 	SYSTEMTIME sysTime;
// 	GetLocalTime(&sysTime);
// 	TCHAR nowTime[30];
// 	swprintf(nowTime, L"%4d-%02d-%02d_%02d:%02d:%02d", sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
// 	TRACE(L"CppSQLite3DB::open--%s,Pid:0x%08X, CSqlite3Database*:0x%08X , Time:%s\n", m_strDBFilePath, dwPid, (int)this, nowTime);
// 	UINT dbAcPtr = UINT(this); 
// 	g_mapPtr2File[dbAcPtr] = m_strDBFilePath;


	return TRUE;
}


// ��ȡ���ݿ�·��
CString CSqlite3Database::GetDatabasePath()
{
	return m_strDBFilePath;
}

// �ر����ݿ�
void CSqlite3Database::CloseDatabase()
{
	m_sqliteDB.close();
	m_bDBOpen = FALSE;

// 	DWORD dwPid = GetCurrentProcessId();
// 	SYSTEMTIME sysTime;
// 	GetLocalTime(&sysTime);
// 	TCHAR nowTime[30];
// 	swprintf(nowTime, L"%4d-%02d-%02d_%02d:%02d:%02d", sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
// 	TRACE(L"CppSQLite3DB::close--%s,Pid:0x%08X, CSqlite3Database*:0x%08X ,Time:%s\n", m_strDBFilePath, dwPid, (int)this, nowTime);
// 
// 	UINT dbAcPtr = UINT(this);
// 	std::map<UINT, CString>::iterator itor; 
// 	itor = g_mapPtr2File.find(dbAcPtr);
// 	if (itor != g_mapPtr2File.end())
// 	{
// 		g_mapPtr2File.erase(itor);
// 	}
}

// 
CppSQLite3DB& CSqlite3Database::GetSqlite3DB()
{
	return m_sqliteDB;
}

BOOL CSqlite3Database::IsDBOpen()
{
	return m_bDBOpen;
}

bool CSqlite3Database::BeginTrans()
{
	// �������쳣 �쳣���ϲ�����ߴ���
	try
	{
		if(g_nTranCounter >= 0)
		{
			CString strSql = _T("");
			if(g_nTranCounter == 0)
			{
			  strSql.Format(_T("savepoint dye%d"), g_nTranCounter);
			  m_sqliteDB.execDML(TransUnicodeToUTF8(strSql).c_str());
			  g_nTranCounter ++;
			}
			else
			{
 				strSql.Format(_T("savepoint dye%d"), g_nTranCounter);
 				g_nTranCounter ++;
				m_sqliteDB.execDML(TransUnicodeToUTF8(strSql).c_str());
			}

		}
	}
	catch(CppSQLite3Exception& e)
	{
		throw e;
		return false;
	}
	return true;
}

bool CSqlite3Database::CommitTrans()
{
	// �������쳣 �쳣���ϲ�����ߴ���
	try
	{
		if(g_nTranCounter > 0)
		{
			CString strSql = _T("commit");
			m_sqliteDB.execDML(TransUnicodeToUTF8(strSql).c_str());
			g_nTranCounter = 0;
		}
	}
	catch (CppSQLite3Exception& e)
	{
		throw e;
		return false;
	}
	return true;
}

bool CSqlite3Database::Rollback()
{
	// �������쳣 �쳣���ϲ�����ߴ���
	try
	{
		if(g_nTranCounter > 0)
		{
			g_nTranCounter --;
			CString strSql = _T("");
			strSql.Format(_T("ROLLBACK to dye%d"), g_nTranCounter);
			m_sqliteDB.execDML(TransUnicodeToUTF8(strSql).c_str());
		}
	}
	catch(CppSQLite3Exception& e)
	{
		throw e;
		return false;
	}
	return true;
}


//////////////////////////////////////////////////////////////////////////
// Sqlite3���ݿ������
CSqlite3DBAccessor::CSqlite3DBAccessor()
{

}

CSqlite3DBAccessor::CSqlite3DBAccessor(const CppSQLite3DB& sqlite3DB)
{
	m_sqliteDB = sqlite3DB;
}

CSqlite3DBAccessor::~CSqlite3DBAccessor()
{
}

// ����Sqlite3DB
void CSqlite3DBAccessor::SetSqlite3DB(const CppSQLite3DB& sqlite3DB)
{
	m_sqliteDB = sqlite3DB;
}

// ��������ж�
BOOL CSqlite3DBAccessor::IsTableExist(CString strTableName)
{
	bool bIsExist = false;
	bIsExist = m_sqliteDB.tableExists(TransUnicodeToUTF8(strTableName).c_str());
	if(bIsExist == true)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

	return FALSE;
}

// ��ͼ�������ж�
bool CSqlite3DBAccessor::IsExistView(CString strViewName)
{
	char szSQL[128];
	const char* szView;
	szView = TransUnicodeToUTF8(strViewName).c_str();
	sprintf(szSQL,
		"select count(*) from sqlite_master where type='view' and name='%s'",
		szView);
	int nRet = m_sqliteDB.execScalar(szSQL);
	return (nRet > 0);
}


// �������ݱ�
BOOL CSqlite3DBAccessor::CreateTable(CString strTableName, CString strSQL)
{
	ASSERT(!strTableName.IsEmpty());

	// ���ֱ���ڣ�ֱ�ӷ���TRUE
	CString str;
	if(m_sqliteDB.tableExists(TransUnicodeToUTF8(strTableName).c_str()))
	{
		str.Format(_T("%s has been existed, delete it first!\n"), strTableName);
		OutputDebugString(str);

		return TRUE;
	}

	try
	{
		m_sqliteDB.execDML(TransUnicodeToUTF8(strSQL).c_str());
	}
	catch(CppSQLite3Exception e)
	{
		PrintExceptionMsg(e);
		throw e;
		return FALSE;
	}

	if(m_sqliteDB.tableExists(TransUnicodeToUTF8(strTableName).c_str()))
		return TRUE;

	return FALSE;
}

// ɾ����
BOOL CSqlite3DBAccessor::DropTable(CString strTableName)
{
	CString strDropTable;
	strDropTable.Format(_T("drop table %s"), strTableName);
	try
	{
		m_sqliteDB.execDML(TransUnicodeToUTF8(strDropTable).c_str());
	}
	catch(CppSQLite3Exception e)
	{
		PrintExceptionMsg(e);
		throw e;
		return FALSE;
	}

	return TRUE;
}

// ��ѯ����
// ����CppSQLite3Query������Եõ��������������
void CSqlite3DBAccessor::QueryData(IN CString strSQL, OUT CppSQLite3Query& query)
{
	query = m_sqliteDB.execQuery(TransUnicodeToUTF8(strSQL).c_str());
}


// �ж�ָ�����ݿ�����Ƿ����ָ���ֶ�
BOOL CSqlite3DBAccessor::IsExistField(CString strTableName, CString strFieldName)
{
	BOOL bIsExistField = TRUE;
	try
	{
			CString strSql =  _T("");
			strSql.Format(_T("select * from %s"), strTableName);

			CppSQLite3Query sqlite3Query = m_sqliteDB.execQuery(TransUnicodeToUTF8(strSql).c_str());
			sqlite3Query.fieldIndex(TransUnicodeToUTF8(strFieldName).c_str());
	}
	catch(CppSQLite3Exception& e)
	{
		CString strErrMsg;
		strErrMsg.Format(_T("%s���ֶ�%s�������жϳ����쳣���󣬴������%d,������Ϣ:%s"), strTableName, strFieldName , 
			e.errorCode(), e.errorMessage());
		throw e;
		bIsExistField = FALSE;
	}
	
	return bIsExistField;
}


// ��ȡ��������к�
long CSqlite3DBAccessor::GetLastInsertRowID()
{
	return m_sqliteDB.lastRowId();
}

// ִ��SQL
// ����ֵ��Ӱ������
int CSqlite3DBAccessor::Execute(CString strSQL)
{
	int nRows = 0;

	try
	{
		nRows = m_sqliteDB.execDML(TransUnicodeToUTF8(strSQL).c_str());
	}
	catch(CppSQLite3Exception e)
	{
		PrintExceptionMsg(e);
		throw e;
		nRows = 0;
	}

	return nRows;
}


CppSQLite3Statement CSqlite3DBAccessor::CompileStatement(const char* pData)
{
	return m_sqliteDB.compileStatement(pData);
}
