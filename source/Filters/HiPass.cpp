/*
  ==============================================================================

    HiPass.cpp
    Created: 10 Jan 2020 4:48:59pm
    Author:  Jeff

  ==============================================================================
*/

#include "HiPass.h"


HiPass::HiPass(FilterStrategy::FilterParams params): FilterStrategy(params)
{
	DBG("HiPass::HiPass");
}

HiPass::~HiPass()
{
	DBG("HiPass::~HiPass");
}

void HiPass::setFilter(FilterParams filterParams, double sampleRate)
{
	filter->setCoefficients(IIRCoefficients::makeHighPass(sampleRate, filterParams.fq, filterParams.q));
}