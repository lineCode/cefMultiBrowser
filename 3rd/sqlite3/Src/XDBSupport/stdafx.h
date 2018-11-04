// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�:
#include <windows.h>

#include "tchar.h"
#include "assert.h"
#include "objidl.h"
#include "string"
using namespace std;

#if defined(_DEBUG)
	#define ASSERT(x) assert(x)
#else
	#define ASSERT(x)
#endif

#ifdef _UNICODE
typedef std::wstring	stdstring;
#else
typedef std::string		stdstring;
#endif 

#include <list>

#include "..\..\Include\TArray.h"
#include "..\..\Include\ASComImplHelp.h"
#include "..\..\Include\sqlite3.h"
