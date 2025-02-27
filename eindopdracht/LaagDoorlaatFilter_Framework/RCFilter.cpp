//****************************************************************************
// TITLE        RCFilter
// DESCRIPTION	Klasse implementatie voor de RCFilter klasse
// FILE			RCFilter.cpp
// AUTHOR		R. Smeets
// DATE			10-aug-2018
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
	this->capacitor = 0.0001;
}

RCFilter::RCFilter(double resistor, double capacitor)
{
	// TODO: invullen

	this->resistor	= resistor;
	this->capacitor = capacitor;
}


// member functies

void RCFilter::setRCValues(const double resistor, const double capacitor)
{
	// TODO: invullen

	this->resistor = resistor;
	this->capacitor = capacitor;
}

void RCFilter::getRCValues(double& resistor, double& capacitor)
{
	// TODO: invullen}

	resistor  = this->resistor;
	capacitor = this->capacitor;
}

double RCFilter::get3dBPoint(void)
{
	// TODO: invullen

	db3Point = (1 / (2 * PI * resistor * capacitor));
}

void RCFilter::getCharacteristics(double& resistor, double& capacitor, double& db3Point)
{
	// TODO: invullen

	resistor  = this->resistor;
	capacitor = this->capacitor;
	db3Point = (1 / (2 * PI * resistor * capacitor));
}

void RCFilter::getTransfer(const double frequency, double& amplitude, double& phase)
{
	// TODO: invullen

	frequency = 
	amplitude = (1 / (sqrt(1 + pow((2 * PI * frequency), 2) * pow(resistor, 2) * pow(capacitor, 2))));
	phase = (-atanh(2 * PI * frequency * resistor * capacitor));
}
