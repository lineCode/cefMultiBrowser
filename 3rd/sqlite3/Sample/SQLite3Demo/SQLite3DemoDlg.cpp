// SQLite3DemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SQLite3Demo.h"
#include "SQLite3DemoDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CSQLite3DemoDlg �Ի���




CSQLite3DemoDlg::CSQLite3DemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSQLite3DemoDlg::IDD, pParent)
	, m_strSqliteVersion(_T(""))
	, m_strDBFile(_T("DataLog.db"))
	, m_strFileName(_T(""))
	, m_strFileSize(_T("0"))
	, m_strFileExt(_T(""))
	, m_strKillStatus(_T("��ȫ"))
	, m_strTask(_T("�ڶ�ɱ��"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSQLite3DemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SQLITE_VERSION, m_strSqliteVersion);
	DDX_Text(pDX, IDC_EDIT_DBFILE, m_strDBFile);
	DDX_Control(pDX, IDC_LIST_DBDATA, m_listDbData);
	DDX_Text(pDX, IDC_EDIT_FILENAME, m_strFileName);
	DDX_Text(pDX, IDC_EDIT_FILESIZE, m_strFileSize);
	DDX_Text(pDX, IDC_EDIT_FILEEXT, m_strFileExt);
	DDX_Text(pDX, IDC_EDIT_KILLSTATUS, m_strKillStatus);
	DDX_Text(pDX, IDC_EDIT_TASK, m_strTask);
}

BEGIN_MESSAGE_MAP(CSQLite3DemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_INSERTDATA, &CSQLite3DemoDlg::OnBtnInsertData)
	ON_BN_CLICKED(IDC_BTN_DELETEDATA, &CSQLite3DemoDlg::OnBtnDeleteData)
	ON_BN_CLICKED(IDC_BTN_BROWSEFILE, &CSQLite3DemoDlg::OnBtnBrowseFile)
END_MESSAGE_MAP()


// CSQLite3DemoDlg ��Ϣ�������

BOOL CSQLite3DemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	InitChildCtrls();

	// �����ݿ���ʾ��¼
	OpenDatabase();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSQLite3DemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSQLite3DemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CSQLite3DemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CSQLite3DemoDlg::DestroyWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	m_sqlite3DB.CloseDatabase();

	return CDialog::DestroyWindow();
}

void CSQLite3DemoDlg::OnBtnInsertData()
{
	UpdateData(TRUE);

	if(m_strFileName.IsEmpty())
	{
		AfxMessageBox(_T("�ļ�����Ϊ�գ�"));
		return;
	}

	STableDataLog sTableDb;
	sTableDb.strID = TransUTF8ToUnicode(CreateGuidstring(TRUE).c_str());
	sTableDb.strFileName = m_strFileName;
	sTableDb.strFileSize = m_strFileSize;
	sTableDb.strFileExt = m_strFileExt;
	CTime time = CTime::GetCurrentTime();
	sTableDb.strStartTime = time.Format(_T("%Y-%m-%d %H:%M:%S"));
	sTableDb.strEndTime = time.Format(_T("%Y-%m-%d %H:%M:%S"));
	sTableDb.strKillStatus = m_strKillStatus;
	sTableDb.strTask = m_strTask;

	UpdateData(FALSE);

	m_dataLogAccessor.InsertData(sTableDb);

	InitDbListDatas();
}

void CSQLite3DemoDlg::OnBtnDeleteData()
{
	POSITION pos = m_listDbData.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		AfxMessageBox(_T("No items were selected!"));
		return;
	}

	while (pos)
	{
		int nItem = m_listDbData.GetNextSelectedItem(pos);
		CString strID = m_listDbData.GetItemText(nItem, 0);

		m_dataLogAccessor.DeleteData(strID);
		InitDbListDatas();
	}

	UpdateData(TRUE);
}

