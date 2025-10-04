// (C) Copyright 2002-2007 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//- StdAfx.h : include file for standard system include files,
//-      or project specific include files that are used frequently,
//-      but are changed infrequently
//-----------------------------------------------------------------------------
#pragma once

#pragma pack (push, 8)
#pragma warning(disable: 4786 4996 26812)

//#pragma warning(disable: 4098)

//-----------------------------------------------------------------------------
#define STRICT

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN			//- Exclude rarely-used stuff from Windows headers
#endif

//- Modify the following defines if you have to target a platform prior to the ones specified below.
//- Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER					//- Allow use of features specific to Windows 95 and Windows NT 4 or later.
#define WINVER _WIN32_WINNT_WIN10			//- Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
#endif

#ifndef _WIN32_WINNT			//- Allow use of features specific to Windows NT 4 or later.
#define _WIN32_WINNT _WIN32_WINNT_WIN10		//- Change this to the appropriate value to target Windows 2000 or later.
#endif						

#ifndef _WIN32_WINDOWS			//- Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS _WIN32_WINNT_WIN10	//- Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE				//- Allow use of features specific to IE 4.0 or later.
#define _WIN32_IE _WIN32_WINNT_WIN10		//- Change this to the appropriate value to target IE 5.0 or later.
#endif

#define SETBIT(flags, bit, value) ((value) ? (flags |= (bit)) : (flags &= ~(bit)))
#define GETBIT(flags, bit) (((flags) & (bit)) ? true : false)

//- ObjectARX and OMF headers needs this
#include <map>
#include <vector>
#include <array>
#include <functional>
#include <memory>
#include <variant>
#include <string>
#include <sstream>
#include <algorithm>
#include <filesystem>

//-----------------------------------------------------------------------------
#include <afxwin.h>				//- MFC core and standard components
#include <afxext.h>				//- MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>				//- MFC OLE classes
#include <afxodlgs.h>			//- MFC OLE dialog classes
#include <afxdisp.h>			//- MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>				//- MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>				//- MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>			//- MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>				//- MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

//-----------------------------------------------------------------------------
//- Include ObjectDBX/ObjectARX headers
//- Uncomment one of the following lines to bring a given library in your project.
//#define _BREP_SUPPORT_			//- Support for the BRep API
//#define _HLR_SUPPORT_				//- Support for the Hidden Line Removal API
//#define _AMODELER_SUPPORT_		//- Support for the AModeler API
//#define _ASE_SUPPORT_				//- Support for the ASI/ASE API
//#define _RENDER_SUPPORT_			//- Support for the AutoCAD Render API
//#define _ARX_CUSTOM_DRAG_N_DROP_	//- Support for the ObjectARX Drag'n Drop API
//#define _INC_LEAGACY_HEADERS_		//- Include legacy headers in this project
#include "arxHeaders.h"
#include "axlock.h"

#if defined(_ARXTARGET)
#pragma comment( lib , "AcPal.lib" )
#pragma comment( lib , "acgeoment.lib" )
#endif

#if defined(_BRXTARGET)
//
#endif

#if defined(_GRXTARGET)
#pragma comment( lib , "gcad.lib" )
#pragma comment( lib , "gcbase.lib" )
#pragma comment( lib , "gcbr.lib" )
#pragma comment( lib , "gccore.lib" )
#pragma comment( lib , "gcdb.lib" )
#endif

#if defined(_ZRXTARGET)
//
#endif

//-----------------------------------------------------------------------------
#include "DocData.h" //- Your document specific data class holder

//- Declare it as an extern here so that it becomes available in all modules
extern AcApDataManager<CDocData> DocVars;

//-----------------------------------------------------------------------------
// nope
template <typename T>
struct non_copyable_movable
{
    non_copyable_movable() = default;
    ~non_copyable_movable() = default;
    non_copyable_movable(const non_copyable_movable&) = delete;
    non_copyable_movable& operator=(const non_copyable_movable&) = delete;
    non_copyable_movable(non_copyable_movable&&) = delete;
    non_copyable_movable& operator=(non_copyable_movable&&) = delete;
};


#ifdef __WXMSW__
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/string.h>
#include <wx/xrc/xmlres.h>

#pragma comment(lib, "wxbase33u.lib")
//#pragma comment(lib, "wxtiff.lib")
//#pragma comment(lib, "wxbase33u_net.lib")
//#pragma comment(lib, "wxscintilla.lib")
//#pragma comment(lib, "wxbase33u_xml.lib")
//#pragma comment(lib, "wxregexu.lib")
//#pragma comment(lib, "wxexpat.lib")
//#pragma comment(lib, "wxpng.lib")
//#pragma comment(lib, "wxjpeg.lib")
//#pragma comment(lib, "wxmsw33u_xrc.lib")
//#pragma comment(lib, "wxmsw33u_adv.lib")
//#pragma comment(lib, "wxmsw33u_webview.lib")
//#pragma comment(lib, "wxmsw33u_aui.lib")
//#pragma comment(lib, "wxmsw33u_stc.lib")
#pragma comment(lib, "wxmsw33u_core.lib")
//#pragma comment(lib, "wxmsw33u_richtext.lib")
//#pragma comment(lib, "wxmsw33u_gl.lib")
//#pragma comment(lib, "wxmsw33u_ribbon.lib")
//#pragma comment(lib, "wxmsw33u_html.lib")
//#pragma comment(lib, "wxmsw33u_qa.lib")
//#pragma comment(lib, "wxmsw33u_media.lib")
//#pragma comment(lib, "wxzlib.lib")
//#pragma comment(lib, "wxmsw33u_propgrid.lib")
#endif

constexpr auto makeBlockRefIterator = [](const AcDbBlockTableRecord& record)
    {
        AcDbBlockReferenceIdIterator* pIter = nullptr;
        Acad::ErrorStatus es = record.newBlockReferenceIdIterator(pIter);
        return std::make_tuple(es, std::unique_ptr<AcDbBlockReferenceIdIterator>(pIter));
    };

template<typename IteratorType>
constexpr auto makeIterator = [](const auto& record)
    {
        IteratorType* pIter = nullptr;
        Acad::ErrorStatus es = record.newIterator(pIter);
        return std::make_tuple(es, std::unique_ptr<IteratorType>(pIter));
    };
constexpr auto makeAcDbSymbolTableIterator = makeIterator<AcDbSymbolTableIterator>;
constexpr auto makeBlockTableIterator = makeIterator<AcDbBlockTableIterator>;
constexpr auto makeBlockTableRecordIterator = makeIterator<AcDbBlockTableRecordIterator>;

//-------------------------------------------------------------------------------------
//AcResBufPtr
using AcResBufPtr = std::unique_ptr < resbuf, decltype([](resbuf* ptr) noexcept
    {
        acutRelRb(ptr);
    }) > ;

//-------------------------------------------------------------------------------------
//AcDbObjectUPtr
template<typename T>
using AcDbObjectUPtr = std::unique_ptr < T, decltype([](T* ptr) noexcept
    {
        if (ptr != nullptr)
        {
            if (!ptr->objectId().isNull())
                ptr->close();
            else
                delete ptr;
        }
    }) > ;

using AcDbEntityUPtr = AcDbObjectUPtr<AcDbEntity>;
using AcDbAcDbPolylineUPtr = AcDbObjectUPtr<AcDbPolyline>;

//
typedef AcDbObjectPointer<AcDbPolyline>AcDbPolylinePointer;


#pragma pack (pop)

