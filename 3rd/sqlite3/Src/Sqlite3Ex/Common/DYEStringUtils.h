
//*********************************************************
// �ļ�����DYEStringUtils.h
// ��  �ߣ�lvkun
// ��  �ڣ�
// Ŀ  �ģ��ַ���ʵ���ࡪ��ͷ�ļ�
// ��  ע��hesl������2008-07-23�� 
//*********************************************************

#if !defined DYESTRINGUTILS_H
#define DYESTRINGUTILS_H

#if _MSC_VER > 1000 
#pragma once
#endif

#include <string>
#include <sstream>
using namespace std;

#pragma comment(lib, "Rpcrt4.lib") 

/// Ϊ���ݶ����ļ�������Dll�������ַ�ʽ����Ƶĺ꣺
/// ��������ʱΪ�գ�Dll����ʱΪDY_EXT_****
#if !defined DYECOMMON_EXT_CLASS
	#define DYECOMMON_EXT_CLASS
#endif

#if !defined DYECOMMON_EXT_API
	#define DYECOMMON_EXT_API
#endif

#if !defined DYECOMMON_EXT_DATA
	#define DYECOMMON_EXT_DATA
#endif


/// �ַ���ʵ����
namespace ns_DYEStringUtils {

	/**
	*	\brief	��ָ����UTF8�ַ���ת��ΪUnicode�����
	*	\param[in]	pszSource	Դ�ַ���(UTF8)
	*/
	DYECOMMON_EXT_API CString TransUTF8ToUnicode(const char* pszSource);

	/**
	*	\brief	��ָ����Unicode�ַ���ת��ΪUTF8 string�����
	*	\param[in]	strSource	Դ�ַ���(Unicode)
	*	\return		UTF8 string
	*/
	DYECOMMON_EXT_API string  TransUnicodeToUTF8(CString strSource);

	///	��CString�ַ���ת��Ϊstd::string�ַ���
	DYECOMMON_EXT_API string TranslateCStringTostring(CString &strSource);

#if (defined _UNICODE) || (defined UNICODE)
	///	��CString�ַ���ת��Ϊstd::wstring�ַ���
	DYECOMMON_EXT_API wstring TranslateCStringTowstring(CString const &strSource);
#endif

	///	��std::string�ַ���ת��ΪCString�ַ���
	DYECOMMON_EXT_API CString TranslatestringToCString(string const &strSource);

	///	��std::wstring�ַ���ת��ΪCString�ַ���
	DYECOMMON_EXT_API CString TranslatewstringToCString(wstring const &strSource);
	
	///	��wstring�ַ���ת��Ϊstring�ַ���
	DYECOMMON_EXT_API string TranslatewstringTostring(wstring const &strSource);

#if (defined _UNICODE) || (defined UNICODE)
	///	��string�ַ���ת��Ϊwstring�ַ���
	DYECOMMON_EXT_API wstring TranslatestringTowstring(string const &strSource);
#endif

	/// ��CString�ַ��������stringstream
	DYECOMMON_EXT_API void TranslateCStringTostringstream(CString &strSource, stringstream &ss);

#if (defined _UNICODE) || (defined UNICODE)
	/// ��wstring�ַ��������stringstream
	DYECOMMON_EXT_API void TranslatewstringTostringstream(wstring const &strSource, stringstream &ss);
#endif

	/// ��string�ַ��������stringstream
	DYECOMMON_EXT_API void TranslatestringTostringstream(string const &strSource, stringstream &ss);

	///	��std::stringstream�ַ������ΪCString�ַ���
	DYECOMMON_EXT_API CString TranslatestringstreamToCString(stringstream const &ss);

#if (defined _UNICODE) || (defined UNICODE)
	///	��std::stringstream�ַ������Ϊwstring�ַ���
	DYECOMMON_EXT_API wstring TranslatestringstreamTowstring(stringstream const &ss);
#endif

	///	��std::stringstream�ַ������Ϊstring�ַ���
	DYECOMMON_EXT_API string TranslatestringstreamTostring(stringstream const &ss);

#if (defined _UNICODE) || (defined UNICODE)
	/// ����wstring��ʽ��GUID������
	DYECOMMON_EXT_API wstring CreateGuidwstring(BOOL bIncludeJointSign = TRUE);
#endif

	/// ����string��ʽ��GUID������
	DYECOMMON_EXT_API string CreateGuidstring(BOOL bIncludeJointSign = TRUE);


	/// ת������������ΪBase64�ַ���
	DYECOMMON_EXT_API CString TranBytesToBase64Str(IN  DWORD nSizeInByte, IN  PBYTE pData);

};// namespace ns_DYEStringUtils

#endif