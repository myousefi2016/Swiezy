/*
* Copyright (c) 2009,
* Computational Image and Simulation Technologies in Biomedicine (CISTIB),
* Universitat Pompeu Fabra (UPF), Barcelona, Spain. All rights reserved.
* See license.txt file for details.
*/

#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include "itkPluginUtilities.h"

#include "itkOtsuThresholdImageFilter.h"

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "itkPluginFilterWatcher.h"

#include "BinaryThresholdImageFilterCLP.h"

// Use an anonymous namespace to keep class types and function names
// from colliding when module is used as shared object module.  Every
// thing should be in an anonymous namespace except for the module
// entry point, e.g. main()
//
namespace {

	template<class T> int DoIt( int argc, char * argv[], T )
	{
		PARSE_ARGS;

		typedef    T       InputPixelType;
		typedef    T       OutputPixelType;
		
		typedef itk::Image< InputPixelType,  3 >   InputImageType;
		typedef itk::Image< OutputPixelType, 3 >   OutputImageType;
		typedef itk::BinaryThresholdImageFilter<
		           InputImageType, OutputImageType >  FilterType;
		typedef itk::ImageFileReader< InputImageType >  ReaderType;
		typedef itk::ImageFileWriter< OutputImageType >  WriterType;
		
		
		typename ReaderType::Pointer reader = ReaderType::New();
		typename FilterType::Pointer filter = FilterType::New();
		itk::PluginFilterWatcher watcher(filter, "Otsu Threshold Image Filter",
		                               CLPProcessInformation);
		
		typename WriterType::Pointer writer = WriterType::New();
		writer->SetInput( filter->GetOutput() );
		writer->SetUseCompression(1);
		reader->SetFileName( inputVolume.c_str() );
		
		filter->SetInput( reader->GetOutput() );
		filter->SetOutsideValue( outsideValue );
		filter->SetInsideValue(  insideValue  );
		filter->SetLowerThreshold(  lowerThreshold  );
		filter->SetUpperThreshold(  upperThreshold  );
		filter->Update();
		
		writer->SetFileName( outputVolume.c_str() );
		writer->Update();
		
		return EXIT_SUCCESS;

	}
	
} // end of anonymous namespace



int main( int argc, char *argv[] )
{
	PARSE_ARGS;

	itk::ImageIOBase::IOPixelType pixelType;
	itk::ImageIOBase::IOComponentType componentType;
	try
	{
		itk::GetImageType (inputVolume, pixelType, componentType);

		// This filter handles all types on input, but only produces
		// signed types
		switch (componentType)
		{
		case itk::ImageIOBase::UCHAR:
			return DoIt( argc, argv, static_cast<unsigned char>(0));
			break;
		case itk::ImageIOBase::CHAR:
			return DoIt( argc, argv, static_cast<char>(0));
			break;
		case itk::ImageIOBase::USHORT:
			return DoIt( argc, argv, static_cast<unsigned short>(0));
			break;
		case itk::ImageIOBase::SHORT:
			return DoIt( argc, argv, static_cast<short>(0));
			break;
		case itk::ImageIOBase::UINT:
			return DoIt( argc, argv, static_cast<unsigned int>(0));
			break;
		case itk::ImageIOBase::INT:
			return DoIt( argc, argv, static_cast<int>(0));
			break;
		case itk::ImageIOBase::ULONG:
			return DoIt( argc, argv, static_cast<unsigned long>(0));
			break;
		case itk::ImageIOBase::LONG:
			return DoIt( argc, argv, static_cast<long>(0));
			break;
		case itk::ImageIOBase::FLOAT:
			return DoIt( argc, argv, static_cast<float>(0));
			break;
		case itk::ImageIOBase::DOUBLE:
			return DoIt( argc, argv, static_cast<double>(0));
			break;
		case itk::ImageIOBase::UNKNOWNCOMPONENTTYPE:
		default:
			std::cout << "unknown component type" << std::endl;
			break;
		}
	}

	catch( itk::ExceptionObject &excep)
	{
		std::cerr << argv[0] << ": exception caught !" << std::endl;
		std::cerr << excep << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

