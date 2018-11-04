#if !defined(_INCLUDE_SQLITE3EXLIB_H__)
#define _INCLUDE_SQLITE3EXLIB_H__

//////////////////////////////////////////////////////////////////////////
//	�ⲿģ�飬ʹ��Sqlite3Ex��ʱ������Ҫ������ͷ�ļ�����
//	
//	CppSQLite3.h�����ϱ��˷�װ��ʹ��sqlite3��CPP�࣬����Ϊ�ⲿ�࣬Ҳ����ֱ
//		��ʹ��
//
//	Sqlite3ExDefine.h����װ�����ݿ�����������ݱ�����࣬���߿��Լ̳�ʹ��
//////////////////////////////////////////////////////////////////////////

#define SQLITE3EX_API		AFX_API_IMPORT
#define SQLITE3EX_CLASS		AFX_CLASS_IMPORT

#include "CppSQLite3.h"
#include "Sqlite3ExDefine.h"


#ifdef WIN64
	#if (defined _UNICODE) || (defined UNICODE)
		#ifdef _DEBUG
			#pragma message("******** Sqlite3Ex����ǰ���뻷�� = Win64_UnicodeDebug ********")
			#pragma comment(lib, __FILE__"\\..\\..\\Lib\\Win64\\Sqlite3ExUD.lib")
		#else
			#pragma message("******** Sqlite3Ex����ǰ���뻷�� = Win64_UnicodeRelease ********")
			#pragma comment(lib, __FILE__"\\..\\..\\Lib\\Win64\\Sqlite3ExU.lib")
		#endif	//_DEBUG
	#endif //_UNICODE
#elif defined(WIN32)
	#if (defined _UNICODE) || (defined UNICODE)
		#ifdef _DEBUG
			#pragma message("******** Sqlite3Ex����ǰ���뻷�� = Win32_UnicodeDebug ********")
			#pragma comment(lib, __FILE__"\\..\\..\\Lib\\Win32\\Sqlite3ExUD.lib")
		#else
			#pragma message("******** Sqlite3Ex����ǰ���뻷�� = Win32_UnicodeRelease ********")
			#pragma comment(lib, __FILE__"\\..\\..\\Lib\\Win32\\Sqlite3ExU.lib")
		#endif	//_DEBUG
	#endif //_UNICODE
#endif //WIN64

#endif // _INCLUDE_SQLITE3EXLIB_H__