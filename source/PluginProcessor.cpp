/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TheBasics_eqAudioProcessor::TheBasics_eqAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), filter(new IIRFilter())
#endif
{
	filterState.type = FilterType::BAND;
	filterState.fq = 10000.0;
	filterState.q = 1.0;
	filterState.gain = 1.0;

	DBG("TheBasics_eqAudioProcessor::TheBasics_eqAudioProcessor");
}

TheBasics_eqAudioProcessor::~TheBasics_eqAudioProcessor()
{
	delete filter;
}

//==============================================================================
const String TheBasics_eqAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TheBasics_eqAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TheBasics_eqAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TheBasics_eqAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TheBasics_eqAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TheBasics_eqAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TheBasics_eqAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TheBasics_eqAudioProcessor::setCurrentProgram (int index)
{
}

const String TheBasics_eqAudioProcessor::getProgramName (int index)
{
    return {};
}

void TheBasics_eqAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void TheBasics_eqAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	filter->setCoefficients(IIRCoefficients::makeBandPass(sampleRate, 1000, 1.0));
}

void TheBasics_eqAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TheBasics_eqAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void TheBasics_eqAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());


    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
		filter->processSamples(buffer.getWritePointer(channel), buffer.getNumSamples());
	}

}

//==============================================================================
bool TheBasics_eqAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TheBasics_eqAudioProcessor::createEditor()
{
    return new TheBasics_eqAudioProcessorEditor (*this);
}

//==============================================================================
void TheBasics_eqAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TheBasics_eqAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void TheBasics_eqAudioProcessor::setFilter(FilterParams filterParams)
{
	switch (filterParams.type)
	{
	case FilterType::HI:
		filter->setCoefficients(IIRCoefficients::makeHighPass(getSampleRate(), filterParams.fq, filterParams.q));
		break;
	case FilterType::BAND:
		filter->setCoefficients(IIRCoefficients::makeBandPass(getSampleRate(), filterParams.fq, filterParams.q));
		break;
	case FilterType::LOW:
		filter->setCoefficients(IIRCoefficients::makeLowPass(getSampleRate(), filterParams.fq, filterParams.q));
		break;
	default:
		break;
	}
	filterState = filterParams;
}

void TheBasics_eqAudioProcessor::setFq(double newFreuency)
{
	filterState.fq = newFreuency;
	setFilter(filterState);
}

void TheBasics_eqAudioProcessor::setQ(double newQ)
{
	filterState.q = newQ;
	setFilter(filterState);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TheBasics_eqAudioProcessor();
}
