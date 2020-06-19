/*
  ==============================================================================

    BandPass.cpp
    Created: 18 Jun 2020 10:16:45pm
    Author:  Jeff

  ==============================================================================
*/

#include "BandPass.h"

BandPass::BandPass(double sampleRate, int samplesPerBlock, float gain, float frequency, float qFactor) :
	FilterStrategy(sampleRate, samplesPerBlock, gain, frequency, qFactor),
	state(sampleRate, samplesPerBlock, gain, frequency, qFactor)
{
	DBG("BandPass::BandPass");
}

BandPass::~BandPass()
{
	DBG("BandPass::~BandPass");
}

void BandPass::applyFilter(AudioBuffer<float>& buffer)
{
	DBG("BandPass::applyFilter");
	dsp::AudioBlock<float> block(buffer);
	dsp::ProcessContextReplacing<float> context(block);
	filter.process(context);
}

void BandPass::setFilterState(const FilterState& state)
{
	this->state = state;
	filter.state = dsp::IIR::Coefficients<float>::makeLowPass(*state.sampleRate, *state.frequency);
	dsp::ProcessSpec spec{ *state.sampleRate, static_cast<uint32> (*state.samplesPerBlock), 2 };
	filter.prepare(spec);
}