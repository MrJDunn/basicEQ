/*
  ==============================================================================

    LoPass.cpp
    Created: 18 Jun 2020 10:14:41pm
    Author:  Jeff

  ==============================================================================
*/

#include "LoPass.h"

LoPass::LoPass(FilterStrategy::FilterParams params) : FilterStrategy(params)
{
	DBG("LoPass::LoPass");
}

LoPass::~LoPass()
{
	DBG("LoPass::~LoPass");
}

void LoPass::setFilter(FilterParams filterParams, double sampleRate)
{
	filter->setCoefficients(IIRCoefficients::makeLowPass(sampleRate, filterParams.fq, filterParams.q));
}