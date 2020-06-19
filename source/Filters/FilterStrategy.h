/*
  ==============================================================================

    FilterStrategy.h
    Created: 13 Jan 2020 3:41:23pm
    Author:  Jeff

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class FilterStrategy
{
public:
	enum FilterType {
		HI = 1, BAND, LOW
	};

	struct FilterParams {
		FilterType type;
		double fq;
		double q;
		double gain;
	};

	FilterStrategy(FilterParams);
	virtual ~FilterStrategy();
	void process(AudioBuffer<float>&,int);
	virtual void setFilter(FilterParams, double) = 0;

protected:
	IIRFilter* filter = nullptr;
private:
	FilterParams filterState;
};