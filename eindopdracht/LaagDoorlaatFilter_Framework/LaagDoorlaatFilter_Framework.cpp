//****************************************************************************
// TITLE        LaagDoorlaatFilter_Framework
// DESCRIPTION	implementation of main program object
// FILE			LaagDoorlaatFilter_Framework.cpp
// AUTHOR		R. Schoonus en J.C. Oostdijk
// DATE			9-01-2019
// ***************************************************************************
 
////////////////////////////////////////////////////////////////////////////////
// includes

#include <string>
#include <vector>
#include <iostream>

#include "mainClass.h"
#include "RCFilter.h"
#include "FrequencyRange.h"
#include "FilterPoint.h"

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
void checkManualFQ(bool manStart, bool manEnd, RCFilter& rcfilter, FrequencyRange& range);

////////////////////////////////////////////////////////////////////////////////
// memberfunction run()

int mainClass::run()
{
	double resistor;
	double capacitor;
	double startF;
	double endF;
	unsigned int nPoints;

	RCFilter rcfilter;
	FrequencyRange Range;

	unsigned int keuze = 0;
	unsigned int keuzeType = 0;

	bool manualStartFQ = true;
	bool manualEndFQ = true;

	double kantelpunt;

	vector<FilterPoint> filterPlot;	// alle punten van het filter voor een bepaalde frequentie	
	
	cout << "Laagdoorlaatfilter berekening" << endl;

	while (keuze != 10)
	{
		cout << "maak keuze:" << endl;
		cout << "--- RC filter ---" << endl;
		cout << "1: stel type in" << endl;
		cout << "2: geef R" << endl;
		cout << "3: geef C" << endl;
		cout << "4: toon filtereigenschappen" << endl;
		cout << endl;
		cout << "--- Plot parameters ---" << endl;				
		cout << "5: geef beginfrequentie" << endl;
		cout << "6: geef eindfrequentie" << endl;
		cout << "7: geef aantal stappen" << endl;
		cout << "8: toon parameters" << endl;
		cout << endl;
		cout << "--- Uitvoeren ---" << endl;
		cout << "9: bereken karakteristiek" << endl;
		cout << "10: einde programma" << endl;

		cin >> keuze;

		switch (keuze)
		{
		case 1:
			//type filter kiezen

			cout << "1: laagdoorlaat filter" << endl;
			cout << "2: hoogdoorlaat filter" << endl;

			cin >> keuzeType;

			switch (keuzeType)
			{
			case 1:
				rcfilter.setType(false);
				break;
			case 2:
				rcfilter.setType(true);
				break;
			default:
				cout << "ongeldige keuze" << endl;
				break;
			}
			break;
		case 2:
			//waarde inlezen voor R
			
			cout << "Voer een waarde in voor R in Ohm: ";
			cin >> resistor;
			rcfilter.setRCValues(resistor, 0);

			break;
		case 3:
			//waarde inlezen voor C

			cout << "Voer een waarde in voor C in uF: ";
			cin >> capacitor;
			capacitor = capacitor * 0.000001;		
			rcfilter.setRCValues(0, capacitor);

			break;
		case 4:
			// waarden weergeven van filtereigenschappen
			
			double amplitude;
			double phase;
			bool type;

			rcfilter.getCharacteristics(resistor, capacitor, kantelpunt, type);

			if (type == false)
			{
				cout << "Type is een laagdoorlaat filter\n";
			}
			else if (type == true)
			{
				cout << "Type is een hoogdoorlaat filter\n";
			}
			cout << "Weerstands waarde: " << resistor <<"\n";
			cout << "Condensator waarde: " << capacitor <<"\n";
			cout << "Kantelpunt waarde: " << kantelpunt <<"\n";

			rcfilter.getTransfer(kantelpunt, amplitude, phase);
			cout << "Amplitude op het kantelpunt: " << amplitude << "\n";
			cout << "Phase op het kantelpunt: " << phase << "\n";

			break;
		case 5:
			//beginfrequentie invoeren

			cout << "Voer een waarde in voor de begin ferqentie in: ";
			cin >> startF;
			Range.setRange(startF, 0, 0);
			manualStartFQ = false;
			break;
		case 6:
			//eindfrequentie invoeren

			cout << "Voer een waarde in voor de eind ferqentie in: ";
			cin >> endF;						
			Range.setRange(0, endF, 0);			
			manualEndFQ = false;
			break;
		case 7:
			//aantal stappen invoeren van de frequentierange

			cout << "Voer een waarde in voor het aantal stappen: ";
			cin >> nPoints;						
			Range.setRange(0, 0, nPoints);		

			break;
		case 8:
			//toon parameters

			checkManualFQ(manualStartFQ, manualEndFQ, rcfilter, Range);	//check of er een manual ferquentie is gebruikt
			Range.getRange(startF, endF, nPoints);						//haal de gegevens op
																		//zet de gegevens op uit uitvoer scherm
			cout << "Startferquentie: " << startF << "\n";
			cout << "Eindferqentie: " << endF << "\n";
			cout << "Aantal punten: " << nPoints << "\n";

			break;
		case 9: 
			//plotten
			
			checkManualFQ(manualStartFQ, manualEndFQ, rcfilter, Range);	//check of er een manual ferquentie is gebruikt

			calculatePoints(Range, rcfilter, filterPlot);				//bereken de punten
			maakPlot(filterPlot, nPoints);								//zet de punten in excel en plot deze

			break;
		case 10:
			//programma afsluiten

			cout << "einde programma" << endl;
			return 0;

			break;
		default:
			//als er geen juiste invoer is

			cout << "ongeldige keuze" << endl;

			break;
		}
	}
}

