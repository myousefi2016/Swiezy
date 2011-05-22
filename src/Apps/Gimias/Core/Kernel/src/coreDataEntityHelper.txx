/*
* Copyright (c) 2009,
* Computational Image and Simulation Technologies in Biomedicine (CISTIB),
* Universitat Pompeu Fabra (UPF), Barcelona, Spain. All rights reserved.
* See license.txt file for details.
*/

#ifndef coreDataEntityHelper_TXX
#define coreDataEntityHelper_TXX

#include "coreDataEntityHelper.h"
#include "coreException.h"
#include "coreLoggerHelper.h"
#include "coreKernel.h"
#include "coreDataContainer.h"

/**
*/
template <class ProcessingDataType>
void Core::DataEntityHelper::GetProcessingData( 
						Core::DataEntityHolder::Pointer dataEntityHolder,
						ProcessingDataType &processingData,
						int iTimeStep /*= 0*/ )
{
	Core::DataEntity::Pointer	dataEntity;

	dataEntity = dataEntityHolder->GetSubject( );
	if ( dataEntity.IsNull( ) )
	{
		throw Core::Exceptions::Exception("DataEntityHelper::GetProcessingData", 
			"You must select an input data from the Processing Browser and set it as input" 
		);
	}

	dataEntity->GetProcessingData( processingData, iTimeStep );
	if( !processingData )
	{
		throw Core::Exceptions::Exception("DataEntityHelper::GetProcessingData", 
			"You must select an input data from the Processing Browser and set it as input" 
		);
	}
}




/**
*/
template <class ProcessingDataType>
void Core::DataEntityHelper::GetProcessingData( 
	Core::DataEntityHolder::Pointer dataEntityHolder,
	std::vector< ProcessingDataType> &processingDataVector )
{
	Core::DataEntity::Pointer	dataEntity;

	dataEntity = dataEntityHolder->GetSubject( );
	if ( dataEntity.IsNull( ) )
	{
		throw Core::Exceptions::Exception("DataEntityHelper::GetProcessingData", 
			"You must select an input data from the Processing Browser and set it as input" 
		);
	}

	for ( size_t iTimeStep = 0 ; iTimeStep < dataEntity->GetNumberOfTimeSteps( ) ; iTimeStep++ )
	{
		ProcessingDataType processingData = NULL;
		bool ok = dataEntity->GetProcessingData( processingData, iTimeStep );
		if( !processingData || !ok )
		{
			throw Core::Exceptions::Exception("DataEntityHelper::GetProcessingData", 
				"You must select an input data from the Processing Browser and set it as input" 
			);
		}

		processingDataVector.push_back( processingData );
	}
}



#endif // coreDataEntityHelper_TXX