void CSQLite3DemoDlg::InitChildCtrls()
{
	UpdateData(TRUE);

	m_strSqliteVersion = m_sqlite3DB.GetSQLiteVersion();
	
	CString strCurPath = GetModuleDirectory(AfxGetInstanceHandle());
	strCurPath.TrimRight(_T("\\"));
	strCurPath += _T("\\");
	strCurPath += m_strDBFile;
	m_strDBFile = strCurPath;

	UpdateData(FALSE);


	SetListCtrlStyle(m_listDbData);
	// ���ñ�ͷ
	int nIndex = 0;
	m_listDbData.InsertColumn( nIndex++, _T("ID"), LVCFMT_LEFT, 200 );
	m_listDbData.InsertColumn( nIndex++, _T("�ļ�����"), LVCFMT_LEFT, 300 );
	m_listDbData.InsertColumn( nIndex++, _T("�ļ���С"), LVCFMT_LEFT, 100 );
	m_listDbData.InsertColumn( nIndex++, _T("�ļ�����"), LVCFMT_LEFT, 150 );
	m_listDbData.InsertColumn( nIndex++, _T("����ʼʱ��"), LVCFMT_LEFT, 200 );
	m_listDbData.InsertColumn( nIndex++, _T("�������ʱ��"), LVCFMT_LEFT, 200 );
	m_listDbData.InsertColumn( nIndex++, _T("ɱ��״̬"), LVCFMT_LEFT, 100 );
	m_listDbData.InsertColumn( nIndex++, _T("������Ŀ"), LVCFMT_LEFT, 150 );
}

