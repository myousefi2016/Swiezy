// -*- C++ -*- generated by wxGlade 0.6.3 on Tue Jun 22 08:59:17 2010

#include <wx/wx.h>
#include <wx/image.h>

#ifndef SIGNALREADERWIDGETUI_H
#define SIGNALREADERWIDGETUI_H

// begin wxGlade: ::dependencies
#include <wx/spinctrl.h>
// end wxGlade

// begin wxGlade: ::extracode
#define wxID_LIST_PROPERTIES wxID("wxID_LIST_PROPERTIES")
#define wxID_SPIN_FACTOR wxID("wxID_SPIN_FACTOR")
#define wxID_OUTPUT_FREQ wxID("wxID_OUTPUT_FREQ")
#define wxID_OUTPUT_SIZE wxID("wxID_OUTPUT_SIZE")

#include "coreNumericDataWidget.h"

// end wxGlade


class SignalReaderWidgetUI: public wxPanel {
public:
    // begin wxGlade: SignalReaderWidgetUI::ids
    // end wxGlade

    SignalReaderWidgetUI(wxWindow* parent, int id, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=0);

private:
    // begin wxGlade: SignalReaderWidgetUI::methods
    void set_properties();
    void do_layout();
    // end wxGlade

protected:
    // begin wxGlade: SignalReaderWidgetUI::attributes
    wxStaticBox* sizer_4_staticbox;
    wxStaticBox* sizer_3_staticbox;
    Core::Widgets::NumericDataWidget* m_PropertiesWidget;
    wxStaticText* label_1;
    wxSpinCtrl* m_SpinFactor;
    wxStaticText* label_2;
    wxTextCtrl* m_txtOutputFreq;
    wxStaticText* label_2_copy;
    wxTextCtrl* m_txtOutputSize;
    // end wxGlade

    DECLARE_EVENT_TABLE();

public:
    virtual void OnSpinFactor(wxSpinEvent &event); // wxGlade: <event_handler>
}; // wxGlade: end class


#endif // SIGNALREADERWIDGETUI_H
