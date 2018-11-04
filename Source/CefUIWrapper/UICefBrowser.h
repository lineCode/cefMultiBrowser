#pragma once

#include <share.h>
#include <Shlwapi.h>

/***********************************************************
ʹ��˵����
	1.��DuiLib::Create����ǰ����InitCef��ʼ��cef
	2.��MessageLoop()֮��Quit
***********************************************************/

namespace ns_CefUI {
	//������
	const TCHAR CCefBrowserUIClassName[] = L"CefBrowserUI";		
	//�ؼ�����
	const TCHAR CCefBrowserUIItemInterface[] = L"CefBrowser";	

	class CEFUIWRAPPER_API CCefBrowserUI : public DuiLib::CControlUI {
	public:
		CCefBrowserUI(HWND parent, CallBackJsCall func, COtherHandleSlot* set_handle = NULL, wstring _url = _T(""));
		~CCefBrowserUI(void);

	//DuiLib�ص�����
	public:
		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		void DoInit();
		//����������������ʾ���
		virtual void SetInternVisible(bool bVisible = true);

		virtual void SetPos(RECT rc, bool bNeedInvalidate = true);

		//�����Ƿ���ʾ
		virtual void SetVisible(bool bVisible = true);

	//��̬���ܽӿ�
	public:
		//��ʼ��CEF
		static bool InitCef(HINSTANCE hInstance, CefString cache_path = "", CefString log_file = "");
		//�˳�CEF
		static void Quit();
		//����cef��Ϣѭ��
		static void StartCefMessageLoop();
		static std::vector<wstring> m_vecV8Function;

	//�ؼ�cef����
	public:
		//����url
		void LoadURL(std::wstring url);
		//�Ƿ������ǰ����
		bool CanGoForward();
		//��ǰ����
		void GoForward();
		//���¼���
		void Reload();
		//���Ի������
		void ReloadIgnoreCache();
		//ֹͣ����
		void StopLoad();
		//������󵼺�
		bool CanGoBack();
		//��󵼺�
		void GoBack();
		//��ȡ��������
		CefWindowHandle GetHwnd();
		//�������ű���
		void SetZoomLevel(double zoomLevel);
		//��ȡ��ǰUrl
		CefString GetURL();
		//ִ��JS ����Ϊ һ��������js���� �����Ѿ����ڵ�js�������Ӳ���
		void ExectueJS(const CefString &jscode);
		//����Cef���������
		bool CCefBrowserUI::CreateCefWindow(HWND hWnd, CefString url, std::unique_ptr<COtherHandleSlot> other_handle = NULL);
		//�ر������
		void CloseCefWindow();
		//���ע�ắ��
		void SetFunction(const CefString &name, CustomFunction function);
	
		bool SwitchUser();

		CefRefPtr<CefBrowser>  GetBrowser();
		CefWindowHandle	       GetBrowserHwnd();//������ҳ����ģ����滹�������Ӵ��ڣ�spy++�����������µ��Ӵ��ڣ�
		
		
	//UI��ӿ�
	public:
		//�ػ������
		void ResizeBrowser(DuiLib::CDuiRect rect);
		CallBackJsCall  m_jscallfunc;

	private:
		//Ĭ�ϵ�ַ
		std::wstring url_;
		
		CefRefPtr<CBrowserClient> m_handler;

		//����load life �ص������ص�ָ��
		COtherHandleSlot* set_handle_;
		//��������
		HWND parent_hwnd_;
		//���������
		std::wstring browser_name_;
		//�Ƿ񴴽����
		bool is_created_;
	};
}

