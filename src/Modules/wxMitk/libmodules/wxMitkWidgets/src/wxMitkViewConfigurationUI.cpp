// -*- C++ -*- generated by wxGlade 0.6.3 on Thu Mar 11 11:53:44 2010

#include "wxMitkViewConfigurationUI.h"

// begin wxGlade: ::extracode

// end wxGlade


wxMitkViewConfigurationUI::wxMitkViewConfigurationUI(wxWindow* parent, int id, const wxPoint& pos, const wxSize& size, long style):
    wxPanel(parent, id, pos, size, wxTAB_TRAVERSAL)
{
    // begin wxGlade: wxMitkViewConfigurationUI::wxMitkViewConfigurationUI
    Direction = new wxStaticText(this, wxID_ANY, wxT("Direction"));
    const wxString m_cmbDirection_choices[] = {
        wxT("Transversal"),
        wxT("Sagital"),
        wxT("Frontal")
    };
    m_cmbDirection = new wxComboBox(this, wxID_VIEW_CMB_DIRECTION, wxT(""), wxDefaultPosition, wxDefaultSize, 3, m_cmbDirection_choices, wxCB_DROPDOWN|wxCB_READONLY);
    m_chkFlip = new wxCheckBox(this, wxID_VIEW_CHK_FLIP, wxT("Flip"));
    const wxString m_rdbxRotate_choices[] = {
        wxT("0�"),
        wxT("90�"),
        wxT("180�"),
        wxT("270�")
    };
    m_rdbxRotate = new wxRadioBox(this, wxID_RDBX_ROTATE, wxT("Rotate"), wxDefaultPosition, wxDefaultSize, 4, m_rdbxRotate_choices, 0, wxRA_SPECIFY_ROWS);

    set_properties();
    do_layout();
    // end wxGlade
}


BEGIN_EVENT_TABLE(wxMitkViewConfigurationUI, wxPanel)
    // begin wxGlade: wxMitkViewConfigurationUI::event_table
    EVT_COMBOBOX(wxID_VIEW_CMB_DIRECTION, wxMitkViewConfigurationUI::OnDirection)
    EVT_CHECKBOX(wxID_VIEW_CHK_FLIP, wxMitkViewConfigurationUI::OnFlip)
    EVT_RADIOBOX(wxID_RDBX_ROTATE, wxMitkViewConfigurationUI::OnRotate)
    // end wxGlade
END_EVENT_TABLE();


void wxMitkViewConfigurationUI::OnDirection(wxCommandEvent &event)
{
    event.Skip();
    wxLogDebug(wxT("Event handler (wxMitkViewConfigurationUI::OnDirection) not implemented yet")); //notify the user that he hasn't implemented the event handler yet
}


void wxMitkViewConfigurationUI::OnFlip(wxCommandEvent &event)
{
    event.Skip();
    wxLogDebug(wxT("Event handler (wxMitkViewConfigurationUI::OnFlip) not implemented yet")); //notify the user that he hasn't implemented the event handler yet
}


void wxMitkViewConfigurationUI::OnRotate(wxCommandEvent &event)
{
    event.Skip();
    wxLogDebug(wxT("Event handler (wxMitkViewConfigurationUI::OnRotate) not implemented yet")); //notify the user that he hasn't implemented the event handler yet
}


// wxGlade: add wxMitkViewConfigurationUI event handlers


void wxMitkViewConfigurationUI::set_properties()
{
    // begin wxGlade: wxMitkViewConfigurationUI::set_properties
    SetSize(wxSize(268, 282));
    m_cmbDirection->SetSelection(0);
    m_rdbxRotate->SetSelection(0);
    // end wxGlade
}


void wxMitkViewConfigurationUI::do_layout()
{
    // begin wxGlade: wxMitkViewConfigurationUI::do_layout
    wxBoxSizer* sizer_1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_2 = new wxBoxSizer(wxHORIZONTAL);
    sizer_2->Add(Direction, 1, wxEXPAND, 0);
    sizer_2->Add(m_cmbDirection, 1, wxEXPAND, 0);
    sizer_1->Add(sizer_2, 0, wxALL|wxEXPAND, 5);
    sizer_1->Add(m_chkFlip, 0, wxALL|wxEXPAND, 5);
    sizer_1->Add(m_rdbxRotate, 0, wxALL|wxEXPAND, 5);
    SetSizer(sizer_1);
    // end wxGlade
}

