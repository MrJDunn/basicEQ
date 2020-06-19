/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Graphics/SpectrogramWindow.h"
#include "Filters/FilterStrategy.h"

//==============================================================================
/**
*/
class TheBasics_eqAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    TheBasics_eqAudioProcessorEditor (TheBasics_eqAudioProcessor&);
    ~TheBasics_eqAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
	//==============================================================================
	void setup();

    TheBasics_eqAudioProcessor& processor;

	Slider sFrequency{"fg"};
	Slider sQFactor{"q"};

	ComboBox cFilterType;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TheBasics_eqAudioProcessorEditor)
};
