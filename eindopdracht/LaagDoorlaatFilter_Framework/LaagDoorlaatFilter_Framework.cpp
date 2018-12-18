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
#include <math.h>

#include "mainClass.h"
#include "RCFilter.h"
#include "FrequencyRange.h"
#include "FilterPoint.h"
#include <iostream>

#include <SimpleXLSXWriter/Source/Xlsx/Chart.h>
#include <SimpleXLSXWriter/Source/Xlsx/Chartsheet.h>
#include <SimpleXLSXWriter/Source/Xlsx/Workbook.h>

#include "ExcelWriter/ExcelWriter.h"

#define PI 3.14159265359

////////////////////////////////////////////////////////////////////////////////
// namespaces

using namespace std;
using namespace SimpleXlsx;

////////////////////////////////////////////////////////////////////////////////
void calculatePoints(double fBegin, double fEnd, unsigned int nPoints, double resistor, double capacitor, vector<FilterPoint>& Punten);
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

void calculatePoints(double fBegin, double fEnd, unsigned int nPoints, double resistor, double capacitor,  vector<FilterPoint>& Punten)
{
	double interval = 1;
	double offset = 0;
	double phaseValue = 0;
	double transferValue = 0;
	double frequencyValue = 0;
	FilterPoint Punt;

	interval = ((fEnd - fBegin) / (nPoints - 1));			// interval berekenen

	cout << "bezig met berekenen...\n";

	for (int i = 0; i < nPoints; i++)
	{
		frequencyValue = (fBegin + offset);
		phaseValue =(-atanh(2*PI*frequencyValue*resistor*capacitor));
		transferValue = (1 / (sqrt(1 + pow((2 * PI*frequencyValue), 2)*pow(resistor, 2)*pow(capacitor, 2))));


		Punt.setFilterPoint(frequencyValue, transferValue, phaseValue);
		Punten.push_back(Punt);

		offset = offset + interval;
	}
	cout << "done\n";


}