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
	freqBegin = 0.159155;
	freqEnd = 15.9155;
	nPoints = 100;
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
	if (freqBegin == 0 && freqEnd == 0 && nPoints == 0)
	{
		return false;
	}
	else
	{
		if (freqBegin != 0)
		{
			this->freqBegin = freqBegin;
		}
		if (freqEnd != 0)
		{
			this->freqEnd = freqEnd;
		}
		if (nPoints != 0)
		{
			this->nPoints = nPoints;
		}
		return true;
	}
}

void FrequencyRange::getRange(double& freqBegin, double& freqEnd, unsigned int& nPoints)
{
	freqBegin = this->freqBegin;
	freqEnd = this->freqEnd;
	nPoints = this->nPoints;
}
