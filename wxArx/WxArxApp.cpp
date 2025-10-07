#include "stdafx.h"
#include "WxArxApp.h"

//------------------------------------------------------------------------------------------------
//  Attach to AutoCAD's main frame
ArxTopLevelWindow::ArxTopLevelWindow()
{
    this->SetHWND(adsw_acadMainWnd());
    this->AdoptAttributesFromHWND();
    this->m_isShown = true;
    wxTopLevelWindows.Append(this);
}

//------------------------------------------------------------------------------------------------
// the wxApp
bool WxApp::OnInit()
{
    resbuf rb;
    const auto rt = acedGetVar(_T("COLORTHEME"), &rb);
    if (rt == RTNORM && rb.restype == RTSHORT && rb.resval.rint == 0)
    {
        if (!wxTheApp->MSWEnableDarkMode(wxApp::DarkMode_Always))
            acutPrintf(_T("MSWEnableDarkMode failed"));
    }
    wxTheApp->SetTopWindow(new ArxTopLevelWindow());
    if (wxTheApp->GetTopWindow() == nullptr)
        return false;
    wxTheApp->SetExitOnFrameDelete(false);
    return true;
}

int WxApp::OnExit()
{
    auto top = wxTheApp->GetTopWindow();
    if (top != nullptr)
        top->DissociateHandle();
    wxTopLevelWindows.Clear();
    return 0;
}

void WxApp::WakeUpIdle()
{
    const CWinApp* mfcApp = AfxGetApp();
    if (mfcApp != nullptr && mfcApp->m_pMainWnd)
    {
        ::PostMessage(mfcApp->m_pMainWnd->m_hWnd, WM_NULL, 0, 0);
    }
}

bool WxApp::initWxApp()
{
    wxApp::SetInstance(new WxApp());
    if (!wxEntryStart(_hdllInstance))
        return false;
    if (wxTheApp && wxTheApp->CallOnInit())
        return true;
    return false;
}

bool WxApp::uninitWxApp()
{
    wxTheApp->OnExit();
    wxEntryCleanup();
    return true;
}

//------------------------------------------------------------------------------------------------
//  wxArxApp
WxArxApp& WxArxApp::instance()
{
    static WxArxApp mthis;
    return mthis;
}

bool WxArxApp::init()
{
    if (auto res = WxApp::initWxApp(); !res)
    {
        acutPrintf(_T("\ninitWxApp Failed!: "));
        return false;
    }
    auto& app = WxArxApp::instance();
    app.initResources();
    return true;
}

bool WxArxApp::uninit()
{
    WxApp::uninitWxApp();
    return true;
}

const std::filesystem::path& WxArxApp::modulePath()
{
    static std::filesystem::path path;
    if (path.empty())
    {
        path = WxArxApp::moduleName();
        path.remove_filename();
    }
    return path;
}

const std::filesystem::path& WxArxApp::moduleName()
{
    static std::filesystem::path path;
    if (path.empty())
    {
        std::wstring buffer(MAX_PATH, 0);
        GetModuleFileName(_hdllInstance, buffer.data(), buffer.size());
        path = buffer.c_str();
    }
    return path;
}

void WxArxApp::initResources()
{
    initIcon();
    wxXmlResource::Get()->InitAllHandlers();
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::current_path(WxArxApp::modulePath());
    wxXmlResource::Get()->Load("..\\..\\..\\..\\Resources\\wxg_dlg_inserttable.xrc");
    wxXmlResource::Get()->Load("..\\..\\..\\..\\Resources\\WxBlockPanel.xrc");
    std::filesystem::current_path(currentPath);
}

void WxArxApp::initIcon()
{
#if defined(_BRXTARGET)
    _wxIcon.CreateFromHICON(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(31233)));
#elif defined(_ZRXTARGET)
    _wxIcon.CreateFromHICON(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(20001)));
#elif defined(_GRXTARGET)
    _wxIcon.CreateFromHICON(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(1017)));
#elif defined(_ARXTARGET)
    auto main = CWnd::FromHandle(adsw_acadMainWnd());
    if (main != nullptr)
        _wxIcon.CreateFromHICON(main->GetIcon(TRUE));
#endif
}

const wxIcon& WxArxApp::getWxIcon() const
{
    return _wxIcon;
}

wxDECLARE_APP(WxApp);
wxIMPLEMENT_APP_NO_MAIN(WxApp);

