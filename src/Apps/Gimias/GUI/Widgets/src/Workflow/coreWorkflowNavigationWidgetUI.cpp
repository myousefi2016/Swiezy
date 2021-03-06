// -*- C++ -*- generated by wxGlade 0.6.3 on Fri Oct 01 11:22:09 2010

#include "coreWorkflowNavigationWidgetUI.h"

// begin wxGlade: ::extracode

// end wxGlade


coreWorkflowNavigationWidgetUI::coreWorkflowNavigationWidgetUI(wxWindow* parent, int id, const wxPoint& pos, const wxSize& size, long style):
    wxScrolledWindow(parent, id, pos, size, wxTAB_TRAVERSAL)
{
    // begin wxGlade: coreWorkflowNavigationWidgetUI::coreWorkflowNavigationWidgetUI
    sizer_3_staticbox = new wxStaticBox(this, -1, wxEmptyString);
    m_bmpBack = new wxBitmapButton(this, wxID_BACK, wxNullBitmap);
    m_bmpAdd = new wxBitmapButton(this, wxID_ADD , wxNullBitmap);
    m_bmpNext = new wxBitmapButton(this, wxID_NEXT , wxNullBitmap);
    m_lblCaption = new wxStaticText(this, wxID_ANY, wxT("None"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
    m_EmptyPanel = new wxPanel(this, wxID_ANY);

    set_properties();
    do_layout();
    // end wxGlade
}


BEGIN_EVENT_TABLE(coreWorkflowNavigationWidgetUI, wxScrolledWindow)
    // begin wxGlade: coreWorkflowNavigationWidgetUI::event_table
    EVT_BUTTON(wxID_BACK, coreWorkflowNavigationWidgetUI::OnBack)
    EVT_BUTTON(wxID_ADD , coreWorkflowNavigationWidgetUI::OnAdd)
    EVT_BUTTON(wxID_NEXT , coreWorkflowNavigationWidgetUI::OnNext)
    // end wxGlade
END_EVENT_TABLE();


void coreWorkflowNavigationWidgetUI::OnBack(wxCommandEvent &event)
{
    event.Skip();
    wxLogDebug(wxT("Event handler (coreWorkflowNavigationWidgetUI::OnBack) not implemented yet")); //notify the user that he hasn't implemented the event handler yet
}


void coreWorkflowNavigationWidgetUI::OnAdd(wxCommandEvent &event)
{
    event.Skip();
    wxLogDebug(wxT("Event handler (coreWorkflowNavigationWidgetUI::OnAdd) not implemented yet")); //notify the user that he hasn't implemented the event handler yet
}


void coreWorkflowNavigationWidgetUI::OnNext(wxCommandEvent &event)
{
    event.Skip();
    wxLogDebug(wxT("Event handler (coreWorkflowNavigationWidgetUI::OnNext) not implemented yet")); //notify the user that he hasn't implemented the event handler yet
}


// wxGlade: add coreWorkflowNavigationWidgetUI event handlers


void coreWorkflowNavigationWidgetUI::set_properties()
{
    // begin wxGlade: coreWorkflowNavigationWidgetUI::set_properties
    SetSize(wxSize(245, 273));
    SetScrollRate(10, 10);
    m_bmpBack->SetMinSize(wxSize(32, 32));
    m_bmpAdd->SetMinSize(wxSize(32, 32));
    m_bmpNext->SetMinSize(wxSize(32, 32));
    m_lblCaption->SetMinSize(wxSize(-1, 20));
    m_lblCaption->SetFont(wxFont(9, wxDEFAULT, wxNORMAL, wxBOLD, 0, wxT("")));
    m_lblCaption->SetWindowStyle(wxALIGN_CENTRE | wxBORDER_SUNKEN);
    // end wxGlade
}


void coreWorkflowNavigationWidgetUI::do_layout()
{
    // begin wxGlade: coreWorkflowNavigationWidgetUI::do_layout
    wxBoxSizer* sizer_1 = new wxBoxSizer(wxVERTICAL);
    wxStaticBoxSizer* sizer_3 = new wxStaticBoxSizer(sizer_3_staticbox, wxVERTICAL);
    wxBoxSizer* sizer_2 = new wxBoxSizer(wxHORIZONTAL);
    sizer_2->Add(m_bmpBack, 1, wxEXPAND, 0);
    sizer_2->Add(m_bmpAdd, 1, wxEXPAND, 0);
    sizer_2->Add(m_bmpNext, 1, wxEXPAND, 0);
    sizer_1->Add(sizer_2, 0, wxALL|wxEXPAND, 5);
    sizer_1->Add(m_lblCaption, 0, wxALL|wxEXPAND, 5);
    sizer_3->Add(m_EmptyPanel, 1, wxEXPAND, 5);
    sizer_1->Add(sizer_3, 1, wxALL|wxEXPAND, 5);
    SetSizer(sizer_1);
    // end wxGlade
}

