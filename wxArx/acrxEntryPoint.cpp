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
//----- acrxEntryPoint.cpp
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
#include "WxArxApp.h"
#include "WxPaletteSet.h"


//-----------------------------------------------------------------------------
#define szRDS _RXST("")

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class wxArx : public AcRxArxApp
{
    inline static WxPaletteSet* _paletteSet = nullptr;

public:
    wxArx() : AcRxArxApp()
    {
    }

    virtual AcRx::AppRetCode On_kInitAppMsg(void* pkt)
    {
        AcRx::AppRetCode retCode = AcRxArxApp::On_kInitAppMsg(pkt);
        acrxLockApplication(pkt); //in case there's some resource still open
        WxArxApp::init();
        return (retCode);
    }

    virtual AcRx::AppRetCode On_kUnloadAppMsg(void* pkt)
    {
        AcRx::AppRetCode retCode = AcRxArxApp::On_kUnloadAppMsg(pkt);
        WxArxApp::uninit();
        return (retCode);
    }

    virtual AcRx::AppRetCode On_kLoadDwgMsg(void* pkt) override
    {
        AcRx::AppRetCode retCode = AcRxDbxApp::On_kLoadDwgMsg(pkt);
        return retCode;
    }

    virtual void RegisterServerComponents()
    {
    }

    static void wxArx_wxdoit(void)
    {
        auto& app = WxArxApp::instance();
        wxWindow* win = wxTheApp->GetMainTopWindow();
        if (win)
        {
            wxDialog dlg;
            if (wxXmlResource::Get()->LoadDialog(&dlg, win, "DLG_INSERTTABLE"))
            {
                dlg.SetIcon(app.getWxIcon());
                dlg.ShowModal();
            }
        }
    }

    static void wxArx_wxpalette(void)
    {
        if (_paletteSet == nullptr)
        {
            _paletteSet = new WxPaletteSet();
            _paletteSet->add(new WxBlockPalette());
        }
        _paletteSet->setVisible(true);
    }
};

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(wxArx)
ACED_ARXCOMMAND_ENTRY_AUTO(wxArx, wxArx, _wxdoit, wxdoit, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(wxArx, wxArx, _wxpalette, wxpalette, ACRX_CMD_TRANSPARENT, NULL)

