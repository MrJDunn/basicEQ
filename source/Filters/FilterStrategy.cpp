/*
  ==============================================================================

    FilterStrategy.cpp
    Created: 13 Jan 2020 3:41:23pm
    Author:  Jeff

  ==============================================================================
*/

#include "FilterStrategy.h"

FilterStrategy::FilterStrategy(FilterParams params): filterState(params), filter(new IIRFilter())
{
}

FilterStrategy::~FilterStrategy()
{
	delete filter;
}

void FilterStrategy::process(AudioBuffer<float>& buffer, int numberOfChannels)
{
	for (int channel = 0; channel < numberOfChannels; ++channel)
	{
		filter->processSamples(buffer.getWritePointer(channel), buffer.getNumSamples());
	}
}