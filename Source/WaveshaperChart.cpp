//
//  WaveshaperChart.cpp
//  FM Plugin
//
//  Created by Keary Mobley on 10/22/22.
//  Copyright © 2022 JUCE. All rights reserved.
//

#include "WaveshaperChart.h"
    

WaveshaperChart::WaveshaperChart(){}
WaveshaperChart::~WaveshaperChart(){}


void WaveshaperChart::paint(Graphics &g){
    g.setColour(juce::Colours::skyblue);
    auto textBox = getLocalBounds().removeFromTop(50);
    g.setFont(textBox.getHeight()/3);
    g.drawText(title, textBox, juce::Justification::centred, true);
    g.setColour(juce::Colours::peachpuff);
    Path wavePath;
    
    
    
    auto chartArea = getLocalBounds().reduced(10, 50);
    g.drawRect(chartArea);
    auto w = chartArea.getWidth();
    auto h = chartArea.getHeight();
    auto startx = chartArea.getX();
    auto starty = chartArea.getCentreY();
    g.setColour (getLookAndFeel().findColour
                 (Slider::thumbColourId));
    
    //TODO: Remove Magic Numbers
    //w is used to make waves start in the center
    //And to create enough sample points to span the width of the graph.
    if (plotSetting == ChartSettingsEnum::straightChart)
    {
        wavePath.startNewSubPath (startx, starty);
        for (float x = plotMin*w/2; x < plotMax*w/2; ++x)
        {
            auto delta = starty - getChebyshevSignal(x/w*2);
            wavePath.lineTo (startx++, delta);
        }
        g.strokePath (wavePath, PathStrokeType (2.0f));
    }
    
    else if (plotSetting == ChartSettingsEnum::sinChart)
    {
        wavePath.startNewSubPath (startx, starty);
        for (float x = (plotMin)*w; x < plotMax*w; ++x)
        {
            auto delta = starty - getChebyshevSignal(sin(2*M_PI* x/w));
            wavePath.lineTo (startx++ , delta);
        }
        g.strokePath (wavePath, PathStrokeType (2.0f));
    }
    else
    {
        //Display No Input
        g.drawText("No Input", chartArea, juce::Justification::centred, true);
    }
}
void WaveshaperChart::setTitle(String titleString)
{
    title = titleString;
}

void WaveshaperChart::setChebyshevAmplitudes(float amplitude, SineWaveVoice::ChebyshevLevels chebyshevLevel)
{
    chebyshevAmplitudes[chebyshevLevel] = amplitude;
    repaint();
}
void WaveshaperChart::plotChebyshev(float min, float max, ChartSettingsEnum setting)
{
    plotSetting = setting;
    plotMin = min;
    plotMax = max;
}

float WaveshaperChart::chebyshevCalculation(int chebyshev, float x)
{
    if (chebyshev == SineWaveVoice::chebyshevLevel0)
    {
        return 1;
    }
    if (chebyshev == SineWaveVoice::chebyshevLevel1)
    {
        return x;
    }
    else
    {
        return 2 * x * chebyshevCalculation(chebyshev-1, x) - chebyshevCalculation(chebyshev-2, x);
    }
}

float WaveshaperChart::getChebyshevSignal(float currentSample)
{
    float chebyshevSignal = 0.0;
    for (auto chebyshevLevel = (int) SineWaveVoice::chebyshevLevel1; chebyshevLevel < SineWaveVoice::chebyshevLevelEnd; chebyshevLevel++)
    {
        chebyshevSignal += chebyshevAmplitudes[chebyshevLevel] * chebyshevCalculation(chebyshevLevel, currentSample);
    }
    return chebyshevSignal;
}
