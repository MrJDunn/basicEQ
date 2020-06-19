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
	LoPass(double, int, float, float, float);
	~LoPass() override;
private:
	FilterState state;
	dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> filter;
	void setFilterState(const FilterState&) override;
	void applyFilter(AudioBuffer<float>&) override;
};