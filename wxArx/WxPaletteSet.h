#pragma once

//-----------------------------------------------------------------------------
#include "adui.h"

#include "wx/combo.h"
#include "wx/listctrl.h"

class WxBlockPalette;
class WxBlockPanel;

//-----------------------------------------------------------------------------
// WxPaletteSet
class WxPaletteSet : public CAdUiPaletteSet {
    DECLARE_DYNCREATE(WxPaletteSet)

public:
    WxPaletteSet();
    virtual ~WxPaletteSet() override = default;

    bool                create();
    void                createChildren();
    int                 add(CAdUiPalette* palette);
    void                setVisible(bool show);

protected:
    virtual void GetMinimumSize(CSize& size);
    virtual void GetMaximumSize(CSize& size);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

    DECLARE_MESSAGE_MAP()

private:
    std::vector<CAdUiPalette*> m_children;
    CString m_paletteName; //GRX, can't set the name until created
    bool m_created = false;
};

//-----------------------------------------------------------------------------
// WxBlockPalette, WxBlockPanel is where we move to wxWidgets
class WxBlockPalette : public CAdUiPalette
{
    DECLARE_DYNAMIC(WxBlockPalette);

public:
    WxBlockPalette();
    virtual ~WxBlockPalette() override = default;
    DECLARE_MESSAGE_MAP();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);


private:
    WxBlockPanel* m_panel = nullptr;
    wxPanel* m_thiswin = nullptr;;
};


//-----------------------------------------------------------------------------
// WxBlockPanel, a child of WxBlockPalette
#define ID_BLOCKMAN -1
#define SYMBOL_WXBLOCKPANEL_STYLE wxTAB_TRAVERSAL
#define SYMBOL_WXBLOCKPANEL_TITLE _("BlockMan")
#define SYMBOL_WXBLOCKPANEL_IDNAME ID_BLOCKMAN
#define SYMBOL_WXBLOCKPANEL_SIZE wxSize(400, -1)
#define SYMBOL_WXBLOCKPANEL_POSITION wxDefaultPosition

class WxBlockPanel : public wxPanel
{
    DECLARE_DYNAMIC_CLASS(WxBlockPanel)
    DECLARE_EVENT_TABLE()

public:
    WxBlockPanel() = default;
    virtual ~WxBlockPanel() override = default;

    bool Create(
        wxWindow* parent, wxWindowID id = SYMBOL_WXBLOCKPANEL_IDNAME,
        const wxPoint& pos = SYMBOL_WXBLOCKPANEL_POSITION,
        const wxSize& size = SYMBOL_WXBLOCKPANEL_SIZE,
        long style = SYMBOL_WXBLOCKPANEL_STYLE);

protected:
    void Init();
    void CreateControls();
    void InitControls();
    void OnChoiceSelected(wxCommandEvent& event);
    void OnButtonClick(wxCommandEvent& event);
    void OnListctrlSelected(wxListEvent& event);
    void OnListctrlBeginDrag(wxListEvent& event);
    static bool ShowToolTips();

private:
    wxStaticBitmap* m_ID_STATIC_PREVIEW = nullptr;
    wxChoice* m_ID_CHOICE = nullptr;
    wxButton* m_ID_BUTTON = nullptr;
    wxListCtrl* m_ID_LISTCTRL = nullptr;
};