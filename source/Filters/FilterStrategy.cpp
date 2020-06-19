/*
  ==============================================================================

    FilterStrategy.cpp
    Created: 13 Jan 2020 3:41:23pm
    Author:  Jeff

  ==============================================================================
*/

#include "FilterStrategy.h"

FilterStrategy::FilterStrategy(FilterState state): state(state)
{
}

FilterStrategy::FilterStrategy(double sampleRate, int samplesPerBlock, float gain, float frequency, float qFactor) :
	state(sampleRate, samplesPerBlock, gain, frequency, qFactor)
{
	DBG("FilterStrategy::FilterStrategy");
}

FilterStrategy::~FilterStrategy()
{
	DBG("FilterStrategy::~FilterStrategy");
}

void FilterStrategy::equalise(AudioBuffer<float>& buffer)
{
	applyFilter(buffer);
}

void FilterStrategy::setFilterState(const FilterState& state)
{
	this->state = state;
}