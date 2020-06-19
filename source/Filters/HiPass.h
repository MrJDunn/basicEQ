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
	HiPass(double, int, float, float, float);
	~HiPass() override;
private:
	FilterState state;
	dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> filter;
	void setFilterState(const FilterState&) override;
	void applyFilter(AudioBuffer<float>&) override;
};