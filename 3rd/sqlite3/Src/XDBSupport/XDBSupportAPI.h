#pragma once

#include "XDBSupportDef.h"
#include "XDBOperInterface.h"

//--------------------------------------------
// CreateXDBInstance
//--------------------------------------------
HRESULT CreateXDBInstance(IXDBConnection** ppObj);

//--------------------------------------------
// DB oper help
//--------------------------------------------

//��ȡ���ݿ⵱ǰʱ���ַ�
wstring GetDBDateString(IXDBConnection* pDB, bool bUTC);
//��ȡ���ݿ�ĵ�ǰʱ��
HRESULT	GetDBDateTime(_variant_t& val, IXDBConnection* pDB, bool bUTC=true);

//--------------------------------------------
// Variant help
//--------------------------------------------

BOOL	BufToVariant(VARIANT& val, PVOID pBuf, int nSize);

int		BufFromVariantBegin(const VARIANT& val);//����������
void	BufFromVariantEnd(PVOID pBuf, const VARIANT& val);