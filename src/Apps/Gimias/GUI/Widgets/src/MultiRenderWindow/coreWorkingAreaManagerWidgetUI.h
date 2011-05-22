// -*- C++ -*- generated by wxGlade 0.6.3 on Fri Aug 27 15:06:19 2010

#include <wx/wx.h>
#include <wx/image.h>

#ifndef COREWORKINGAREAMANAGERWIDGETUI_H
#define COREWORKINGAREAMANAGERWIDGETUI_H

// begin wxGlade: ::dependencies
// end wxGlade

// begin wxGlade: ::extracode
#include "wxID.h"

#define wxID_BTN_NEW wxID( "wxID_BTN_NEW" )
#define wxID_BTN_SAVE wxID( "wxID_BTN_SAVE" )
#define wxID_BTN_DELETE wxID( "wxID_BTN_DELETE" )
#define wxID_BTN_RENAME wxID( "wxID_BTN_RENAME" )
#define wxID_BTN_CONFIGURE wxID( "wxID_BTN_CONFIGURE" )


// end wxGlade


class coreWorkingAreaManagerWidgetUI: public wxScrolledWindow {
public:
    // begin wxGlade: coreWorkingAreaManagerWidgetUI::ids
    // end wxGlade

    coreWorkingAreaManagerWidgetUI(wxWindow* parent, int id, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=0);

private:
    // begin wxGlade: coreWorkingAreaManagerWidgetUI::methods
    void set_properties();
    void do_layout();
    // end wxGlade

protected:
    // begin wxGlade: coreWorkingAreaManagerWidgetUI::attributes
    wxStaticBox* sizer_3_staticbox;
    wxStaticBox* ManageWorkingAreas_staticbox;
    wxListBox* m_List;
    wxButton* m_btnNew;
    wxButton* m_btnRename;
    wxButton* m_btnSave;
    wxButton* m_btnDelete;
    // end wxGlade

    DECLARE_EVENT_TABLE();

public:
    virtual void OnSelectedWorkingArea(wxCommandEvent &event); // wxGlade: <event_handler>
    virtual void OnNew(wxCommandEvent &event); // wxGlade: <event_handler>
    virtual void OnRename(wxCommandEvent &event); // wxGlade: <event_handler>
    virtual void OnSave(wxCommandEvent &event); // wxGlade: <event_handler>
    virtual void OnDelete(wxCommandEvent &event); // wxGlade: <event_handler>
}; // wxGlade: end class


#endif // COREWORKINGAREAMANAGERWIDGETUI_H
