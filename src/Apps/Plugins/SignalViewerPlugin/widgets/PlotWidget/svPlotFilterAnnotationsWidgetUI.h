// -*- C++ -*- generated by wxGlade 0.6.3 on Wed Jan 20 14:28:14 2010

#include <wx/wx.h>
#include <wx/image.h>

#ifndef SVPLOTFILTERANNOTATIONSWIDGETUI_H
#define SVPLOTFILTERANNOTATIONSWIDGETUI_H

// begin wxGlade: ::dependencies
#include <wx/treectrl.h>
// end wxGlade

// begin wxGlade: ::extracode
#define wxID_PLOT_FILTER_ANNOTATIONS_TREE wxID( "wxID_PLOT_FILTER_ANNOTATIONS_TREE" )
// end wxGlade


class svPlotFilterAnnotationsWidgetUI: public wxScrolledWindow {
public:
    // begin wxGlade: svPlotFilterAnnotationsWidgetUI::ids
    // end wxGlade

    svPlotFilterAnnotationsWidgetUI(wxWindow* parent, int id, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=0);

private:
    // begin wxGlade: svPlotFilterAnnotationsWidgetUI::methods
    void set_properties();
    void do_layout();
    // end wxGlade

protected:
    // begin wxGlade: svPlotFilterAnnotationsWidgetUI::attributes
    wxStaticBox* sizer_1_staticbox;
    wxTreeCtrl* m_TreeCtrl;
    // end wxGlade
}; // wxGlade: end class


#endif // SVPLOTFILTERANNOTATIONSWIDGETUI_H