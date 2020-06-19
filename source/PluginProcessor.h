/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "FilterStrategy.h"
#include "HiPass.h"
#include "BandPass.h"
#include "LoPass.h"

//==============================================================================
/**
*/
class TheBasics_eqAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    TheBasics_eqAudioProcessor();
    ~TheBasics_eqAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	//==============================================================================
	enum FilterType {
		HI = 1, BAND, LOW
	};

	struct FilterParams{
		FilterType type;
		double fq;
		double q;
		double gain;
	};

	FilterParams filterState;

	void setFilter(FilterParams);
	void setFq(double);
	void setQ(double);

private:
	//==============================================================================
	//BandPass& bp;
	IIRFilter* filter = nullptr;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TheBasics_eqAudioProcessor)
};
