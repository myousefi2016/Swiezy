/*
* Copyright (c) 2009,
* Computational Image and Simulation Technologies in Biomedicine (CISTIB),
* Universitat Pompeu Fabra (UPF), Barcelona, Spain. All rights reserved.
* See license.txt file for details.
*/

#ifndef _coreToolbarPluginTab_H
#define _coreToolbarPluginTab_H

#include <wx/wx.h>
#include <wx/image.h>
#include "wx/toolbar.h"

#include "gmWidgetsWin32Header.h"

#include "coreBaseWindow.h"
#include "coreWindowConfig.h"

namespace Core
{
namespace Widgets
{

/**
\brief Automatically create tools from BaseWindow bitmaps and update
shown/hidden state
\ingroup gmWidgets
\author Xavi Planes
\date 1 April 2010
*/
class GMWIDGETS_EXPORT ToolbarPluginTab: public wxToolBar, public BaseWindow {
public:

	ToolbarPluginTab(wxWindow* parent, wxWindowID id, 
		const wxPoint& pos = wxDefaultPosition, 
		const wxSize& size = wxDefaultSize, 
		long style = wxTB_HORIZONTAL | wxTB_FLAT, 
		const wxString& name = wxPanelNameStr);


	//!
	Core::BaseProcessor::Pointer GetProcessor( );

protected:
	//!
	virtual void UpdateState();

	//!
	virtual void AddWidgetTool( wxWindow* window );

	//!
	void SetPluginTab(Core::Widgets::PluginTab* val);

	//!
	void OnSelectedTool( wxCommandEvent& event );

	//!
	virtual void AddTool( 
		wxWindowID id, const wxString &label, const wxBitmap &bitmap );

	DECLARE_EVENT_TABLE();
private:

	//! From window id to tool ID
	std::map<wxWindowID,wxWindowID> m_ToolWidgetMap;
};

} // namespace Widget
} // namespace Core

#endif // _coreToolbarPluginTab_H
