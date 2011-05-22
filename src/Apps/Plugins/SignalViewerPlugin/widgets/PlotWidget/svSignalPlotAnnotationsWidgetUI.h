// -*- C++ -*- generated by wxGlade 0.6.3 on Tue Jan 26 14:18:44 2010

#include <wx/wx.h>
#include <wx/image.h>

#ifndef SVSIGNALPLOTANNOTATIONSWIDGETUI_H
#define SVSIGNALPLOTANNOTATIONSWIDGETUI_H

// begin wxGlade: ::dependencies
// end wxGlade

// begin wxGlade: ::extracode

// end wxGlade


class svSignalPlotAnnotationsWidgetUI: public wxPanel {
public:
    // begin wxGlade: svSignalPlotAnnotationsWidgetUI::ids
    // end wxGlade

    svSignalPlotAnnotationsWidgetUI(wxWindow* parent, int id, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=0);

private:
    // begin wxGlade: svSignalPlotAnnotationsWidgetUI::methods
    void set_properties();
    void do_layout();
    // end wxGlade

protected:
    // begin wxGlade: svSignalPlotAnnotationsWidgetUI::attributes
    wxStaticBox* sizer_1_staticbox;
    wxStaticBox* sizer_5_staticbox;
    wxListBox* m_listBoxAnnotations;
    wxStaticText* label_2;
    wxComboBox* m_cmbType;
    wxStaticText* label_3;
    wxTextCtrl* m_txtDuration;
    wxButton* button_1;
    // end wxGlade

    DECLARE_EVENT_TABLE();

public:
    virtual void OnSelectedAnnotation(wxCommandEvent &event); // wxGlade: <event_handler>
    virtual void OnComboSelected(wxCommandEvent &event); // wxGlade: <event_handler>
    virtual void OnDuration(wxCommandEvent &event); // wxGlade: <event_handler>
    virtual void OnRemoveButton(wxCommandEvent &event); // wxGlade: <event_handler>
}; // wxGlade: end class


#endif // SVSIGNALPLOTANNOTATIONSWIDGETUI_H
