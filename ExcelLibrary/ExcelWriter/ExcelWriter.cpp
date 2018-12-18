//****************************************************************************
// TITLE        ExcelWriter
// DESCRIPTION	Klasse implementatie voor de ExcelWriter klasse
// FILE			ExcelWriter.cpp
// AUTHOR		R. Smeets
// DATE			10-aug-2018
// ***************************************************************************

#include "ExcelWriter.h"

#include <SimpleXLSXWriter/Source/Xlsx/Chart.h>
#include <SimpleXLSXWriter/Source/Xlsx/Chartsheet.h>
#include <SimpleXLSXWriter/Source/Xlsx/Workbook.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace SimpleXlsx;

ExcelWriter::ExcelWriter()
{
	m_fileName = "noname.xlsx";
	m_workbook = NULL;
}

ExcelWriter::ExcelWriter(const string& fileName)
{
	m_fileName = fileName;
	m_workbook = NULL;
}

ExcelWriter::~ExcelWriter()
{
	cout << "destructor ExcelWriter" << endl;
}

void ExcelWriter::setWorkbookName(const string& fileName)
{
	m_fileName = fileName;
}

CWorksheet& ExcelWriter::addWorkSheet(const string& sheetName)
{
	CWorksheet& worksheet = m_workbook->AddSheet(sheetName);

	return worksheet;
}

CChartsheet& ExcelWriter::addChartSheet(const string& chartsheetName)
{
	CChartsheet& chartsheet = m_workbook->AddChartSheet(chartsheetName);

	return chartsheet;
}

void ExcelWriter::openWorkbook(void)
{
	if (m_workbook == NULL)
	{
		m_workbook = new CWorkbook;
	}
}

void ExcelWriter::closeWorkbook(void)
{
	// remove workbook upon saving!!! Otherwise it is not possible to
	// reuse the CWorkbook object for a next round...

	if (m_workbook != NULL)
	{
		m_workbook->~CWorkbook();	// explicitly call destructor
		m_workbook = NULL;
	}
}

bool ExcelWriter::saveWorkbook(void)
{
	bool result = m_workbook->Save(m_fileName);
	if (result)
	{
		cout << "> Save OK: " << m_fileName << endl;
	}
	else
	{
		cout << "> Save FAILED: " << m_fileName << endl;
	}
	cout.flush();

	return result;
}


void ExcelWriter::addRow(CWorksheet& worksheet, vector<double>& rowdata)
{
	vector<CellDataDbl> row;
	vector<double>::iterator pos;

	for (pos = rowdata.begin(); pos != rowdata.end(); pos++)
	{
		row.push_back(*pos);
	}
	worksheet.AddRow(row);
}


void ExcelWriter::addPlot(CWorksheet& sourcedataSheet, const string& diagramName,
						  short xColumnIndex, short xSize, short yColumIndex, short ySize,
						  CWorksheet& destinationSheet)
{
	// create series object, that contains most chart settings
	CChart::Series ser;

	// amplitude, x-axis
	ser.catAxisFrom = CellCoord(1,     xColumnIndex);
	ser.catAxisTo   = CellCoord(xSize, xColumnIndex);
	ser.catSheet    = &sourcedataSheet;

	// specify range for values sequence (Y axis)
	ser.valAxisFrom = CellCoord(1,     yColumIndex);
	ser.valAxisTo   = CellCoord(ySize, yColumIndex);
	ser.valSheet    = &sourcedataSheet; // don`t forget to set the pointer to the data sheet

	ser.title = diagramName;
	ser.JoinType = CChart::Series::joinSmooth;

	CChart& chart = m_workbook->AddChart(destinationSheet, DrawingPoint(3, 3), DrawingPoint(20, 25), CHART_LINEAR);

	chart.AddSeries(ser);
	chart.SetDiagrammName(diagramName);
	chart.SetXAxisToCat();	// takes care of setting the correct C values for the X-axis

	chart.SetLegendPos(CChart::POS_TOP);
}