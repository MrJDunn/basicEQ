/*
  ==============================================================================

    HiPass.h
    Created: 10 Jan 2020 4:48:59pm
    Author:  Jeff

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "./FilterStrategy.h"

class HiPass : public FilterStrategy
{
public:
	HiPass(FilterParams);
	~HiPass() override;
	
	void setFilter(FilterParams params, double sampleRate) override;

};