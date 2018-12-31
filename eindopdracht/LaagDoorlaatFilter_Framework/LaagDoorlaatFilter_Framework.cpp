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
void calculatePoints(FrequencyRange& range, RCFilter& rcfilter, vector<FilterPoint>& Punten);
void maakPlot(vector<FilterPoint>& points, unsigned int nPoints);
// TODO: invullen


////////////////////////////////////////////////////////////////////////////////
// memberfunction run()

int mainClass::run()
{
	double resistor = 1000;
	double capacitor = 0.0001;
	double startF;
	double endF;
	RCFilter rcfilter;
	FrequencyRange Range;

	unsigned int keuze = 0;
	unsigned int nPoints = 100;

	vector<FilterPoint> filterPlot;	// alle punten van het filter voor een bepaalde frequentie	
	
	cout << "Laagdoorlaatfilter berekening" << endl;

	while (keuze != 9)
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
			rcfilter.setRCValues(resistor, 0);

			break;
		case 2:
			// TODO: waarde inlezen voor C

			cout << "Voer een waarde in voor C in uF: ";
			cin >> capacitor;
			capacitor = capacitor * 0.000001;
			rcfilter.setRCValues(0, capacitor);

			break;
		case 3:
			// TODO: waarden weergeven van filtereigenschappen
			double kantelpunt;
			rcfilter.getCharacteristics(resistor, capacitor, kantelpunt);
			cout << "weerstands waarde: " << resistor <<"\n";
			cout << "condensator waarde: " << capacitor <<"\n";
			cout << "kantelpunt waarde: " << kantelpunt <<"\n";

			break;
		case 4:
			// TODO: toon beginfrequentie
			cout << "Voer een waarde in voor de begin ferqentie in: ";
			cin >> startF;
			Range.setRange(startF, 0, 0);
			break;
		case 5:
			cout << "Voer een waarde in voor de eind ferqentie in: ";
			cin >> endF;
			Range.setRange(0, endF, 0);
			
			break;
		case 6:
			cout << "Voer een waarde in voor het aantal stappen: ";
			cin >> nPoints;
			Range.setRange(0, 0, nPoints);

			break;
		case 7:
			Range.getRange(startF, endF, nPoints);

			cout << "startferquentie: " << startF << "\n";
			cout << "eindferqentie: " << endF << "\n";
			cout << "aantal punten: " << nPoints << "\n";
			break;
		case 8: 
			calculatePoints(Range, rcfilter, filterPlot);
			maakPlot(filterPlot, nPoints);
			break;
		case 9:
			cout << "einde programma" << endl;
			return 0;
			break;
		default:
			cout << "ongeldige keuze" << endl;
			break;
		}
	}
}
void calculatePoints(FrequencyRange& range, RCFilter& rcfilter, vector<FilterPoint>& Punten)
{
	double interval = 1;
	double offset = 0;
	double phaseValue = 0;
	double transferValue = 0;
	double frequencyValue = 0;

	double fBegin;
	double fEnd;
	unsigned int nPoints;
	
	range.getRange(fBegin, fEnd, nPoints);

	FilterPoint Punt;

	interval = ((fEnd - fBegin) / (nPoints - 1));			// interval berekenen

	cout << "bezig met berekenen...\n";

	for (unsigned int i = 0; i < nPoints; i++)
	{
		frequencyValue = (fBegin + offset);
		rcfilter.getTransfer(frequencyValue, transferValue, phaseValue);

		Punt.setFilterPoint(frequencyValue, transferValue, phaseValue);
		Punten.push_back(Punt);

		offset = offset + interval;
	}
	cout << "done\n";


}

void maakPlot(vector<FilterPoint>& points, unsigned int nPoints)
{
	string antwoord = "";
	bool saved = false;

	double transfer;
	double phase; 
	double freq;
	FilterPoint point;

	vector<double> tabelwaarden(3, 0);

	vector<FilterPoint>::iterator pos_values;
	vector<double>::iterator pos_tabel;

	pos_values = points.begin();
	

	ExcelWriter excelPlot("LCplot.xlsx");
	excelPlot.openWorkbook();

	CWorksheet& sheet_1 = excelPlot.addWorkSheet("datawaarden");
	CWorksheet& sheet_2 = excelPlot.addWorkSheet("plot");

	cout << "bezig met ploten...\n";

	for (int i = 0; i < nPoints; i++)
	{
		pos_tabel = tabelwaarden.begin();
		
		point = *pos_values;

		point.getFilterPoint(freq, transfer, phase);
		
		*pos_tabel = freq;
		pos_tabel += 1;
		*pos_tabel = transfer;
		pos_tabel += 1;
		*pos_tabel = phase;
		

		excelPlot.addRow(sheet_1, tabelwaarden);
		pos_values += 1;
	}
	excelPlot.addPlot(sheet_1, "overdracht", 0, nPoints, 1, nPoints, sheet_2);
	excelPlot.addPlot(sheet_1, "fase", 0, nPoints, 2, nPoints, sheet_2);
	
	if (excelPlot.saveWorkbook())
	{
		excelPlot.closeWorkbook();
		saved = true;
	}

	while (saved == false)
	{
		cout << "het opslaan is mis gegaan !\n";
		/*
		cout << "j/n\n";
		cin >> antwoord;
		if (antwoord == "j")
		{
			if (excelPlot.saveWorkbook() == true)
			{
				saved = false;
			}
			else
			{
				saved = true;
			}
		}
		else if (antwoord == "n")
		{
			excelPlot.closeWorkbook();
			saved == true;
		}*/
	}

	cout << "done\n";


}