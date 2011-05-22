// -*- C++ -*- generated by wxGlade 0.6.3 on Tue Apr 27 08:20:49 2010

#include <wx/wx.h>
#include <wx/image.h>

#ifndef SVPLOTWIDGETUI_H
#define SVPLOTWIDGETUI_H

// begin wxGlade: ::dependencies
#include <wx/notebook.h>
// end wxGlade

// begin wxGlade: ::extracode
#define wxID_PLOTNOTEBOOK wxID("wxID_PLOTNOTEBOOK")

// end wxGlade


class svPlotWidgetUI: public wxPanel {
public:
    // begin wxGlade: svPlotWidgetUI::ids
    // end wxGlade

    svPlotWidgetUI(wxWindow* parent, int id, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=0);

private:
    // begin wxGlade: svPlotWidgetUI::methods
    void set_properties();
    void do_layout();
    // end wxGlade

protected:
    // begin wxGlade: svPlotWidgetUI::attributes
    wxPanel* ploteNotebookePane1;
    wxNotebook* m_plotNotebook;
    // end wxGlade

    DECLARE_EVENT_TABLE();

public:
    virtual void OnPageChanged(wxNotebookEvent &event); // wxGlade: <event_handler>
}; // wxGlade: end class


#endif // SVPLOTWIDGETUI_H
