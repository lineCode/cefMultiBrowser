// Copyright (c) 2018 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=b5571470d0f53b671bfc5c223e9e2239fb590801$
//

#include "libcef_dll/ctocpp/print_dialog_callback_ctocpp.h"
#include "libcef_dll/ctocpp/print_settings_ctocpp.h"

// VIRTUAL METHODS - Body may be edited by hand.

void CefPrintDialogCallbackCToCpp::Continue(
    CefRefPtr<CefPrintSettings> settings) {
  cef_print_dialog_callback_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, cont))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: settings; type: refptr_same
  DCHECK(settings.get());
  if (!settings.get())
    return;

  // Execute
  _struct->cont(_struct, CefPrintSettingsCToCpp::Unwrap(settings));
}

void CefPrintDialogCallbackCToCpp::Cancel() {
  cef_print_dialog_callback_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, cancel))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->cancel(_struct);
}

// CONSTRUCTOR - Do not edit by hand.

CefPrintDialogCallbackCToCpp::CefPrintDialogCallbackCToCpp() {}

template <>
cef_print_dialog_callback_t* CefCToCppRefCounted<
    CefPrintDialogCallbackCToCpp,
    CefPrintDialogCallback,
    cef_print_dialog_callback_t>::UnwrapDerived(CefWrapperType type,
                                                CefPrintDialogCallback* c) {
  NOTREACHED() << "Unexpected class type: " << type;
  return NULL;
}

#if DCHECK_IS_ON()
template <>
base::AtomicRefCount CefCToCppRefCounted<
    CefPrintDialogCallbackCToCpp,
    CefPrintDialogCallback,
    cef_print_dialog_callback_t>::DebugObjCt ATOMIC_DECLARATION;
#endif

template <>
CefWrapperType CefCToCppRefCounted<CefPrintDialogCallbackCToCpp,
                                   CefPrintDialogCallback,
                                   cef_print_dialog_callback_t>::kWrapperType =
    WT_PRINT_DIALOG_CALLBACK;