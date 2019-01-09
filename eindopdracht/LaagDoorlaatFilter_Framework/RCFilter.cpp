//****************************************************************************
// TITLE        RCFilter
// DESCRIPTION	Klasse implementatie voor de RCFilter klasse
// FILE			RCFilter.cpp
// AUTHOR		R. Schoonus en J.C. Oostdijk
// DATE			9-01-2019
// ***************************************************************************

#define _USE_MATH_DEFINES
#include <cmath>
#include "RCFilter.h"

const double PI = 3.14159265358979F;

// Constructors RCFilter()

RCFilter::RCFilter()
{
	// TODO: invullen

	this->resistor	= 1000;
	this->capacitor = 0.00001;
	this->hoogDoorlaat = false;
}

RCFilter::RCFilter(double resistor, double capacitor)
{
	// TODO: invullen

	this->resistor	= resistor;
	this->capacitor = capacitor;
	this->hoogDoorlaat = false;
}


// member functies

void RCFilter::setRCValues(const double resistor, const double capacitor)
{
	// TODO: invullen

	if (resistor != 0)
	{
		this->resistor = resistor;
	}
	if (capacitor != 0)
	{
		this->capacitor = capacitor;
	}	
}

void RCFilter::getRCValues(double& resistor, double& capacitor)
{
	// TODO: invullen}

	resistor  = this->resistor;
	capacitor = this->capacitor;
}

double RCFilter::get3dBPoint(void)
{
	
	db3Point = (1 / (2 * PI * resistor * capacitor));
	return db3Point; 
}

void RCFilter::getCharacteristics(double& resistor, double& capacitor, double& db3Point, bool& type)
{
	
	type = hoogDoorlaat;
	resistor  = this->resistor;
	capacitor = this->capacitor;
	db3Point = (1 / (2 * PI * resistor * capacitor));
}

void RCFilter::getTransfer(const double frequency, double& amplitude, double& phase)
{
	
	//afhankelijk van het type de juiste berekeningen
	if (hoogDoorlaat == false)
	{
		amplitude = (1 / (sqrt(1 + pow((2 * PI * frequency), 2) * pow(resistor, 2) * pow(capacitor, 2))));
		phase = (-atan(2 * PI * frequency * resistor * capacitor));
	}
	else if (hoogDoorlaat == true)
	{
		amplitude = (resistor / (resistor + (1 / (2 * PI * frequency * capacitor))));
		phase = (atan(1/(2 * PI * frequency * resistor * capacitor)));
	}
	
}

void RCFilter::setType(bool type)
{
	hoogDoorlaat = type;
}
