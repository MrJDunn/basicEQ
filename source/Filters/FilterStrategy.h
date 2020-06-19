/*
  ==============================================================================

    FilterStrategy.h
    Created: 13 Jan 2020 3:41:23pm
    Author:  Jeff

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class FilterStrategy
{
public:
	struct FilterState
	{
		FilterState(double sampleRate, int samplesPerBlock, float gain, float frequency, float qFactor): 
			sampleRate(&sampleRate), samplesPerBlock(&samplesPerBlock), gain(&gain), frequency(&frequency), qFactor(&qFactor){};
		~FilterState(){};
		
		const FilterState operator= (const FilterState& state)
		{
			return FilterStrategy::FilterState(*state.sampleRate, *state.samplesPerBlock, *state.gain, *state.frequency, *state.qFactor);
		};

		double* sampleRate;
		int* samplesPerBlock;
		float* gain;
		float* frequency;
		float* qFactor;
	};

	FilterStrategy(FilterState);
	FilterStrategy(double sampleRate, int samplesPerBlock, float gain, float frequency, float qFactor);
	virtual ~FilterStrategy();
	void equalise(AudioBuffer<float>&);
	virtual void setFilterState(const FilterState&);

protected:
	virtual void applyFilter(AudioBuffer<float>&) = 0;
private:
	FilterState state;
};