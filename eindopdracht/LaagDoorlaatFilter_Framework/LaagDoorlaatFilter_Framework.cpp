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
// function prototypes
void calculatePoints(double fBegin, double fEnd, unsigned int nPoints, double resistor, double capacitor, vector<FilterPoint>& Punten);
// TODO: invullen


////////////////////////////////////////////////////////////////////////////////
// memberfunction run()

int mainClass::run()
{
	double resistor = 1000;
	double capacitor = 0.0001;

	unsigned int keuze = 0;

	vector<FilterPoint> filterPlot;	// alle punten van het filter voor een bepaalde frequentie	
	
	cout << "Laagdoorlaatfilter berekening" << endl;

	while (keuze != 13)
	{
		cout << "maak keuze:" << endl;
		cout << "--- RC filter ---" << endl;
		cout << "1: geef R" << endl;
		cout << "2: geef C" << endl;
		cout << "3: toon filtereigenschappen" << endl;
		cout << endl;
		cout << "--- Plot parameters ---" << endl;				
		cout << "4: geef beginfrequentie" << endl;
		cout << "5: geef eindfrequentie" << endl;
		cout << "6: geef aantal stappen" << endl;
		cout << "7: toon parameters" << endl;
		cout << endl;
		cout << "--- Uitvoeren ---" << endl;
		cout << "8: bereken karakteristiek" << endl;
		cout << "9: einde programma" << endl;

		cin >> keuze;

		switch (keuze)
		{
		case 1:
			// TODO: waarde inlezen voor R
			
			cout << "Voer een waarde in voor R in Ohm: ";
			cin >> resistor;

			break;
		case 2:
			// TODO: waarde inlezen voor C

			cout << "Voer een waarde in voor C in uF: ";
			cin >> capacitor;

			break;
		case 3:
			// TODO: waarden weergeven van filtereigenschappen

			getRCValues(R, C);

			break;
		case 4:
			// TODO: toon beginfrequentie
			
			break;
		case 5:
			// TODO: toon eindfrequentie
			
			break;
		case 6:
			// TODO: toon aantal stappen

			break;
		case 7:
			// TODO: toon parameters

			break;
		case 8: 
			// TODO: toon karakteristiek
		case 9:
			cout << "einde programma" << endl;
			return 0;
			break;
		default:
			cout << "ongeldige keuze" << endl;
			break;
		}
	}
while (cin.get() != '\n');
cin.get();

return 0;  // Return from memberfunction, geen fouten
}
void calculatePoints(double fBegin, double fEnd, unsigned int nPoints, double resistor, double capacitor, vector<FilterPoint>& Punten)
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
		phaseValue = (-atanh(2 * PI*frequencyValue*resistor*capacitor));
		transferValue = (1 / (sqrt(1 + pow((2 * PI*frequencyValue), 2)*pow(resistor, 2)*pow(capacitor, 2))));


		Punt.setFilterPoint(frequencyValue, transferValue, phaseValue);
		Punten.push_back(Punt);

		offset = offset + interval;
	}
	cout << "done\n";


}