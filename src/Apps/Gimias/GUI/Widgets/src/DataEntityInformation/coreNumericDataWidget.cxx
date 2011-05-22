// -*- C++ -*- generated by wxGlade 0.6.3 on Wed Sep 02 10:30:41 2009

#include "coreNumericDataWidget.h"

// begin wxGlade: ::extracode
// end wxGlade



Core::Widgets::NumericDataWidget::NumericDataWidget(wxWindow* parent, int id, const wxPoint& pos, const wxSize& size, long style):
    wxPanel(parent, id, pos, size, wxTAB_TRAVERSAL)
{
    // begin wxGlade: NumericDataWidget::NumericDataWidget
    gridNumericResults = new wxGrid(this, wxID_ANY);

    set_properties();
    do_layout();
    // end wxGlade
}


void Core::Widgets::NumericDataWidget::set_properties()
{
    // begin wxGlade: NumericDataWidget::set_properties
    gridNumericResults->CreateGrid(0, 2);
    gridNumericResults->EnableEditing(false);
    gridNumericResults->SetRowLabelSize(0);
    gridNumericResults->SetColLabelValue(0, wxT("Information"));
    gridNumericResults->SetColSize(0, 130);
    gridNumericResults->SetColLabelValue(1, wxT("Value"));
    gridNumericResults->SetColSize(1, 90);
    // end wxGlade
}


void Core::Widgets::NumericDataWidget::do_layout()
{
    // begin wxGlade: NumericDataWidget::do_layout
    wxBoxSizer* sizer_1 = new wxBoxSizer(wxVERTICAL);
    sizer_1->Add(gridNumericResults, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 0);
    SetSizer(sizer_1);
    sizer_1->Fit(this);
    // end wxGlade
}

void Core::Widgets::NumericDataWidget::UpdateWidget(std::vector<blTagMap::Pointer> tagMapVector, int timeStep)
{			
	//currently we have always one blTagMap
	blTagMap::Pointer tagMap = tagMapVector.at(0);
	blTagMap::Iterator it;
	int i = 0;
	for (it=tagMap->GetIteratorBegin(); it!=tagMap->GetIteratorEnd() ; it++)
	{
		gridNumericResults->AppendRows();
		gridNumericResults->SetCellValue(i,0, tagMap->GetTag(it)->GetName());

		wxString value = _U( tagMap->GetTag(it)->GetValueAsString() );
		gridNumericResults->SetCellValue(i,1, value);
		i++;
	}

	wxSize si = gridNumericResults->GetSize();
	si = gridNumericResults->GetMinSize();
	si = gridNumericResults->GetBestSize();

	Fit( );
}