void CSQLite3DemoDlg::SetListCtrlStyle(CListCtrl& list)
{
	// ����listctrl �����չ���
	LONG lStyle;
	lStyle = GetWindowLong(list.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
	lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
	lStyle |= LVS_REPORT; //����style
	SetWindowLong(list.m_hWnd, GWL_STYLE, lStyle);//����style

	DWORD dwStyle = list.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	//dwStyle |= LVS_EX_CHECKBOXES;//itemǰ����checkbox�ؼ�
	list.SetExtendedStyle(dwStyle); //������չ���
}

void CSQLite3DemoDlg::OpenDatabase()
{
	UpdateData(TRUE);

	////--���Ӿ����ò�Ҫ���̼߳乲��������������ݿ�--https://blog.csdn.net/wsmrcool/article/details/8287904///
	//����һ��
	//string ssTst = "update EventUpFailed set uid='dsqw'";
	//static sqlite3* m_db = nullptr; 
	//CW2M  sDB(m_strDBFile, CP_UTF8);
	//sqlite3_open(sDB, &m_db);

	//int ret = sqlite3_exec(m_db, ssTst.data(), NULL, NULL, NULL);
	//return ;

	//���Զ���
// 	static CComPtr<IXDBConnection> dbCon, dbcon2;
// 	CreateXDBInstance(&dbCon);
// 	dbCon->Open(m_strDBFile);
// 	
// 	CreateXDBInstance(&dbcon2);
// 	dbcon2->Open(m_strDBFile);
// 	CString sss;
// 	sss.Format(_T("update db set TaskColumn='dsqw' where id='EE9FBFA7-7CC4-4866-8F54-8198692ED186'"));
// 	dbcon2->Excute(sss);
// 	return;

	if(FALSE == m_sqlite3DB.OpenDatabase(m_strDBFile))
	{
		AfxMessageBox(_T("OpenDatabase Failed!"));
		return;
	}

	// ������
	m_dataLogAccessor.SetSqlite3DB(m_sqlite3DB.GetSqlite3DB());
	m_dataLogAccessor.CreateTable();

	InitDbListDatas();
}


void CSQLite3DemoDlg::InitDbListData(STableDataLog& sDbData)
{
	int nIndex = 0;
	int nRow = m_listDbData.InsertItem(nIndex++, sDbData.strID);
	m_listDbData.SetItemText(nRow, nIndex++, sDbData.strFileName);
	m_listDbData.SetItemText(nRow, nIndex++, sDbData.strFileSize);
	m_listDbData.SetItemText(nRow, nIndex++, sDbData.strFileExt);
	m_listDbData.SetItemText(nRow, nIndex++, sDbData.strStartTime);
	m_listDbData.SetItemText(nRow, nIndex++, sDbData.strEndTime);
	m_listDbData.SetItemText(nRow, nIndex++, sDbData.strKillStatus);
	m_listDbData.SetItemText(nRow, nIndex++, sDbData.strTask);
}

void CSQLite3DemoDlg::InitDbListDatas()
{
	ASTableDataLogArray asTableDb;
	m_dataLogAccessor.GetAllDatas(asTableDb);

	m_listDbData.DeleteAllItems();
	for(int i=0; i<asTableDb.GetSize(); i++)
	{
		STableDataLog sDbData = asTableDb.GetAt(i);
		InitDbListData(sDbData);
	}
}


///////////////////////////////////////////////////////////////
//	�� �� �� : GetModuleDirectory
//	�������� : Global
//	�������� : ��ȡָ��Module����Ŀ¼
//	������� : 
//	��    ע : ���ؽ���ԡ�\����β
//	��    �� : hesl
//	ʱ    �� : 2008��7��22��
//	�� �� ֵ : CString����ָ��Module����Ŀ¼
//	����˵�� : HINSTANCE hInstCurModule����[in]ָ��ģ����
///////////////////////////////////////////////////////////////
CString CSQLite3DemoDlg::GetModuleDirectory(HINSTANCE hInstCurModule)
{
	TCHAR chrModuleFileName[MAX_PATH];
	memset(chrModuleFileName, 0, sizeof(chrModuleFileName));
	GetModuleFileName(hInstCurModule, chrModuleFileName, MAX_PATH);

	CString strCurFullPath = chrModuleFileName;
	int nPos = strCurFullPath.ReverseFind('\\');
	if(nPos == -1)
	{
		return _T("C:\\");	
	}

	return strCurFullPath.Left(nPos + 1); 
}

///////////////////////////////////////////////////////////////
//	�� �� �� : GetFileSize
//	�������� : Global
//	�������� : ��ȡָ���ļ���С
//	������� : 
//	��    ע : 
//	��    �� : hesl
//	ʱ    �� : 2008��7��22��
//	�� �� ֵ : LONGLONG����ָ���ļ���С
//	����˵�� : CString strFileFullPath����[in]ָ���ļ�ȫ·��
///////////////////////////////////////////////////////////////
LONGLONG CSQLite3DemoDlg::GetFileSize(CString strFileFullPath)
{	
	LONGLONG llFileSize = 0;

	WIN32_FIND_DATA FileData;
	HANDLE hFind = FindFirstFile(strFileFullPath, &FileData);
	if(hFind != INVALID_HANDLE_VALUE)
	{
		llFileSize = ((LONGLONG)FileData.nFileSizeLow) | ((LONGLONG)FileData.nFileSizeHigh << 32);
		FindClose(hFind);
	}

	return llFileSize;
}

CString CSQLite3DemoDlg::GetFileSizeString(UINT64 ullFileSize)
{
	CString csFileSize;

	double lFileSize = (double)ullFileSize;
	if (ullFileSize < 1024)
	{
		csFileSize.Format(_T("%I64u B"), ullFileSize);
	}
	else if (ullFileSize < 1024 * 1024)
	{
		lFileSize /= 1024;
		csFileSize.Format(_T("%.0f KB"), lFileSize);
	}
	else if (ullFileSize < 1024 * 1024 * 1024)
	{
		lFileSize /= 1024 * 1024;
		csFileSize.Format(_T("%.2f MB"), lFileSize);
	}
	else
	{
		lFileSize /= 1024 * 1024 * 1024;
		csFileSize.Format(_T("%.2f GB"), lFileSize);
	}

	return csFileSize;
}

void CSQLite3DemoDlg::OnBtnBrowseFile()
{
	CFileDialog dlg(TRUE, _T("All Files (*.*)"), NULL, OFN_READONLY | OFN_FILEMUSTEXIST, _T("All Files (*.*)|*.*||"), NULL);
	if(IDOK == dlg.DoModal())
	{
		m_strFileName = dlg.GetPathName();
		m_strFileExt = dlg.GetFileExt();
		m_strFileSize = GetFileSizeString(GetFileSize(m_strFileName));
		UpdateData(FALSE);
	}
}
