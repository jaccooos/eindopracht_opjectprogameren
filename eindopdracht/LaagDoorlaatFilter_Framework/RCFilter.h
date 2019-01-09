
//****************************************************************************
// TITLE        RCFilter
// DESCRIPTION	Klassedefinitie voor een RC filter
// FILE			RCFilter.h
// AUTHOR		R. Schoonus en J.C. Oostdijk
// DATE			9-01-2019
// ***************************************************************************

#pragma once

using namespace std;

// klasse RCFilter

class RCFilter
{
private:
	// TODO: invullen

	double resistor;
	double capacitor;
	double db3Point;
	bool hoogDoorlaat;

public:
	// TODO: invullen

	RCFilter();
	RCFilter(double resistor, double capacitor);

	void setRCValues(const double resistor, const double capacitor);
	void getRCValues(double& resistor, double& capacitor);
	double get3dBPoint(void);
	void getCharacteristics(double& resistor, double& capacitor, double& db3Point, bool& type);
	void getTransfer(const double frequency, double& amplitude, double& phase);
	void setType(bool type);
};

