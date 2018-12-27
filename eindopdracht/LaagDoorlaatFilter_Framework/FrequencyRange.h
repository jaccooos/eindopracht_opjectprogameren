//****************************************************************************
// TITLE        FrequencyRange
// DESCRIPTION	Klasse definitie voor FrequencyRange
// FILE			FrequencyRange.h
// AUTHOR		R. Smeets
// DATE			11-aug-2018
// ***************************************************************************

#pragma once

// klasse FrequencyRange

class FrequencyRange
{
private:
	double freqBegin = 1;
	double freqEnd = 1000;
	unsigned int nPoints = 10000;

public:
	FrequencyRange::FrequencyRange();
	FrequencyRange::FrequencyRange(double freqBegin, double freqEnd, unsigned int nPoints);
	bool FrequencyRange::setRange(double freqBegin, double freqEnd, unsigned int nPoints);
	void FrequencyRange::getRange(double& freqBegin, double& freqEnd, unsigned int& nPoints);
};
