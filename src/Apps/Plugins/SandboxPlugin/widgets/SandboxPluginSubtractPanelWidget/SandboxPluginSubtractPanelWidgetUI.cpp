// -*- C++ -*- generated by wxGlade 0.6.3 on Fri Oct 24 09:55:28 2008

#include "SandboxPluginSubtractPanelWidgetUI.h"

// begin wxGlade: ::extracode

// end wxGlade


SandboxPluginSubtractPanelWidgetUI::SandboxPluginSubtractPanelWidgetUI(wxWindow* parent, int id, const wxPoint& pos, const wxSize& size, long style):
    wxScrolledWindow(parent, id, pos, size, wxTAB_TRAVERSAL)
{
    // begin wxGlade: SandboxPluginSubtractPanelWidgetUI::SandboxPluginSubtractPanelWidgetUI
    sizer_1_staticbox = new wxStaticBox(this, -1, wxT("Subtraction"));
    m_btnSubtract = new wxButton(this, wxID_BTN_SUBTRACT, wxT("Apply"));

    set_properties();
    do_layout();
    // end wxGlade
}


void SandboxPluginSubtractPanelWidgetUI::set_properties()
{
    // begin wxGlade: SandboxPluginSubtractPanelWidgetUI::set_properties
    SetScrollRate(10, 10);
    // end wxGlade
}


void SandboxPluginSubtractPanelWidgetUI::do_layout()
{
    // begin wxGlade: SandboxPluginSubtractPanelWidgetUI::do_layout
    wxBoxSizer* GlobalSizer = new wxBoxSizer(wxVERTICAL);
    wxStaticBoxSizer* sizer_1 = new wxStaticBoxSizer(sizer_1_staticbox, wxVERTICAL);
    sizer_1->Add(m_btnSubtract, 0, wxALL|wxEXPAND, 5);
    GlobalSizer->Add(sizer_1, 0, wxEXPAND, 0);
    SetSizer(GlobalSizer);
    GlobalSizer->Fit(this);
    // end wxGlade
}
