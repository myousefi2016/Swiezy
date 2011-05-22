// -*- C++ -*- generated by wxGlade 0.6.3 on Tue Apr 27 10:34:16 2010

#include <wx/wx.h>
#include <wx/image.h>

#ifndef SVCONFIGURATIONWIDGETUI_H
#define SVCONFIGURATIONWIDGETUI_H

// begin wxGlade: ::dependencies
// end wxGlade

// begin wxGlade: ::extracode
#define wxID_SIGNAL_OFFSET wxID("wxID_SIGNAL_OFFSET")
#define wxID_SIGNAL_WINDOW_SIZE wxID("wxID_SIGNAL_WINDOW_SIZE")
// end wxGlade


class svConfigurationWidgetUI: public wxPanel {
public:
    // begin wxGlade: svConfigurationWidgetUI::ids
    // end wxGlade

    svConfigurationWidgetUI(wxWindow* parent, int id, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=0);

private:
    // begin wxGlade: svConfigurationWidgetUI::methods
    void set_properties();
    void do_layout();
    // end wxGlade

protected:
    // begin wxGlade: svConfigurationWidgetUI::attributes
    wxStaticBox* sizer_1_staticbox;
    wxStaticText* label_2;
    wxTextCtrl* m_txtOffset;
    wxStaticText* label_3;
    wxTextCtrl* m_txtSize;
    // end wxGlade

    DECLARE_EVENT_TABLE();

public:
    virtual void OnOffset(wxCommandEvent &event); // wxGlade: <event_handler>
    virtual void OnSize(wxCommandEvent &event); // wxGlade: <event_handler>
}; // wxGlade: end class


#endif // SVCONFIGURATIONWIDGETUI_H
