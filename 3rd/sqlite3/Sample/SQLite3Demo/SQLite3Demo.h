// SQLite3Demo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSQLite3DemoApp:
// �йش����ʵ�֣������ SQLite3Demo.cpp
//

class CSQLite3DemoApp : public CWinApp
{
public:
	CSQLite3DemoApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSQLite3DemoApp theApp;