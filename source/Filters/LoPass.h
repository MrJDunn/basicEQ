/*
  ==============================================================================

    LoPass.h
    Created: 18 Jun 2020 10:14:41pm
    Author:  Jeff

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "./FilterStrategy.h"

class LoPass : public FilterStrategy
{
public:
	LoPass(FilterParams);
	~LoPass() override;

	void setFilter(FilterParams params, double sampleRate) override;

};