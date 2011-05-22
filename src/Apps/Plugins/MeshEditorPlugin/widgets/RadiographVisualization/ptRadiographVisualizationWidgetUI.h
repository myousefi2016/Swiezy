// -*- C++ -*- generated by wxGlade 0.6.3 on Wed Aug 26 17:55:39 2009

#include <wx/wx.h>
#include <wx/image.h>

#ifndef ptRadiographVisualizationWidgetUI_H
#define ptRadiographVisualizationWidgetUI_H

// begin wxGlade: ::dependencies
// end wxGlade

// begin wxGlade: ::extracode
#include "wxID.h"
#include "coreProcessingWidget.h"
#define wxID_BTN_SHOW wxID("wxID_BTN_SHOW")

// end wxGlade


class ptRadiographVisualizationWidgetUI: 
	public wxPanel,
	public Core::Widgets::ProcessingWidget {
public:
    // begin wxGlade: ptRadiographVisualizationWidgetUI::ids
    // end wxGlade

    ptRadiographVisualizationWidgetUI(wxWindow* parent, int id, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=0);

private:
    // begin wxGlade: ptRadiographVisualizationWidgetUI::methods
    void set_properties();
    void do_layout();
    // end wxGlade

protected:
    // begin wxGlade: ptRadiographVisualizationWidgetUI::attributes
    wxStaticText* m_lblParam1;
    wxTextCtrl* m_txtParam1;
   // CustomWidget* m_window;
    wxButton* m_btnProject;
    // end wxGlade

    DECLARE_EVENT_TABLE();

public:
    virtual void OnBtnShowProjection(wxCommandEvent &event); // wxGlade: <event_handler>
}; // wxGlade: end class


#endif // ptRadiographVisualizationWidgetUI_H
