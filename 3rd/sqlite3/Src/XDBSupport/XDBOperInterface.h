
#pragma once

#include "comutil.h"

//=======================================================================
// IXDBRecordset - ���ݿ��¼��
//=======================================================================
MIDL_INTERFACE("97560C71-4CE9-4A7C-9A57-8E555F8E433A")
IXDBRecordset : public IUnknown
{
	virtual	long	GetFieldCount()const=0;
	virtual	HRESULT	GetFieldName(int nField, OUT _bstr_t& bstrField)const=0;

	//Start() -> GetFieldValue() -> Next()
	virtual HRESULT Start()=0;	//��ʼ��ȡһ����¼
	virtual HRESULT Next()=0;	//������ȡ��һ����¼
	virtual	HRESULT	GetFieldValue(LPCTSTR lpszField, OUT _variant_t& val)const=0;
	virtual	HRESULT	GetFieldValue(int nField, OUT _variant_t& val, OUT _bstr_t* pField=NULL)const=0;
};

//=======================================================================
// IXDBRecordsetAdd - �����ݿ���Ӽ�¼
//=======================================================================
MIDL_INTERFACE("F96CA966-28BC-479F-B6F1-38538613A4EF")
IXDBRecordsetAdd : public IUnknown
{
	//AddNew()->SetFieldValue()..SetFieldValue() -> Update()
	virtual HRESULT AddNew()=0;	//��ʼ���һ���¼�¼
	virtual HRESULT Update()=0;	//���¼�¼�����ݿ��ţ����Զ��AddNew()�����һ����Update()
	virtual	HRESULT	SetFieldValue(LPCTSTR lpszField, const _variant_t& val)=0;
};

//=======================================================================
// IXDBConnection - ���ݿ����Ӷ���
//=======================================================================
MIDL_INTERFACE("F5EE2307-6841-4973-869F-B29242F76825")
IXDBConnection : public IUnknown
{
	virtual	DWORD	GetDBType()const=0;	//��ȡ���ݿ����ͣ��������ݿ�ʱָ��

	virtual HRESULT	Open( LPCTSTR lpszDatabase)=0;
	virtual void	Close()=0;
	virtual	bool	IsOpen()const=0;
	virtual bool    IsExistTable(LPCTSTR lpszTableName)=0;

	virtual	HRESULT	Excute(LPCTSTR lpszCommand, OUT IXDBRecordset** ppRecdset = NULL)=0;
	virtual	HRESULT	AddRecord(LPCTSTR lpszTableName, IXDBRecordsetAdd** ppRecdset)=0;

	virtual	HRESULT	BeginTrans()=0;
	virtual	HRESULT CommitTrans()=0;
	virtual	HRESULT RollbackTrans()=0;
};
