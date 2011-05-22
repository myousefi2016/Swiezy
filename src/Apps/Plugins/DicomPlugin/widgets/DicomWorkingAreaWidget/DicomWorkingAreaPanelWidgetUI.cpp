// -*- C++ -*- generated by wxGlade 0.6.3 on Mon Dec 20 11:54:29 2010

#include "DicomWorkingAreaPanelWidgetUI.h"

// begin wxGlade: ::extracode

// end wxGlade


DicomWorkingAreaPanelWidgetUI::DicomWorkingAreaPanelWidgetUI(wxWindow* parent, int id, const wxPoint& pos, const wxSize& size, long style):
    wxPanel(parent, id, pos, size, wxTAB_TRAVERSAL)
{
    // begin wxGlade: DicomWorkingAreaPanelWidgetUI::DicomWorkingAreaPanelWidgetUI
    sizer_11_staticbox = new wxStaticBox(this, -1, wxT("Advanced"));
    sizer_1_staticbox = new wxStaticBox(this, -1, wxT("DICOM Tree Viewer"));
    sizer_6_staticbox = new wxStaticBox(this, -1, wxT("Reconstruct data"));
    m_treeDicomView = new DicomPlugin::DICOMTree(this, wxID_DICOM_TREE, wxDefaultPosition, wxDefaultSize, wxTR_HAS_BUTTONS|wxTR_LINES_AT_ROOT|wxTR_MULTIPLE|wxTR_MULTIPLE|wxTR_DEFAULT_STYLE|wxSUNKEN_BORDER);
    label_2 = new wxStaticText(this, wxID_ANY, wxT("Space"));
    m_dcmSpaceSlider = new wxSlider(this, wxID_DICOM_IMG_SPACE_SLIDER, 0, 0, 10, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_AUTOTICKS);
    m_sliceName = new wxStaticText(this, wxID_ANY, wxT("Slice name:"));
    m_RenderWindow = new DicomPlugin::DcmImageViewWindow(this, wxID_ANY);
    label_1 = new wxStaticText(this, wxID_ANY, wxT("Time"));
    m_dcmTimeSlider = new wxSlider(this, wxID_DICOM_IMG_TIME_SLIDER, 0, 0, 10, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_AUTOTICKS);
    m_LevelWindowWidget = new mitk::wxMitkLevelWindowWidget(this, wxID_ANY);
    m_chbCombineData = new wxCheckBox(this, wxID_DICOM_COMBINE_DATA, wxT("Combine data"));
    m_chbReorientData = new wxCheckBox(this, wxID_DICOM_REORIENT_DATA, wxT("Reorient data"));
    m_chbExportRawData = new wxCheckBox(this, wxID_DICOM_EXPORT_RAW_DATA, wxT("Export DICOM slices"));
    m_chbTaggedMR = new wxCheckBox(this, wxID_DICOM_TAGGED_MR, wxT("Tagged MR"));
    label_3 = new wxStaticText(this, wxID_ANY, wxT("Time tag"));
    const wxString *m_cmbTimeTag_choices = NULL;
    m_cmbTimeTag = new wxComboBox(this, wxID_DICOM_TIME_TAG, wxT(""), wxDefaultPosition, wxDefaultSize, 0, m_cmbTimeTag_choices, wxCB_DROPDOWN|wxCB_READONLY);
    m_btnAddToDatalist = new wxButton(this, wxID_DICOM_ADD_TO_DATALIST, wxT("Add to Datalist"), wxDefaultPosition, wxDefaultSize, wxBU_RIGHT);

    set_properties();
    do_layout();
    // end wxGlade
}


BEGIN_EVENT_TABLE(DicomWorkingAreaPanelWidgetUI, wxPanel)
    // begin wxGlade: DicomWorkingAreaPanelWidgetUI::event_table
    EVT_COMBOBOX(wxID_DICOM_TIME_TAG, DicomWorkingAreaPanelWidgetUI::OnTimeTag)
    // end wxGlade
END_EVENT_TABLE();


void DicomWorkingAreaPanelWidgetUI::OnTimeTag(wxCommandEvent &event)
{
    event.Skip();
    wxLogDebug(wxT("Event handler (DicomWorkingAreaPanelWidgetUI::OnTimeTag) not implemented yet")); //notify the user that he hasn't implemented the event handler yet
}


// wxGlade: add DicomWorkingAreaPanelWidgetUI event handlers


