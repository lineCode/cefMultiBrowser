#pragma once

//////////////////////////////////////////////////////////////////////////
//	���ݱ��ֶ����ƶ���
//////////////////////////////////////////////////////////////////////////

// ���ݱ�
#define TableDataLog_Name			_T("Db")
// �ֶ�����
#define TableDataLog_ID				_T("ID")
#define TableDataLog_FileName		_T("FileName")
#define TableDataLog_FileSize		_T("FileSize")
#define TableDataLog_FileExt		_T("FileExt")
#define TableDataLog_StartTime		_T("StartTime")
#define TableDataLog_EndTime		_T("EndTime")
#define TableDataLog_KillStatus		_T("KillStatus")
#define TableDataLog_TaskColumn		_T("TaskColumn")

//////////////////////////////////////////////////////////////////////////
// ���ݱ�ṹ����
//////////////////////////////////////////////////////////////////////////

struct STableDataLog
{
	CString strID;
	CString strFileName;		// �ļ���
	CString strFileSize;		// �ļ���С
	CString strFileExt;			// �ļ�����
	CString strStartTime;		// ����ʼʱ��
	CString strEndTime;			// �������ʱ��
	CString strKillStatus;		// ɱ��״̬
	CString strTask;			// ������Ŀ

	STableDataLog()
	{
		strID = _T("00000000-0000-0000-0000-000000000000");
		strFileName = _T("");
		strFileExt = _T("*.*");
		strStartTime = _T("");
		strEndTime = _T("");
		strKillStatus = _T("");
		strTask = _T("");
	}

	STableDataLog& operator = (const STableDataLog& other)
	{
		if(this != &other)
		{
			strID = other.strID;
			strFileName = other.strFileName;
			strFileSize = other.strFileSize;
			strFileExt = other.strFileExt;
			strStartTime = other.strStartTime;
			strEndTime = other.strEndTime;
			strKillStatus = other.strKillStatus;
			strTask = other.strTask;
		}

		return *this;
	}
};

typedef CArray<STableDataLog, STableDataLog&>	ASTableDataLogArray;


//////////////////////////////////////////////////////////////////////////
// ���ݱ������
//////////////////////////////////////////////////////////////////////////


class CTableDataLogAccessor : public CSqlite3DBAccessor
{
public:
	CTableDataLogAccessor(void);
	CTableDataLogAccessor(const CppSQLite3DB& sqlite3DB);
	virtual ~CTableDataLogAccessor(void);

public:
	// ������
	BOOL CreateTable();

	// ɾ����
	BOOL DropTable();

	// ��������
	int InsertData(STableDataLog& sDataLog);

	// ɾ������
	int DeleteData(CString strID);

	// ��ȡ����
	int GetAllDatas(OUT ASTableDataLogArray& asTableDB, IN CString strCondition = _T(""));

private:
	CppSQLite3DB	m_sqliteDB;
	CString			m_strTableName;
};
