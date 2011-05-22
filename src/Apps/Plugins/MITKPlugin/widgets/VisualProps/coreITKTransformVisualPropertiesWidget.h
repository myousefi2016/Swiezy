/*
* Copyright (c) 2009,
* Computational Image and Simulation Technologies in Biomedicine (CISTIB),
* Universitat Pompeu Fabra (UPF), Barcelona, Spain. All rights reserved.
* See license.txt file for details.
*/

#ifndef coreITKTransformVisualPropertiesWidget_H
#define coreITKTransformVisualPropertiesWidget_H

#include "gmWidgetsWin32Header.h"
#include "coreObject.h"
#include "coreDataHolder.h"
#include <wxMitkTransformVisualPropWidget.h>
#include <mitkDataTreeNode.h>
#include "coreVisualProperties.h"

namespace Core
{
namespace Widgets 
{ 
/** 

\ingroup gmWidgets
\author Juan Antonio Moya
\date 07 Feb 2008
*/
class PLUGIN_EXPORT ITKTransformVisualPropertiesWidget 
	: public mitk::wxMitkTransformVisualPropWidget, public VisualPropertiesBase
{
public:
	//!
	coreDefineBaseWindowFactory( ITKTransformVisualPropertiesWidget );

	coreClassNameMacro(ITKTransformVisualPropertiesWidget);

	ITKTransformVisualPropertiesWidget(
		wxWindow* parent, 
		wxWindowID id, 
		const wxPoint& pos = wxDefaultPosition, 
		const wxSize& size = wxDefaultSize, 
		long style = wxBORDER_NONE, 
		const wxString& name = wxT("ITKTransformVisualPropertiesWidget"));
	virtual ~ITKTransformVisualPropertiesWidget(void);

	void SetInputHolder(DataEntityHolder::Pointer _aInputHolder)
	{
		this->m_InputHolder = _aInputHolder;
		this->m_InputHolder->AddObserver(
			this, 
			&ITKTransformVisualPropertiesWidget::OnInputHolderChangeSubject, 
			Core::DH_SUBJECT_MODIFIED_OR_NEW_SUBJECT);
	};
	DataEntityHolder::Pointer GetInputHolder(void) const
	{ 
		return this->m_InputHolder; 
	};
	//!
	bool IsValidData( Core::DataEntity::Pointer dataEntity )
	{
		return dataEntity->IsTransform();
	}
	//!
	void SetMultiRenderWindow(Core::Widgets::RenderWindowBase* val);

private:
	void OnInputHolderChangeSubject(void);
	DataEntityHolder::Pointer m_InputHolder;

};

}
}


#endif // ITKTransformVisualPropertiesWidget_H
