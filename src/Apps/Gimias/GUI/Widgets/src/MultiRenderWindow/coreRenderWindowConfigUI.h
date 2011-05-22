// -*- C++ -*- generated by wxGlade 0.6.3 on Thu Nov 11 08:30:08 2010

#include <wx/wx.h>
#include <wx/image.h>

#ifndef CORERENDERWINDOWCONFIGUI_H
#define CORERENDERWINDOWCONFIGUI_H

// begin wxGlade: ::dependencies
// end wxGlade

// begin wxGlade: ::extracode
#include "wxID.h"

#define wxID_BTN_ADD_COL_VIEW wxID( "wxID_BTN_ADD_COL_VIEW" )
#define wxID_BTN_ADD_ROW_VIEW wxID( "wxID_BTN_ADD_ROW_VIEW" )

#define wxID_BTN_REMOVE_VIEW wxID( "wxID_BTN_REMOVE_VIEW" )

#define wxID_SPIN_CTRL_ROW wxID( "wxID_SPIN_CTRL_ROW" )
#define wxID_SPIN_CTRL_LAYER wxID( "wxID_SPIN_CTRL_LAYER" )


// end wxGlade


class coreRenderWindowConfigUI: public wxScrolledWindow {
public:
    // begin wxGlade: coreRenderWindowConfigUI::ids
    // end wxGlade

    coreRenderWindowConfigUI(wxWindow* parent, int id, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=0);

private:
    // begin wxGlade: coreRenderWindowConfigUI::methods
    void set_properties();
    void do_layout();
    // end wxGlade

protected:
    // begin wxGlade: coreRenderWindowConfigUI::attributes
    wxStaticBox* ManageViews_staticbox;
    wxComboBox* m_CmbNewView;
    wxButton* m_btnAddColView;
    wxButton* m_btnAddRowView;
    wxButton* m_btnRemoveView;
    // end wxGlade

    DECLARE_EVENT_TABLE();

public:
    virtual void OnAddCol(wxCommandEvent &event); // wxGlade: <event_handler>
    virtual void OnAddRow(wxCommandEvent &event); // wxGlade: <event_handler>
    virtual void OnRemove(wxCommandEvent &event); // wxGlade: <event_handler>
}; // wxGlade: end class


#endif // CORERENDERWINDOWCONFIGUI_H
