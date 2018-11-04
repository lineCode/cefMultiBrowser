#pragma once
#include "include/cef_v8.h"
#include <map>
#include "RenderAndBrowserApp.h"
#include "CefHandlerBack.h"
namespace ns_CefUI {
	class CV8ExtensionHandler : public CefV8Handler
    {
	public:
		CV8ExtensionHandler();
		~CV8ExtensionHandler();

		//js�ص�����
		virtual bool Execute(const CefString& name,
			CefRefPtr<CefV8Value> object,
			const CefV8ValueList& arguments,
			CefRefPtr<CefV8Value>& retval,
			CefString& exception) OVERRIDE;

		
		//ע����չ����
		void SetFunction(const CefString &name, CustomFunction function);

	private:
		//V8js�ص��ӿ�ʵ��
		//CefRefPtr<IExecuteSolt> execute_solt_;
		std::map<CefString, CustomFunction> function_map_;
		IMPLEMENT_REFCOUNTING(CV8ExtensionHandler);
	};
}

