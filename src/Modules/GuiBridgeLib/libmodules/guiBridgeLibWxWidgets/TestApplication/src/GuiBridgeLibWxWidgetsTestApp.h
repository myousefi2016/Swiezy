// -*- C++ -*- generated by wxGlade 0.6.3 on Tue Mar 18 16:56:29 2008

#include <wx/wx.h>
#include <wx/image.h>
// begin wxGlade: ::dependencies
#include <wx/tglbtn.h>
// end wxGlade

#ifndef GUIBRIDGELIBWXWIDGETSTESTAPP_H
#define GUIBRIDGELIBWXWIDGETSTESTAPP_H

#include "gblWxBridgeLib.h"
#include "boost/shared_ptr.hpp"

// begin wxGlade: ::extracode
// end wxGlade


class MainFrame: public wxFrame {
public:
    // begin wxGlade: MainFrame::ids
    // end wxGlade

    MainFrame(wxWindow* parent, int id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE);

	void UpdateWidget();
	void TestBridgeEvent();

private:
    // begin wxGlade: MainFrame::methods
    void set_properties();
    void do_layout();
    // end wxGlade

protected:
    // begin wxGlade: MainFrame::attributes
    wxTextCtrl* text_ctrl_1;
    wxRadioButton* radio_btn_1;
    wxRadioButton* radio_btn_2;
    wxToggleButton* button_1;
    wxCheckBox* checkbox_1;
    wxChoice* choice_1;
    wxComboBox* combo_box_1;
    wxListBox* list_box_1;
    wxButton* btnTest;
    // end wxGlade

	//typedef boost::shared_ptr<gbl::wx::ConnectorOfWidgetChangesToSlotFunction> ConnectorOfWidgetChangesToSlotFunctionPtr;
	typedef gbl::wx::ConnectorOfWidgetChangesToSlotFunction* ConnectorOfWidgetChangesToSlotFunctionPtr;
	ConnectorOfWidgetChangesToSlotFunctionPtr m_Connector;

    DECLARE_EVENT_TABLE();
}; // wxGlade: end class


#endif // GUIBRIDGELIBWXWIDGETSTESTAPP_H