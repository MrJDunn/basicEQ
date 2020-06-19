/*
  ==============================================================================

    LoPass.cpp
    Created: 18 Jun 2020 10:14:41pm
    Author:  Jeff

  ==============================================================================
*/

#include "LoPass.h"

LoPass::LoPass(double sampleRate, int samplesPerBlock, float gain, float frequency, float qFactor) :
	FilterStrategy(sampleRate, samplesPerBlock, gain, frequency, qFactor),
	state(sampleRate, samplesPerBlock, gain, frequency, qFactor)
{
	DBG("LoPass::LoPass");
}

LoPass::~LoPass()
{
	DBG("LoPass::~LoPass");
}

void LoPass::applyFilter(AudioBuffer<float>& buffer)
{
	DBG("LoPass::applyFilter");
	dsp::AudioBlock<float> block(buffer);
	dsp::ProcessContextReplacing<float> context(block);

	int numChannels = (int)context.getInputBlock().getNumChannels();

	filter.process(context);
}

void LoPass::setFilterState(const FilterState& state)
{
	this->state = state;
	filter.state = dsp::IIR::Coefficients<float>::makeLowPass(*state.sampleRate, *state.frequency);
	dsp::ProcessSpec spec{ *state.sampleRate, static_cast<uint32> (*state.samplesPerBlock), 2 };
	filter.prepare(spec);
}