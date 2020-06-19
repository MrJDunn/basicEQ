/*
  ==============================================================================

    SpectrogramWindow.h
    Created: 19 Jun 2020 8:42:51am
    Author:  Jeff

  ==============================================================================
*/
#include "../JuceLibraryCode/JuceHeader.h"

#pragma once

//==============================================================================
class SpectrogramWindow : public AudioAppComponent,
							 private Timer
{
public:
	SpectrogramWindow()
		: forwardFFT(fftOrder), spectrogramImage(Image::RGB, 512, 512, true)
	{
		setOpaque(true);
		setAudioChannels(2, 0);
		startTimerHz(60);
		setSize(700, 500);
	}

	~SpectrogramWindow() override
	{
		shutdownAudio();
	}

	//==============================================================================
	void prepareToPlay(int, double) override {}
	void releaseResources() override {}

	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override
	{
		if (bufferToFill.buffer->getNumChannels() > 0)
		{
			auto* channelData = bufferToFill.buffer->getReadPointer(0, bufferToFill.startSample);

			for (auto i = 0; i < bufferToFill.numSamples; ++i)
				pushNextSampleIntoFifo(channelData[i]);
		}
	}

	//==============================================================================
	void paint(Graphics& g) override
	{
		g.fillAll(Colours::black);

		g.setOpacity(1.0f);
		g.drawImage(spectrogramImage, getLocalBounds().toFloat());
	}

	void timerCallback() override 
	{
		if (nextFFTBlockReady)
		{
			drawNextLineOfSpectrogram();
			nextFFTBlockReady = false;
			repaint();
		}
	}

	void pushNextSampleIntoFifo(float sample) noexcept
	{
		if (fifoIndex == fftSize)
		{
			if (!nextFFTBlockReady)
			{
				std::fill(fftData.begin(), fftData.end(), 0.0f);
				std::copy(fifo.begin(), fifo.end(), fftData.begin());
				nextFFTBlockReady = true;
			}

			fifoIndex = 0;
		}

		fifo[fifoIndex++] = sample;
	}

	void drawNextLineOfSpectrogram() 
	{
		auto rightHandEdge = spectrogramImage.getWidth() - 1;
		auto imageHeight = spectrogramImage.getHeight();

		spectrogramImage.moveImageSection(0, 0, 1, 0, rightHandEdge, imageHeight);

		forwardFFT.performFrequencyOnlyForwardTransform(fftData.data());

		auto maxLevel = FloatVectorOperations::findMinAndMax(fftData.data(), fftSize / 2);

		for (auto y = 1; y < imageHeight; ++y)
		{
			auto skewedProportionY = 1.0f - std::exp(std::log(y / (float)imageHeight) * 0.2f);
			auto fftDataIndex = (size_t)jlimit(0, fftSize / 2, (int)(skewedProportionY * fftSize / 2));
			auto level = jmap(fftData[fftDataIndex], 0.0f, jmax(maxLevel.getEnd(), 1e-5f), 0.0f, 1.0f);

			spectrogramImage.setPixelAt(rightHandEdge, y, Colour::fromHSV(level, 1.0f, level, 1.0f));
		}
	}

	static constexpr auto fftOrder = 10;
	static constexpr auto fftSize = 1 << fftOrder;

private:
	dsp::FFT forwardFFT;
	std::array<float, fftSize> fifo;
	std::array<float, fftSize * 2> fftData;
	int fifoIndex = 0;
	bool nextFFTBlockReady = false;

	Image spectrogramImage;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SpectrogramWindow)
};
