//****************************************************************************
// TITLE        FrequencyRange
// DESCRIPTION	Klasse definitie voor FrequencyRange
// FILE			FrequencyRange.h
// AUTHOR		R. Schoonus en J.C. Oostdijk
// DATE			9-01-2019
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
	FrequencyRange();
	FrequencyRange(double freqBegin, double freqEnd, unsigned int nPoints);
	bool setRange(double freqBegin, double freqEnd, unsigned int nPoints);
	void getRange(double& freqBegin, double& freqEnd, unsigned int& nPoints);
};