void calculatePoints(FrequencyRange& range, RCFilter& rcfilter, vector<FilterPoint>& Punten)
{
	//variabelen
	double interval = 1;
	double offset = 0;
	double phaseValue = 0;
	double transferValue = 0;
	double frequencyValue = 0;

	double fBegin;
	double fEnd;
	unsigned int nPoints;
	
	FilterPoint Punt;

	range.getRange(fBegin, fEnd, nPoints);					//gegevens uit range ophalen
	interval = ((fEnd - fBegin) / (nPoints - 1));			// interval berekenen

	cout << "bezig met berekenen...\n";

	for (unsigned int i = 0; i < nPoints; i++)	
	{
		//voor het aantal punten wordt voor elke ferquentie de aparte waarden uitgerekend en vervolgens in de vector gezet
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
	//variabelen
	string antwoord = "";
	bool saved = false;

	double transfer;
	double phase; 
	double freq;
	FilterPoint point;

	vector<double> tabelwaarden(3, 0);
	vector<FilterPoint>::iterator pos_values;
	vector<double>::iterator pos_tabel;

	//maak een excel document aan
	ExcelWriter excelPlot("RCplot.xlsx");
	excelPlot.openWorkbook();
	CWorksheet& sheet_1 = excelPlot.addWorkSheet("datawaarden");
	CWorksheet& sheet_2 = excelPlot.addWorkSheet("plot");

	cout << "bezig met ploten...\n";

	pos_values = points.begin();		//pos naar begin van de vector verplatsen

	for (int i = 0; i < nPoints; i++)
	{
		pos_tabel = tabelwaarden.begin();	//pos naar begin van de vector verplatsen
		
		point = *pos_values;				//punt van uit vector kopieren

											//zet de verschillende waarden achter elkaar in de tabel vector
		point.getFilterPoint(freq, transfer, phase);
		
		*pos_tabel = freq;
		pos_tabel += 1;
		*pos_tabel = transfer;
		pos_tabel += 1;
		*pos_tabel = phase;
		
				
		excelPlot.addRow(sheet_1, tabelwaarden);	//nieuwe rij
		pos_values += 1;							//een plekje opschuiven in de vector 
	}

	excelPlot.addPlot(sheet_1, "overdracht", 0, nPoints, 1, nPoints, sheet_2);
	excelPlot.addPlot(sheet_1, "fase", 0, nPoints, 2, nPoints, sheet_2);
	
	if (excelPlot.saveWorkbook())				//check of het opslaan gelukt is
	{
		excelPlot.closeWorkbook();
		saved = true;
	}
	else
	{
		cout << "het opslaan is mis gegaan !\n";
	}
	
	cout << "done\n";
}

void checkManualFQ(bool manStart, bool manEnd, RCFilter& rcfilter, FrequencyRange& range)
{
	double kantelpunt;
	//deze functie kijkt of er een handimatige ferquentie is ingesteld zo niet zet deze de standaard waardes in de ferquentie range


	kantelpunt = rcfilter.get3dBPoint();			// haal het kantelpunt op

	if (manStart == true)
	{
		range.setRange((0.1*kantelpunt), 0, 0);		//zet de standaard start waarde in de ferquentie range
	}
	if (manEnd == true)
	{
		range.setRange(0, (10 * kantelpunt), 0);	//zet de standaard eind waarde in de ferquentie range
	}
}