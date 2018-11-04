// SQLite3DemoDlg.h : ͷ�ļ�
//

#pragma once

#include "DataLog.h"
#include "afxcmn.h"

// CSQLite3DemoDlg �Ի���
class CSQLite3DemoDlg : public CDialog
{
// ����
public:
	CSQLite3DemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SQLITE3DEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual BOOL DestroyWindow();
	afx_msg void OnBtnInsertData();
	afx_msg void OnBtnDeleteData();
	afx_msg void OnBtnBrowseFile();
	DECLARE_MESSAGE_MAP()

private:
	void InitChildCtrls();
	void SetListCtrlStyle(CListCtrl& list);
	void OpenDatabase();
	void InitDbListData(STableDataLog& sDbData);
	void InitDbListDatas();
	CString GetModuleDirectory(HINSTANCE hInstCurModule);
	LONGLONG GetFileSize(CString strFileFullPath);
	CString GetFileSizeString(UINT64 ullFileSize);

private:
	CSqlite3Database		m_sqlite3DB;
	CTableDataLogAccessor	m_dataLogAccessor;
	
	CString		m_strSqliteVersion;
	CString		m_strDBFile;
	CListCtrl	m_listDbData;
	CString		m_strFileName;
	CString		m_strFileSize;
	CString		m_strFileExt;
	CString		m_strKillStatus;
	CString		m_strTask;
};
