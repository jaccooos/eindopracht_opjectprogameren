//****************************************************************************
// TITLE        ExcelWriter
// DESCRIPTION	Klasse definitie voor ExcelWriter
// FILE			ExcelWriter.h
// AUTHOR		R. Smeets
// DATE			11-aug-2018
// ***************************************************************************
#pragma once

#include <string>

#include <SimpleXLSXWriter/Source/Xlsx/Chart.h>
#include <SimpleXLSXWriter/Source/Xlsx/Chartsheet.h>
#include <SimpleXLSXWriter/Source/Xlsx/Workbook.h>

using namespace std;
using namespace SimpleXlsx;


class ExcelWriter
{
private:
	string     m_fileName;
	CWorkbook* m_workbook;


public:
	
	// constructors
	ExcelWriter();
	ExcelWriter(const string& workbookName);

	~ExcelWriter();

	// member functions

	void setWorkbookName(const string& workbookName);
	void openWorkbook(void);
	void closeWorkbook(void);

	CWorksheet&  addWorkSheet (const string& worksheetName);
	CChartsheet& addChartSheet(const string& chartsheetName);
	
	void addRow(CWorksheet&  worksheet, vector<double>& rowdata);
	void addPlot(CWorksheet& sourcedataSheet, const string& plotName, 
				 short xColumnIndex, short xSize, short yColumIndex, short ySize,
				 CWorksheet& destChartSheet);

	bool saveWorkbook(void);
};
