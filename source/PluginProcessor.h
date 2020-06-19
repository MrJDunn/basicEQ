/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Filters/FilterStrategy.h"
#include "Filters/HiPass.h"
#include "Filters/BandPass.h"
#include "Filters/LoPass.h"

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
	FilterStrategy::FilterParams filterState;

	void setFilter(FilterStrategy::FilterParams);
	void setFq(double);
	void setQ(double);

private:
	//==============================================================================
	//BandPass& bp;
	IIRFilter* filter = nullptr;
	FilterStrategy* filterStrategy = nullptr;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TheBasics_eqAudioProcessor)
};
