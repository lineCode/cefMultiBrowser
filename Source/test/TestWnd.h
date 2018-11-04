#pragma once
#include "UIlib.h"
#include "..\CefUIWrapper\CefUIWrapperHeads.h"

using namespace DuiLib;
class CTestWnd :
	public WindowImplBase,
	public COtherHandleSlot
{
public:
	CTestWnd(void);
	~CTestWnd(void);
	LPCTSTR GetWindowClassName() const ;
	virtual CDuiString GetSkinFolder();
	virtual CDuiString GetSkinFile();
	virtual UILIB_RESTYPE GetResourceType() const;
	virtual void InitWindow();

	virtual void Notify(TNotifyUI& msg);
	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	void Show();


	CControlUI* CreateControl(LPCTSTR pstrClass);

	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser);
	virtual void DoClose(CefRefPtr<CefBrowser> browser);
	//virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser);
	//���س���
	virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefLoadHandler::ErrorCode errorCode,
		const CefString& errorText,
		const CefString& failedUrl);

	//����״̬�ı�
	virtual void OnLoadingStateChange(CefRefPtr<CefBrowser> browser,
		bool isLoading,
		bool canGoBack,
		bool canGoForward);

	//���ؿ�ʼ
	virtual void OnLoadStart(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame);

	//�������
	virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		int httpStatusCode);
private:
	CCefBrowserUI* browser_;
	CHorizontalLayoutUI* browser_pan_;
};

