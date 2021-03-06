// -*- C++ -*- generated by wxGlade 0.6.3 on Mon Dec 14 14:28:54 2009

#include <wx/wx.h>
#include <wx/image.h>

#ifndef TavernaPluginWorkflowPanelWidgetUI_H
#define TavernaPluginWorkflowPanelWidgetUI_H

// begin wxGlade: ::dependencies
// end wxGlade

// begin wxGlade: ::extracode
#define wxID_BTN_Apply wxID("ApplyButton")
// end wxGlade


class TavernaPluginWorkflowPanelWidgetUI: public wxScrolledWindow {
public:
    // begin wxGlade: TavernaPluginWorkflowPanelWidgetUI::ids
    // end wxGlade

    TavernaPluginWorkflowPanelWidgetUI(wxWindow* parent, int id, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=0);

private:
    // begin wxGlade: TavernaPluginWorkflowPanelWidgetUI::methods
    void set_properties();
    void do_layout();
    // end wxGlade

protected:
    // begin wxGlade: TavernaPluginWorkflowPanelWidgetUI::attributes
    wxButton* m_btnApply;
    // end wxGlade

    DECLARE_EVENT_TABLE();

public:
    virtual void OnBtnApply(wxCommandEvent &event); // wxGlade: <event_handler>
}; // wxGlade: end class


#endif // TavernaPluginWorkflowPanelWidgetUI_H
