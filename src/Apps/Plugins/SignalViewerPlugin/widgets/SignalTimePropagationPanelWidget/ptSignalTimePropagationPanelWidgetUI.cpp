// -*- C++ -*- generated by wxGlade 0.6.3 on Mon May 03 18:02:30 2010

#include "ptSignalTimePropagationPanelWidgetUI.h"

// begin wxGlade: ::extracode

// end wxGlade


ptSignalTimePropagationPanelWidgetUI::ptSignalTimePropagationPanelWidgetUI(wxWindow* parent, int id, const wxPoint& pos, const wxSize& size, long style):
    wxPanel(parent, id, pos, size, wxTAB_TRAVERSAL)
{
    // begin wxGlade: ptSignalTimePropagationPanelWidgetUI::ptSignalTimePropagationPanelWidgetUI
    label_1 = new wxStaticText(this, wxID_ANY, wxT("Markers per scan"));
    m_txtMarkersPerScan = new wxTextCtrl(this, wxID_txtMarkersPerScan, wxT("1"));
    m_btnSignalTimePropagation = new wxButton(this, wxID_btnSignalTimePropagation, wxT("Propagate Time"));

    set_properties();
    do_layout();
    // end wxGlade
}


BEGIN_EVENT_TABLE(ptSignalTimePropagationPanelWidgetUI, wxPanel)
    // begin wxGlade: ptSignalTimePropagationPanelWidgetUI::event_table
    EVT_TEXT(wxID_txtMarkersPerScan, ptSignalTimePropagationPanelWidgetUI::OnMarkersPerScan)
    EVT_BUTTON(wxID_btnSignalTimePropagation, ptSignalTimePropagationPanelWidgetUI::OnButtonSignalTimePropagation)
    // end wxGlade
END_EVENT_TABLE();


void ptSignalTimePropagationPanelWidgetUI::OnMarkersPerScan(wxCommandEvent &event)
{
    event.Skip();
    wxLogDebug(wxT("Event handler (ptSignalTimePropagationPanelWidgetUI::OnMarkersPerScan) not implemented yet")); //notify the user that he hasn't implemented the event handler yet
}


void ptSignalTimePropagationPanelWidgetUI::OnButtonSignalTimePropagation(wxCommandEvent &event)
{
    event.Skip();
    wxLogDebug(wxT("Event handler (ptSignalTimePropagationPanelWidgetUI::OnButtonSignalTimePropagation) not implemented yet")); //notify the user that he hasn't implemented the event handler yet
}


// wxGlade: add ptSignalTimePropagationPanelWidgetUI event handlers


void ptSignalTimePropagationPanelWidgetUI::set_properties()
{
    // begin wxGlade: ptSignalTimePropagationPanelWidgetUI::set_properties
    // end wxGlade
}


void ptSignalTimePropagationPanelWidgetUI::do_layout()
{
    // begin wxGlade: ptSignalTimePropagationPanelWidgetUI::do_layout
    wxBoxSizer* GlobalSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_2 = new wxBoxSizer(wxHORIZONTAL);
    sizer_2->Add(label_1, 1, 0, 0);
    sizer_2->Add(m_txtMarkersPerScan, 0, 0, 0);
    sizer_1->Add(sizer_2, 0, wxALL|wxEXPAND, 5);
    sizer_1->Add(m_btnSignalTimePropagation, 0, wxALL|wxALIGN_RIGHT, 5);
    GlobalSizer->Add(sizer_1, 1, wxEXPAND, 0);
    SetSizer(GlobalSizer);
    GlobalSizer->Fit(this);
    // end wxGlade
}

