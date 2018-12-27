//****************************************************************************
// TITLE        FrequencyRange
// DESCRIPTION	Klasse implementatie voor de FrequencyRange klasse
// FILE			FrequencyRange.cpp
// AUTHOR		R. Smeets
// DATE			10-aug-2018
// ***************************************************************************

#include "FrequencyRange.h"

// Constructors:

FrequencyRange::FrequencyRange()
{
	freqBegin = 1;
	FreqEnd = 1000;
	nPoints = 10000;
}

FrequencyRange::FrequencyRange(double freqBegin, double freqEnd, unsigned int nPoints)
{
	this->freqBegin = freqBegin;
	this->freqEnd = freqEnd;
	this->nPoints = nPoints;
}

// member functions

bool FrequencyRange::setRange(double freqBegin, double freqEnd, unsigned int nPoints)
{
	this->freqBegin = freqBegin;
	this->freqEnd = freqEnd;
	this->nPoints = nPoints;
}

void FrequencyRange::getRange(double& freqBegin, double& freqEnd, unsigned int& nPoints)
{
	freqBegin = this->freqBegin;
	freqEnd = this->freqEnd;
	nPoints = this->nPoints;
}
