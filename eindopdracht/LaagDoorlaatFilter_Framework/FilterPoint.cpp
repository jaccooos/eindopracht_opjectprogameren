//****************************************************************************
// TITLE        FilterPoint
// DESCRIPTION	Klasse implementatie voor de FilterPoint klasse
// FILE			FilterPoint.cpp
// AUTHOR		R. Smeets
// DATE			10-aug-2018
// ***************************************************************************

#include "FilterPoint.h"

FilterPoint::FilterPoint()
{
	this->frequency = 0;
	this->transfer = 0;
	this->phase = 0;
}

FilterPoint::FilterPoint(double frequency, double transfer, double phase)
{
	this->frequency = frequency;
	this->transfer = transfer;
	this->phase = phase;
}

void FilterPoint::getFilterPoint(double& frequency, double& transfer, double& phase)
{
	frequency = this->frequency;
	transfer = this->transfer;
	phase = this->phase;
}

void FilterPoint::setFilterPoint(double frequency, double transfer, double phase)
{
	this->frequency = frequency;
	this->transfer = transfer;
	this->phase = phase;
}

