/*
* Copyright (c) 2009,
* Computational Image and Simulation Technologies in Biomedicine (CISTIB),
* Universitat Pompeu Fabra (UPF), Barcelona, Spain. All rights reserved.
* See license.txt file for details.
*/

#ifndef coreVTKUnstructuredGridReader_H
#define coreVTKUnstructuredGridReader_H

#include "coreBaseDataEntityReader.h"

namespace Core
{
namespace IO
{
/** 
A specialization of the DataEntityReader class for VTK PolyData objects.
If wraps the VTKPolyDataReader class to be used as a DataEntityReader 
that can be registered by the Core.

\ingroup gmIO
\author Chiara Riccobene
\date  2008
*/
class GMIO_EXPORT VTKUnstructuredGridReader : public BaseDataEntityReader
{
public:
	coreDeclareSmartPointerClassMacro(
		VTKUnstructuredGridReader, 
		BaseDataEntityReader);

	void ReadData( );

protected:
	VTKUnstructuredGridReader(void);
	virtual ~VTKUnstructuredGridReader(void);

	//!
	virtual boost::any ReadSingleTimeStep( 
		int iTimeStep, 
		const std::string &filename );

private:
	coreDeclareNoCopyConstructors(VTKUnstructuredGridReader);
};

}
}

#endif
