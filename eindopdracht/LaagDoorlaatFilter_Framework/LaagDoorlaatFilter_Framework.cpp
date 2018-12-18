//****************************************************************************
// TITLE        LaagDoorlaatFilter_Framework
// DESCRIPTION	implementation of main program object
// FILE			LaagDoorlaatFilter_Framework.cpp
// AUTHOR		R. Smeets
// DATE			10-aug-2018
// ***************************************************************************
 
////////////////////////////////////////////////////////////////////////////////
// includes

#include <string>
#include <vector>

#include "mainClass.h"
#include "RCFilter.h"
#include "FrequencyRange.h"
#include "FilterPoint.h"
#include <iostream>

#include <SimpleXLSXWriter/Source/Xlsx/Chart.h>
#include <SimpleXLSXWriter/Source/Xlsx/Chartsheet.h>
#include <SimpleXLSXWriter/Source/Xlsx/Workbook.h>

#include "ExcelWriter/ExcelWriter.h"


////////////////////////////////////////////////////////////////////////////////
// namespaces

using namespace std;
using namespace SimpleXlsx;

////////////////////////////////////////////////////////////////////////////////
void calculatePoints(double xBegin, double xEnd, unsigned int nPoints, vector<FilterPoint>& Punten);
// TODO: invullen


////////////////////////////////////////////////////////////////////////////////
// memberfunction run()

int mainClass::run()
{

	vector<FilterPoint> filterPlot;	// alle punten van het filter voor een bepaalde frequentie	
	
	cout << "Laagdoorlaatfilter berekening" << endl;

	while (cin.get() != '\n');
	cin.get();

	return 0;  // Return from memberfunction, geen fouten
}

void calculatePoints(double xBegin, double xEnd, unsigned int nPoints, vector<FilterPoint>& Punten)
{
	double interval = 1;
	double offset = 0;
	double sinvalue = 0;
	double xvalue = 0;
	interval = ((xEnd - xBegin) / (nPoints - 1));			// interval berekenen

	cout << "bezig met berekenen...\n";
	for (int i = 0; i < nPoints; i++)
	{
		xvalue = (xBegin + offset);
		sinvalue = sin(xvalue);

		xValues.push_back(xvalue);
		sinxValues.push_back(sinvalue);

		offset = offset + interval;
	}
	cout << "done\n";


}