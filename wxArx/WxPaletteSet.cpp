#include "StdAfx.h"
#include "resource.h"
#include "WxPaletteSet.h"

//-----------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(WxPaletteSet, CAdUiPaletteSet)

BEGIN_MESSAGE_MAP(WxPaletteSet, CAdUiPaletteSet)
    ON_WM_CREATE()
END_MESSAGE_MAP()

WxPaletteSet::WxPaletteSet()
    : m_paletteName(_T("WxPaletteSet"))
{
}

bool WxPaletteSet::create()
{
    constexpr auto paletteStyleFlags = PSS_AUTO_ROLLUP | PSS_PROPERTIES_MENU | PSS_CLOSE_BUTTON | PSS_SNAP;
    if (m_created)
        return true;
    CAcModuleResourceOverride resourceOverride;
    CRect rect(0, 0, 275, 500);
    this->Create(
        m_paletteName,
        WS_OVERLAPPED | WS_DLGFRAME,
        rect,
        acedGetAcadFrame(),
        paletteStyleFlags
    );
    this->EnableDocking(CBRS_ALIGN_ANY);
    this->SetName(m_paletteName);
    createChildren();
    m_created = true;
    return m_created;
}

void WxPaletteSet::createChildren()
{
    for (auto& child : m_children)
    {
        if (child->Create(WS_CHILD | WS_VISIBLE, child->GetName(), this) == FALSE)
            acutPrintf(_T("Failed to Create palette: "));
        if (this->AddPalette(child) == -1)
            acutPrintf(_T("Failed to add palette: "));
    }
}

int WxPaletteSet::add(CAdUiPalette* palette)
{
    if (palette != nullptr)
    {
        m_children.push_back(palette);
        return m_children.size() - 1;
    }
    return -1;
}

void WxPaletteSet::setVisible(bool show)
{
    if (create())
    {
        this->RestoreControlBar();
        acedGetAcadFrame()->ShowControlBar(this, show ? TRUE : FALSE, FALSE);
    }
}

int WxPaletteSet::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CAdUiPaletteSet::OnCreate(lpCreateStruct) == -1)
        return -1;
    return 0;
}

void WxPaletteSet::GetMinimumSize(CSize& size) 
{
    CAdUiPaletteSet::GetMinimumSize(size);
}

void WxPaletteSet::GetMaximumSize(CSize& size) 
{
    CAdUiPaletteSet::GetMaximumSize(size);
}

//---------------------------------------------------------------------
// WxBlockPalette
IMPLEMENT_DYNAMIC(WxBlockPalette, CAdUiPalette)

BEGIN_MESSAGE_MAP(WxBlockPalette, CAdUiPalette)
    ON_WM_CREATE()
    ON_WM_SIZE()
END_MESSAGE_MAP()

WxBlockPalette::WxBlockPalette()
{
    SetName(_T("WxBlockPalette"));
}

int WxBlockPalette::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    CAcModuleResourceOverride resourceOverride;
    auto mcfParent = this->GetParent();
    if (mcfParent == nullptr)
        return -1;

    // create a wxWidgets wrapper of this window
    m_thiswin = new wxPanel();
    m_thiswin->SetHWND((WXHWND)this->GetSafeHwnd());
    m_thiswin->AdoptAttributesFromHWND();

    // create WxBlockPanel derived from wxPanel;
    m_panel = new WxBlockPanel();
    if (!m_panel->Create(m_thiswin))
        return -1;
    return 0;
}

void WxBlockPalette::OnSize(UINT nType, int cx, int cy)
{
    CAdUiPalette::OnSize(nType, cx, cy);
    CAcModuleResourceOverride resourceOverride;
    CRect rect;
    GetClientRect(rect);
    // forward size event
    m_panel->SetSize(rect.left, rect.top, rect.right, rect.bottom);
}

//-----------------------------------------------------------------------------
// WxBlockPanel
IMPLEMENT_DYNAMIC_CLASS(WxBlockPanel, wxPanel)

BEGIN_EVENT_TABLE(WxBlockPanel, wxPanel)
EVT_CHOICE(XRCID("ID_CHOICE"), WxBlockPanel::OnChoiceSelected)
EVT_BUTTON(XRCID("ID_BUTTON"), WxBlockPanel::OnButtonClick)
EVT_LIST_ITEM_SELECTED(XRCID("ID_LISTCTRL"), WxBlockPanel::OnListctrlSelected)
EVT_LIST_BEGIN_DRAG(XRCID("ID_LISTCTRL"), WxBlockPanel::OnListctrlBeginDrag)
END_EVENT_TABLE()

bool WxBlockPanel::Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
{
    Init();
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    SetParent(parent);
    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
    return true;
}

void WxBlockPanel::Init()
{
    m_ID_STATIC_PREVIEW = NULL;
    m_ID_CHOICE = NULL;
    m_ID_BUTTON = NULL;
    m_ID_LISTCTRL = NULL;
}

void WxBlockPanel::CreateControls()
{
    // See WxArxApp::initResources()
    if (!wxXmlResource::Get()->LoadPanel(this, GetParent(), wxT("ID_BLOCKMAN")))
        acutPrintf(wxT("Missing wxXmlResource::Get()->Load() in OnInit()?"));
    m_ID_STATIC_PREVIEW = XRCCTRL(*this, "ID_STATIC_PREVIEW", wxStaticBitmap);
    m_ID_CHOICE = XRCCTRL(*this, "ID_CHOICE", wxChoice);
    m_ID_BUTTON = XRCCTRL(*this, "ID_BUTTON", wxButton);
    m_ID_LISTCTRL = XRCCTRL(*this, "ID_LISTCTRL", wxListCtrl);
    InitControls();
}

void WxBlockPanel::InitControls()
{
    wxArrayString choices;
    choices.Add(L"Option 1");
    choices.Add(L"Option 2");
    choices.Add(L"Option 3");
    m_ID_CHOICE->Append(choices);

    m_ID_LISTCTRL->InsertColumn(0, L"Column 0", wxLIST_FORMAT_LEFT, 100);
    m_ID_LISTCTRL->InsertColumn(1, L"Column 1", wxLIST_FORMAT_LEFT, 100);
    long index = m_ID_LISTCTRL->InsertItem(0, L"item 0, column 0");
    m_ID_LISTCTRL->SetItem(index, 1, L"item 0, column 1");

    index = m_ID_LISTCTRL->InsertItem(1, L"item 1, column 0");
    m_ID_LISTCTRL->SetItem(index, 1, L"item 1, column 1");
}

bool WxBlockPanel::ShowToolTips()
{
    return true;
}

void WxBlockPanel::OnListctrlSelected(wxListEvent& event)
{
    acutPrintf(_T("\nOnListctrlSelected"));
    event.Skip();
}

void WxBlockPanel::OnListctrlBeginDrag(wxListEvent& event)
{
    acutPrintf(_T("\nOnListctrlBeginDrag"));
    event.Skip();
}

void WxBlockPanel::OnChoiceSelected(wxCommandEvent& event)
{
    acutPrintf(_T("\nOnChoiceSelected"));
    event.Skip();
}

void WxBlockPanel::OnButtonClick(wxCommandEvent& event)
{
    acutPrintf(_T("\nOnButtonClick"));
    event.Skip();
}

