// -*- C++ -*- generated by wxGlade 0.6.3 on Thu Nov 11 13:16:44 2010

#include "CmguiPluginImageVisualPropsUI.h"

// begin wxGlade: ::extracode

// end wxGlade


CmguiPluginImageVisualPropsUI::CmguiPluginImageVisualPropsUI(wxWindow* parent, int id, const wxPoint& pos, const wxSize& size, long style):
    wxScrolledWindow(parent, id, pos, size, wxTAB_TRAVERSAL)
{
    // begin wxGlade: CmguiPluginImageVisualPropsUI::CmguiPluginImageVisualPropsUI
    m_Tree = new wxTreeCtrl(this, wxID_TREE, wxDefaultPosition, wxDefaultSize, wxTR_HAS_BUTTONS|wxTR_LINES_AT_ROOT|wxTR_DEFAULT_STYLE|wxSUNKEN_BORDER);
    m_btnShowAll = new wxButton(this, wxID_BTN_SHOW_ALL, wxT("Show all"));
    m_btnHideAll = new wxButton(this, wxID_BTN_HIDE_ALL, wxT("Hide all"));
    m_btnShowSelected = new wxToggleButton(this, wxID_BTN_SHOW_SELECTED, wxT("Show selected"));

    set_properties();
    do_layout();
    // end wxGlade
}


BEGIN_EVENT_TABLE(CmguiPluginImageVisualPropsUI, wxScrolledWindow)
    // begin wxGlade: CmguiPluginImageVisualPropsUI::event_table
    EVT_TREE_SEL_CHANGED(wxID_TREE, CmguiPluginImageVisualPropsUI::OnTreeSelChanged)
    EVT_BUTTON(wxID_BTN_SHOW_ALL, CmguiPluginImageVisualPropsUI::OnShowAll)
    EVT_BUTTON(wxID_BTN_HIDE_ALL, CmguiPluginImageVisualPropsUI::OnHideAll)
    EVT_TOGGLEBUTTON(wxID_BTN_SHOW_SELECTED, CmguiPluginImageVisualPropsUI::OnShowSelected)
    // end wxGlade
END_EVENT_TABLE();


void CmguiPluginImageVisualPropsUI::OnTreeSelChanged(wxTreeEvent &event)
{
    event.Skip();
    wxLogDebug(wxT("Event handler (CmguiPluginImageVisualPropsUI::OnTreeSelChanged) not implemented yet")); //notify the user that he hasn't implemented the event handler yet
}


void CmguiPluginImageVisualPropsUI::OnShowAll(wxCommandEvent &event)
{
    event.Skip();
    wxLogDebug(wxT("Event handler (CmguiPluginImageVisualPropsUI::OnShowAll) not implemented yet")); //notify the user that he hasn't implemented the event handler yet
}


void CmguiPluginImageVisualPropsUI::OnHideAll(wxCommandEvent &event)
{
    event.Skip();
    wxLogDebug(wxT("Event handler (CmguiPluginImageVisualPropsUI::OnHideAll) not implemented yet")); //notify the user that he hasn't implemented the event handler yet
}


void CmguiPluginImageVisualPropsUI::OnShowSelected(wxCommandEvent &event)
{
    event.Skip();
    wxLogDebug(wxT("Event handler (CmguiPluginImageVisualPropsUI::OnShowSelected) not implemented yet")); //notify the user that he hasn't implemented the event handler yet
}


// wxGlade: add CmguiPluginImageVisualPropsUI event handlers


void CmguiPluginImageVisualPropsUI::set_properties()
{
    // begin wxGlade: CmguiPluginImageVisualPropsUI::set_properties
    SetScrollRate(10, 10);
    // end wxGlade
}


void CmguiPluginImageVisualPropsUI::do_layout()
{
    // begin wxGlade: CmguiPluginImageVisualPropsUI::do_layout
    wxBoxSizer* GlobalSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_2 = new wxBoxSizer(wxHORIZONTAL);
    sizer_1->Add(m_Tree, 1, wxEXPAND, 0);
    sizer_2->Add(m_btnShowAll, 0, wxALL, 5);
    sizer_2->Add(m_btnHideAll, 0, wxALL, 5);
    sizer_2->Add(m_btnShowSelected, 0, wxALL, 5);
    sizer_1->Add(sizer_2, 0, wxEXPAND, 0);
    GlobalSizer->Add(sizer_1, 1, wxALL|wxEXPAND, 5);
    SetSizer(GlobalSizer);
    GlobalSizer->Fit(this);
    // end wxGlade
}

