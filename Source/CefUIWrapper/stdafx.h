// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�: 
#include <windows.h>


// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include "CefUIWrapper.h"
#include "..\DuiLib\UIlib.h"
using namespace DuiLib;
#ifdef _DEBUG
#     pragma comment(lib, "DuiLib_d.lib")
#else
#     pragma comment(lib, "DuiLib.lib")
#endif


