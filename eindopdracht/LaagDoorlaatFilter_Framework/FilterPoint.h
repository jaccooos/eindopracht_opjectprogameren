//****************************************************************************
// TITLE        FilterPoint
// DESCRIPTION	Classe definitie van de data-classe FilterPunt bestaande uit
//				frequentie, overdracht en fase
// FILE			FilterPoint.h
// AUTHOR		R. Schoonus en J.C. Oostdijk
// DATE			9-01-2019
// ***************************************************************************

#pragma once

class FilterPoint
{
private:
	double frequency;
	double transfer;
	double phase;


public:
	FilterPoint();
	FilterPoint(double frequency, double transfer, double phase);
	void getFilterPoint(double& frequency, double& transfer, double& phase);
	void setFilterPoint(double frequency, double transfer, double phase);
};

