#pragma once

//------------------------------------------------------------------------------------------------
//  this is AutoCAD's main frame
class ArxTopLevelWindow : public wxTopLevelWindow
{
public:
    ArxTopLevelWindow();
    virtual ~ArxTopLevelWindow() override = default;
};

//------------------------------------------------------------------------------------------------
//  WxApp
class WxApp : public non_copyable_movable<WxApp>, public wxApp
{
public:
    virtual bool    OnInit() override;
    virtual int     OnExit() override;
    virtual void    WakeUpIdle() override;
    static bool     initWxApp();
    static bool     uninitWxApp();
};

//------------------------------------------------------------------------------------------------
//  wxArxApp
class WxArxApp : non_copyable_movable<WxArxApp>
{
public:
    void                initResources();
    void                initIcon();
    const wxIcon&       getWxIcon() const;
    static WxArxApp&    instance();
    static bool         init();
    static bool         uninit();
    static const std::filesystem::path& modulePath();
    static const std::filesystem::path& moduleName();
private:
    wxIcon _wxIcon;
};