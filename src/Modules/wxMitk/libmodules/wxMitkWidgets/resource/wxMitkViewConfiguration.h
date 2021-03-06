// -*- C++ -*- generated by wxGlade 0.6.3 on Sun Jan 10 18:38:30 2010

#include <wx/wx.h>
#include <wx/image.h>

#ifndef WXMITKVIEWCONFIGURATION_H
#define WXMITKVIEWCONFIGURATION_H

// begin wxGlade: ::dependencies
// end wxGlade

// begin wxGlade: ::extracode

// end wxGlade


class wxMitkViewConfiguration: public wxPanel {
public:
    // begin wxGlade: wxMitkViewConfiguration::ids
    // end wxGlade

    wxMitkViewConfiguration(wxWindow* parent, int id, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=0);

private:
    // begin wxGlade: wxMitkViewConfiguration::methods
    void set_properties();
    void do_layout();
    // end wxGlade

protected:
    // begin wxGlade: wxMitkViewConfiguration::attributes
    wxStaticText* Direction;
    wxComboBox* m_cmbDirection;
    wxCheckBox* m_chkFlip;
    wxRadioBox* m_rdbxRotate;
    // end wxGlade
}; // wxGlade: end class


#endif // WXMITKVIEWCONFIGURATION_H
