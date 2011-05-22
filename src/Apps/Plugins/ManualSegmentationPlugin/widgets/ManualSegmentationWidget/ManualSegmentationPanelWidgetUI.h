// -*- C++ -*- generated by wxGlade 0.6.3 on Thu Jun 17 10:17:27 2010

#include <wx/wx.h>
#include <wx/image.h>

#ifndef MANUALSEGMENTATIONPANELWIDGETUI_H
#define MANUALSEGMENTATIONPANELWIDGETUI_H

// begin wxGlade: ::dependencies
#include <wx/tglbtn.h>
// end wxGlade

// begin wxGlade: ::extracode
#include "wxMitkColorSelectorControl.h"
#include "wxID.h"

#define wxID_BTN_MERGE_IMAGES wxID("CardiacManualSegmentationPanelWidgetUIBtnMergetImages")
#define wxID_COLOR_SELECTOR wxID("CardiacManualSegmentationPanelWidgetUIColorSelector")
#define wxID_LEVEL_SPINCTRL wxID("CardiacManualSegmentationPanelWidgetUILevelSpinCtrl")
#define wxID_BTN_EDITROI wxID("CardiacManualSegmentationPanelWidgetUIEditRoiBtn")
#define wxID_CHK_COLOR wxID("CardiacManualSegmentationPanelWidgetUIChkColor")
#define wxID_COMBO_LEVEL wxID("CardiacManualSegmentationPanelWidgetUIComboLevel")
#define wxID_COMBO_LUT wxID("CardiacManualSegmentationPanelWidgetUIComboLUT")
#define wxID_BTN_ADD wxID("CardiacManualSegmentationPanelWidgetUIBtnAdd")
#define wxID_BTN_PROPAGATE wxID("CardiacManualSegmentationPanelWidgetUIBtnPropagate")
#define wxID_BTN_UPDATEMEASURES wxID("CardiacManualSegmentationPanelWidgetUIBtnUpdateMeasures")
#define wxID_BTN_CREATESIGNAL wxID("CardiacManualSegmentationPanelWidgetUIBtnCreateSignal")
#define wxID_EnableInteraction wxID("wxID_EnableInteraction")
// end wxGlade


class ManualSegmentationPanelWidgetUI: public wxScrolledWindow {
public:
    // begin wxGlade: ManualSegmentationPanelWidgetUI::ids
    // end wxGlade

    ManualSegmentationPanelWidgetUI(wxWindow* parent, int id, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=0);

private:
    // begin wxGlade: ManualSegmentationPanelWidgetUI::methods
    void set_properties();
    void do_layout();
    // end wxGlade

protected:
    // begin wxGlade: ManualSegmentationPanelWidgetUI::attributes
    wxStaticBox* sizer_1_staticbox;
    wxStaticBox* sizer_4_staticbox;
    wxStaticBox* sizer_2_staticbox;
    wxTextCtrl* m_txtAdd;
    wxButton* m_btnAdd;
    wxComboBox* m_ComboLevel;
    mitk::wxMitkColorSelectorControl* m_roiColorSelector;
    wxCheckBox* m_chkEraseOnlySelectedColor;
    wxComboBox* m_ComboLUT;
    wxToggleButton* m_btnEnableInteraction;
    // end wxGlade
}; // wxGlade: end class


#endif // MANUALSEGMENTATIONPANELWIDGETUI_H