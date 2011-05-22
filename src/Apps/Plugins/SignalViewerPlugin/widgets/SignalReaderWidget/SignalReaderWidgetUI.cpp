// -*- C++ -*- generated by wxGlade 0.6.3 on Tue Jun 22 08:59:17 2010

#include "SignalReaderWidgetUI.h"

// begin wxGlade: ::extracode

// end wxGlade


SignalReaderWidgetUI::SignalReaderWidgetUI(wxWindow* parent, int id, const wxPoint& pos, const wxSize& size, long style):
    wxPanel(parent, id, pos, size, wxTAB_TRAVERSAL)
{
    // begin wxGlade: SignalReaderWidgetUI::SignalReaderWidgetUI
    sizer_4_staticbox = new wxStaticBox(this, -1, wxT("Subsampling"));
    sizer_3_staticbox = new wxStaticBox(this, -1, wxT("Properties"));
    m_PropertiesWidget = new Core::Widgets::NumericDataWidget(this, wxID_ANY);
    label_1 = new wxStaticText(this, wxID_ANY, wxT("Factor"));
    m_SpinFactor = new wxSpinCtrl(this, wxID_SPIN_FACTOR, wxT("1"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 100);
    label_2 = new wxStaticText(this, wxID_ANY, wxT("Output sample rate"));
    m_txtOutputFreq = new wxTextCtrl(this, wxID_OUTPUT_FREQ, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    label_2_copy = new wxStaticText(this, wxID_ANY, wxT("Output size (Mb)"));
    m_txtOutputSize = new wxTextCtrl(this, wxID_OUTPUT_SIZE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);

    set_properties();
    do_layout();
    // end wxGlade
}


BEGIN_EVENT_TABLE(SignalReaderWidgetUI, wxPanel)
    // begin wxGlade: SignalReaderWidgetUI::event_table
    EVT_SPINCTRL(wxID_SPIN_FACTOR, SignalReaderWidgetUI::OnSpinFactor)
    // end wxGlade
END_EVENT_TABLE();


void SignalReaderWidgetUI::OnSpinFactor(wxSpinEvent &event)
{
    event.Skip();
    wxLogDebug(wxT("Event handler (SignalReaderWidgetUI::OnSpinFactor) not implemented yet")); //notify the user that he hasn't implemented the event handler yet
}


// wxGlade: add SignalReaderWidgetUI event handlers


void SignalReaderWidgetUI::set_properties()
{
    // begin wxGlade: SignalReaderWidgetUI::set_properties
    // end wxGlade
}


void SignalReaderWidgetUI::do_layout()
{
    // begin wxGlade: SignalReaderWidgetUI::do_layout
    wxBoxSizer* sizer_1 = new wxBoxSizer(wxVERTICAL);
    wxStaticBoxSizer* sizer_4 = new wxStaticBoxSizer(sizer_4_staticbox, wxVERTICAL);
    wxBoxSizer* sizer_6_copy = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_6 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_5 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticBoxSizer* sizer_3 = new wxStaticBoxSizer(sizer_3_staticbox, wxHORIZONTAL);
    sizer_3->Add(m_PropertiesWidget, 1, wxEXPAND, 0);
    sizer_1->Add(sizer_3, 1, wxALL|wxEXPAND, 5);
    sizer_5->Add(label_1, 1, 0, 0);
    sizer_5->Add(m_SpinFactor, 1, 0, 0);
    sizer_4->Add(sizer_5, 1, wxALL|wxEXPAND, 5);
    sizer_6->Add(label_2, 1, 0, 0);
    sizer_6->Add(m_txtOutputFreq, 1, 0, 0);
    sizer_4->Add(sizer_6, 1, wxALL|wxEXPAND, 5);
    sizer_6_copy->Add(label_2_copy, 1, 0, 0);
    sizer_6_copy->Add(m_txtOutputSize, 1, 0, 0);
    sizer_4->Add(sizer_6_copy, 1, wxALL|wxEXPAND, 5);
    sizer_1->Add(sizer_4, 0, wxALL|wxEXPAND, 5);
    SetSizer(sizer_1);
    sizer_1->Fit(this);
    // end wxGlade
}

