/*
  ==============================================================================

    BandPass.cpp
    Created: 18 Jun 2020 10:16:45pm
    Author:  Jeff

  ==============================================================================
*/

#include "BandPass.h"

BandPass::BandPass(FilterStrategy::FilterParams params) : FilterStrategy(params)
{
	DBG("BandPass::BandPass");
}

BandPass::~BandPass()
{
	DBG("BandPass::~BandPass");
}

void BandPass::setFilter(FilterParams filterParams, double sampleRate)
{
	filter->setCoefficients(IIRCoefficients::makeBandPass(sampleRate, filterParams.fq, filterParams.q));
}