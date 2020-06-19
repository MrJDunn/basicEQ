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
	BandPass(double, int, float, float, float);
	~BandPass() override;
private:
	FilterState state;
	dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> filter;
	void setFilterState(const FilterState&) override;
	void applyFilter(AudioBuffer<float>&) override;
};