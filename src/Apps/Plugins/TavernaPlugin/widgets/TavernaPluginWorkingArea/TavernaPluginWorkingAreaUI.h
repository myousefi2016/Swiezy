// -*- C++ -*- generated by wxGlade 0.6.3 on Fri Jan 21 00:12:56 2011

#include <wx/wx.h>
#include <wx/image.h>

#ifndef TAVERNAPLUGINWORKINGAREAUI_H
#define TAVERNAPLUGINWORKINGAREAUI_H

// begin wxGlade: ::dependencies
// end wxGlade

// begin wxGlade: ::extracode

// end wxGlade


class TavernaPluginWorkingAreaUI: public wxScrolledWindow {
public:
    // begin wxGlade: TavernaPluginWorkingAreaUI::ids
    // end wxGlade

    TavernaPluginWorkingAreaUI(wxWindow* parent, int id, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=0);

private:
    // begin wxGlade: TavernaPluginWorkingAreaUI::methods
    void set_properties();
    void do_layout();
    // end wxGlade

protected:
    // begin wxGlade: TavernaPluginWorkingAreaUI::attributes
    wxStaticText* m_lblEmpty;
    // end wxGlade
}; // wxGlade: end class


#endif // TAVERNAPLUGINWORKINGAREAUI_H
