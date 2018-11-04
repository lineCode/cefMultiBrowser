#pragma once

#include "CefHandlerBack.h"
#include "include/base/cef_lock.h"
#include "V8ExtensionHandler.h"

#include <set>
#include <set>
using namespace std;

namespace ns_CefUI {

	class CBrowserClient :
		public CefClient, 
		public COtherHandleSlot
	{
	public:

		CBrowserClient(std::unique_ptr<COtherHandleSlot> other_handle=NULL);

		~CBrowserClient(void);

		virtual CefRefPtr<CefRequestHandler> GetRequestHandler() OVERRIDE;
		virtual CefRefPtr<CefContextMenuHandler> GetContextMenuHandler();
		virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE;
		virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE;
		virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE;
		virtual CefRefPtr<CefDownloadHandler> GetDownloadHandler() OVERRIDE;
		virtual CefRefPtr<CefDragHandler> GetDragHandler() OVERRIDE;

		//CefRequestHandler
		cef_return_value_t OnBeforeResourceLoad(
			CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			CefRefPtr<CefRequest> request,
			CefRefPtr<CefRequestCallback> callback) OVERRIDE;

		//CefContextMenuHandler
		virtual void OnBeforeContextMenu(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			CefRefPtr<CefContextMenuParams> params,
			CefRefPtr<CefMenuModel> model);

		virtual bool OnContextMenuCommand(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			CefRefPtr<CefContextMenuParams> params,
			int command_id,
			EventFlags event_flags);

		// CefLifeSpanHandler methods:
		//�����µĵ�������ĵ���
		virtual bool OnBeforePopup(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			const CefString& target_url,
			const CefString& target_frame_name,
			CefLifeSpanHandler::WindowOpenDisposition target_disposition,
			bool user_gesture,
			const CefPopupFeatures& popupFeatures,
			CefWindowInfo& windowInfo,
			CefRefPtr<CefClient>& client,
			CefBrowserSettings& settings,
			bool* no_javascript_access);
		virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
		virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
		virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

		// CefLoadHandler methods:
		//���س���
		virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			ErrorCode errorCode,
			const CefString& errorText,
			const CefString& failedUrl);

		//����״̬�ı�
		virtual void OnLoadingStateChange(CefRefPtr<CefBrowser> browser,
			bool isLoading,
			bool canGoBack,
			bool canGoForward);

		//���ؿ�ʼ
		virtual void OnLoadStart(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			TransitionType transition_type);

		//�������
		virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			int httpStatusCode);

		// CefDisplayHandler methods:
		//��ַ�ı�
		virtual void OnAddressChange(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			const CefString& url);
		//����ı�
		virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,
			const CefString& title);
		//ҳ��ͼ��ı�
		virtual void OnFaviconURLChange(CefRefPtr<CefBrowser> browser,
			const std::vector<CefString>& icon_urls);
		//ҳ��ȫ��ʱ����
		virtual void OnFullscreenModeChange(CefRefPtr<CefBrowser> browser,
			bool fullscreen);
		//�������ʾ������ʾ
		virtual bool OnTooltip(CefRefPtr<CefBrowser> browser,
			CefString& text);
		//���յ�״̬��Ϣʱ
		virtual void OnStatusMessage(CefRefPtr<CefBrowser> browser,
			const CefString& value);
		//������ʾ����̨��Ϣ
		virtual bool OnConsoleMessage(CefRefPtr<CefBrowser> browser,
			/*cef_log_severity_t level,*/
			const CefString& message,
			const CefString& source,
			int line);

		//CefClient
		virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
			CefProcessId source_process,
			CefRefPtr<CefProcessMessage> message);

		//CefDownloadHandler
		virtual void OnBeforeDownload(
			CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefDownloadItem> download_item,
			const CefString& suggested_name,
			CefRefPtr<CefBeforeDownloadCallback> callback) OVERRIDE;

		virtual void OnDownloadUpdated(
			CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefDownloadItem> download_item,
			CefRefPtr<CefDownloadItemCallback> callback) OVERRIDE;

		//CefDragHandler
		virtual bool OnDragEnter(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefDragData> dragData,
			DragOperationsMask mask) OVERRIDE;

		virtual void OnDraggableRegionsChanged(
			CefRefPtr<CefBrowser> browser,
			const std::vector<CefDraggableRegion>& regions) OVERRIDE;

	public:
		//���ע�ắ��
		void SetFunction(const CefString &name, CustomFunction function);

		bool SetCallBackJsCallFun(CallBackJsCall func);

		//browser�Ƿ�ر�
		bool IsClosing() const;
		//�Ƿ񴴽����
		bool IsCreated() const;

	public:
		//�洢���������
		CefRefPtr<CefBrowser> browser_;
		int		m_BrowserId;
		//��
		base::Lock lock_;
		//V8��չ��
		CefRefPtr<CV8ExtensionHandler> extension_;
	private:
		std::unique_ptr<COtherHandleSlot>   other_handle_;

		CallBackJsCall m_jscallfunc;
		typedef std::set<std::wstring> ProtocalSet;
		ProtocalSet m_ProtocalSet;

		//�Ƿ�رձ�ʶ
		bool is_closing_; 
		//�Ƿ񴴽����
		bool is_created_;
		//����������Զ����ü���
		IMPLEMENT_REFCOUNTING(CBrowserClient);
	};
}

