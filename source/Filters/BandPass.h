/*
  ==============================================================================

    BandPass.h
    Created: 18 Jun 2020 10:16:45pm
    Author:  Jeff

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "./FilterStrategy.h"

class BandPass : public FilterStrategy
{
public:
	BandPass(FilterParams);
	~BandPass() override;

	void setFilter(FilterParams params, double sampleRate) override;

};