void DicomWorkingAreaPanelWidgetUI::set_properties()
{
    // begin wxGlade: DicomWorkingAreaPanelWidgetUI::set_properties
    m_dcmSpaceSlider->SetToolTip(wxT("move through the space"));
    m_sliceName->SetFont(wxFont(8, wxDEFAULT, wxNORMAL, wxNORMAL, 0, wxT("")));
    m_dcmTimeSlider->SetBackgroundColour(wxColour(236, 233, 216));
    m_dcmTimeSlider->SetFont(wxFont(8, wxDEFAULT, wxNORMAL, wxNORMAL, 0, wxT("")));
    m_dcmTimeSlider->SetToolTip(wxT("move through the time"));
    m_LevelWindowWidget->SetToolTip(wxT("Adjust Level Window"));
    m_chbCombineData->SetToolTip(wxT("Combine selected items into one data"));
    m_chbReorientData->SetToolTip(wxT("Use DICOM orientation to reorient the data"));
    m_chbReorientData->SetValue(1);
    m_chbExportRawData->SetToolTip(wxT("Export tagged MR"));
    m_chbTaggedMR->SetToolTip(wxT("Export DICOM slices as 2D slices images without creating a 3D image"));
    m_btnAddToDatalist->SetToolTip(wxT("Add selected data to GIMIAS data list"));
    // end wxGlade
}


void DicomWorkingAreaPanelWidgetUI::do_layout()
{
    // begin wxGlade: DicomWorkingAreaPanelWidgetUI::do_layout
    wxBoxSizer* GlobalSizer = new wxBoxSizer(wxVERTICAL);
    wxStaticBoxSizer* sizer_1 = new wxStaticBoxSizer(sizer_1_staticbox, wxHORIZONTAL);
    wxBoxSizer* sizer_3 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_4 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticBoxSizer* sizer_11 = new wxStaticBoxSizer(sizer_11_staticbox, wxHORIZONTAL);
    wxStaticBoxSizer* sizer_6 = new wxStaticBoxSizer(sizer_6_staticbox, wxHORIZONTAL);
    wxBoxSizer* sizer_9 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_10 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_5 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_7 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_8 = new wxBoxSizer(wxVERTICAL);
    sizer_1->Add(m_treeDicomView, 2, wxALL|wxEXPAND, 5);
    sizer_8->Add(label_2, 0, wxTOP, 10);
    sizer_8->Add(m_dcmSpaceSlider, 1, wxEXPAND, 0);
    sizer_2->Add(sizer_8, 0, wxEXPAND, 0);
    sizer_5->Add(m_sliceName, 0, wxLEFT|wxALIGN_CENTER_VERTICAL, 0);
    sizer_5->Add(m_RenderWindow, 10, wxALL|wxEXPAND, 0);
    sizer_7->Add(label_1, 0, wxLEFT|wxALIGN_CENTER_VERTICAL|wxSHAPED, 5);
    sizer_7->Add(m_dcmTimeSlider, 1, wxLEFT|wxEXPAND, 0);
    sizer_5->Add(sizer_7, 0, wxEXPAND, 0);
    sizer_2->Add(sizer_5, 9, wxEXPAND, 5);
    sizer_2->Add(m_LevelWindowWidget, 0, wxEXPAND, 0);
    sizer_3->Add(sizer_2, 9, wxBOTTOM|wxEXPAND, 5);
    sizer_10->Add(m_chbCombineData, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_VERTICAL, 5);
    sizer_10->Add(m_chbReorientData, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_VERTICAL, 5);
    sizer_6->Add(sizer_10, 1, wxEXPAND, 0);
    sizer_9->Add(m_chbExportRawData, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_VERTICAL, 5);
    sizer_9->Add(m_chbTaggedMR, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_VERTICAL, 5);
    sizer_6->Add(sizer_9, 1, wxEXPAND, 0);
    sizer_4->Add(sizer_6, 0, wxEXPAND, 0);
    sizer_11->Add(label_3, 0, wxALL, 5);
    sizer_11->Add(m_cmbTimeTag, 0, 0, 0);
    sizer_4->Add(sizer_11, 1, wxEXPAND, 0);
    sizer_4->Add(m_btnAddToDatalist, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5);
    sizer_3->Add(sizer_4, 0, wxEXPAND, 0);
    sizer_1->Add(sizer_3, 6, wxEXPAND, 0);
    GlobalSizer->Add(sizer_1, 1, wxALL|wxEXPAND, 5);
    SetSizer(GlobalSizer);
    GlobalSizer->Fit(this);
    // end wxGlade
}
