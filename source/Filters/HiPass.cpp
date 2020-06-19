/*
  ==============================================================================

    HiPass.cpp
    Created: 10 Jan 2020 4:48:59pm
    Author:  Jeff

  ==============================================================================
*/

#include "HiPass.h"

HiPass::HiPass(double sampleRate, int samplesPerBlock, float gain, float frequency, float qFactor) : 
	FilterStrategy(sampleRate, samplesPerBlock, gain, frequency, qFactor),
	state(sampleRate, samplesPerBlock, gain, frequency, qFactor)
{
	DBG("HiPass::HiPass");
}

HiPass::~HiPass()
{
	DBG("HiPass::~HiPass");
}

void HiPass::applyFilter(AudioBuffer<float>& buffer)
{
	DBG("HiPass::applyFilter");
	dsp::AudioBlock<float> block(buffer);
	dsp::ProcessContextReplacing<float> context(block);
	filter.process(context);
}

void HiPass::setFilterState(const FilterState& state)
{
	this->state = state;
	filter.state = dsp::IIR::Coefficients<float>::makeHighPass(*state.sampleRate, *state.frequency);
	dsp::ProcessSpec spec{ *state.sampleRate, static_cast<uint32> (*state.samplesPerBlock), 2 };
	filter.prepare(spec);
}
