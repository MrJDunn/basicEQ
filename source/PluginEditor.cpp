/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TheBasics_eqAudioProcessorEditor::TheBasics_eqAudioProcessorEditor(TheBasics_eqAudioProcessor& p)
	: AudioProcessorEditor(&p), processor(p)
{
	setSize(500, 200);
	setup();
}

TheBasics_eqAudioProcessorEditor::~TheBasics_eqAudioProcessorEditor()
{
}

//==============================================================================
void TheBasics_eqAudioProcessorEditor::paint(Graphics& g)
{
	auto area = getLocalBounds();

	g.setGradientFill(ColourGradient(
		getLookAndFeel().findColour(ResizableWindow::backgroundColourId), 0, 0,
		Colour::fromRGB(5, 5, 5), 500, 500, true));
	g.fillAll();

	g.setGradientFill(ColourGradient(
		Colour::fromRGBA(186, 255, 255, 75), getWidth() / 2, -50,
		getLookAndFeel().findColour(MidiKeyboardComponent::ColourIds::shadowColourId), 250, 250, true));

	g.fillAll();
}

void TheBasics_eqAudioProcessorEditor::resized()
{
	auto area = getLocalBounds();

	sFrequency.setBounds(area.removeFromTop(50).reduced(5));
	sQFactor.setBounds(area.removeFromTop(50).reduced(5));
	cFilterType.setBounds(area.removeFromTop(50).reduced(5));
	
}

void TheBasics_eqAudioProcessorEditor::setup()
{
	addAndMakeVisible(sFrequency);
	sFrequency.setRange(1.0, 20000.0);
	sFrequency.setTextValueSuffix("Hz");
	sFrequency.setValue(10000);

	addAndMakeVisible(sQFactor);
	sQFactor.setRange(0.1, 10.0);
	sFrequency.setValue(5.0);

	//bandFrequency.setSliderStyle(Slider::SliderStyle::RotaryHorizontalDrag);
	sFrequency.onValueChange = [this] {
		processor.setFq(sFrequency.getValue());
	};

	sQFactor.onValueChange = [this] {
		processor.setQ(sQFactor.getValue());
	};

	addAndMakeVisible(cFilterType);
	cFilterType.addItem("Hi-Pass", 1);
	cFilterType.addItem("Band-Pass", 2);
	cFilterType.addItem("Lo-Pass", 3);

	cFilterType.onChange = [this]
	{
		auto params = FilterStrategy::FilterParams();
		params.type = FilterStrategy::FilterType(cFilterType.getSelectedId());
		params.fq = sFrequency.getValue();
		params.q = sQFactor.getValue();
		processor.setFilter(params);
	};
	cFilterType.setSelectedId(1);

}
