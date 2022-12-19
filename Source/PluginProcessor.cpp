
//
//  PluginProcessor.hpp
//  AudioPluginDemo - All
//
//  Copyright © 2022 JUCE. All rights reserved.
//

/*
  ==============================================================================

   This file is part of the JUCE examples.
   Copyright (c) 2020 - Raw Material Software Limited

   The code included in this file is provided under the terms of the ISC license
   http://www.isc.org/downloads/software-support-policy/isc-license. Permission
   To use, copy, modify, and/or distribute this software for any purpose with or
   without fee is hereby granted provided that the above copyright notice and
   this permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES,
   WHETHER EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR
   PURPOSE, ARE DISCLAIMED.

  ==============================================================================
*/

/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

 name:                  FMPlugin
 version:               1.0.0
 vendor:                JUCE
 website:               http://juce.com
 description:           Synthesiser audio plugin.

 dependencies:          juce_audio_basics, juce_audio_devices, juce_audio_formats,
                        juce_audio_plugin_client, juce_audio_processors,
                        juce_audio_utils, juce_core, juce_data_structures,
                        juce_events, juce_graphics, juce_gui_basics, juce_gui_extra
 exporters:             xcode_mac, vs2017, vs2019, linux_make, xcode_iphone, androidstudio

 moduleFlags:           JUCE_STRICT_REFCOUNTEDPOINTER=1

 type:                  AudioProcessor
 mainClass:             JuceDemoPluginAudioProcessor

 useLocalCopy:          1

 pluginCharacteristics: pluginIsSynth, pluginWantsMidiIn, pluginProducesMidiOut,
                        pluginEditorRequiresKeys
 extraPluginFormats:    AUv3

 END_JUCE_PIP_METADATA

*******************************************************************************/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SineWaveVoice.h"
#include "SineWaveSound.h"
//TODO: Change Juce Header include to ifndef or pragma
#include <JuceHeader.h>

//==============================================================================
JuceDemoPluginAudioProcessor::JuceDemoPluginAudioProcessor()
    : AudioProcessor (getBusesProperties()),
      state (*this, nullptr, "state",
             { std::make_unique<AudioParameterFloat> ("gain",  "Gain",           NormalisableRange<float> (0.0f, 1.0f), 1.0f),
              std::make_unique<AudioParameterFloat> ("delay", "Delay Feedback", NormalisableRange<float> (0.0f, 100.0f), 0.0f),
             std::make_unique<AudioParameterFloat> ("mod", "Modulation", NormalisableRange<float> (0.0f, 100.0f), 0.5f),
          std::make_unique<AudioParameterInt> ("indexNum", "Index Numerator", 2, 99, 2),
          std::make_unique<AudioParameterInt> ("indexDen", "Index Denominator", 2, 20, 2), //min, max, default
          std::make_unique<AudioParameterFloat>("attack", "Attack", NormalisableRange<float>(0.0f, 100.0f), 0.5f),
          std::make_unique<AudioParameterFloat>("sustain", "Sustain", NormalisableRange<float>(0.0f, 100.0f), 0.5f),
          std::make_unique<AudioParameterFloat>("release", "Release", NormalisableRange<float>(0.0f, 100.0f), 0.5f),
          
          std::make_unique<AudioParameterFloat>("mattack", "mAttack", NormalisableRange<float>(0.0f, 100.0f), 0.5f),
          std::make_unique<AudioParameterFloat>("msustain", "mSustain", NormalisableRange<float>(0.0f, 100.0f), 0.5f),
          std::make_unique<AudioParameterFloat>("mrelease", "mRelease", NormalisableRange<float>(0.0f, 100.0f), 0.5f),
          std::make_unique<AudioParameterInt> ("expLineEnv", "Index Numerator", 0, 3, 0),
          std::make_unique<AudioParameterInt> ("expLinModEnv", "Index Denominator", 0, 3, 0),
          std::make_unique<AudioParameterFloat>("chebyshevAmp1", "Chebyshev Amplitude", NormalisableRange<float>(-100.0f, 100.0f), 0.5f),
          std::make_unique<AudioParameterFloat>("chebyshevAmp2", "Chebyshev Amplitude", NormalisableRange<float>(-100.0f, 100.0f), 0.5f),
          std::make_unique<AudioParameterFloat>("chebyshevAmp3", "Chebyshev Amplitude", NormalisableRange<float>(-100.0f, 100.0f), 0.5f),
          std::make_unique<AudioParameterFloat>("chebyshevAmp4", "Chebyshev Amplitude", NormalisableRange<float>(-100.0f, 100.0f), 0.5f),
          std::make_unique<AudioParameterFloat>("chebyshevAmp5", "Chebyshev Amplitude", NormalisableRange<float>(-100.0f, 100.0f), 0.5f),
          std::make_unique<AudioParameterFloat>("chebyshevAmp6", "Chebyshev Amplitude", NormalisableRange<float>(-100.0f, 100.0f), 0.5f),
          std::make_unique<AudioParameterFloat>("chebyshevAmp7", "Chebyshev Amplitude", NormalisableRange<float>(-100.0f, 100.0f), 0.5f),
          std::make_unique<AudioParameterFloat>("chebyshevAmp8", "Chebyshev Amplitude", NormalisableRange<float>(-100.0f, 100.0f), 0.5f),
          std::make_unique<AudioParameterFloat>("chebyshevAmp9", "Chebyshev Amplitude", NormalisableRange<float>(-100.0f, 100.0f), 0.5f)
          //min, max, default
          })
{
    // Add a sub-tree to store the state of our UI
    state.state.addChild ({ "uiState", { { "width",  1200 }, { "height", 800 } }, {} }, -1, nullptr);

    initialiseSynth();
}

//==============================================================================
bool JuceDemoPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    // Only mono/stereo and input/output must have same layout
    const auto& mainOutput = layouts.getMainOutputChannelSet();
    const auto& mainInput  = layouts.getMainInputChannelSet();

    // input and output layout must either be the same or the input must be disabled altogether
    if (! mainInput.isDisabled() && mainInput != mainOutput)
        return false;

    // do not allow disabling the main buses
    if (mainOutput.isDisabled())
        return false;

    // only allow stereo and mono
    if (mainOutput.size() > 2)
        return false;

    return true;
}

void JuceDemoPluginAudioProcessor::prepareToPlay (double newSampleRate, int /*samplesPerBlock*/)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    synth.setCurrentPlaybackSampleRate (newSampleRate);
    keyboardState.reset();

    if (isUsingDoublePrecision())
    {
        delayBufferDouble.setSize (2, 12000);
        delayBufferFloat .setSize (1, 1);
    }
    else
    {
        delayBufferFloat .setSize (2, 12000);
        delayBufferDouble.setSize (1, 1);
    }

    reset();
}

void JuceDemoPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    keyboardState.reset();
}

void JuceDemoPluginAudioProcessor::reset()
{
    // Use this method as the place to clear any delay lines, buffers, etc, as it
    // means there's been a break in the audio's continuity.
    delayBufferFloat .clear();
    delayBufferDouble.clear();
}

//==============================================================================
void JuceDemoPluginAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    jassert (! isUsingDoublePrecision());
    process (buffer, midiMessages, delayBufferFloat);
}

void JuceDemoPluginAudioProcessor::processBlock (AudioBuffer<double>& buffer, MidiBuffer& midiMessages)
{
    jassert (isUsingDoublePrecision());
    process (buffer, midiMessages, delayBufferDouble);
}

//==============================================================================
bool JuceDemoPluginAudioProcessor::hasEditor() const                                  { return true; }

AudioProcessorEditor* JuceDemoPluginAudioProcessor::createEditor()
{
    return new JuceDemoPluginAudioProcessorEditor (*this);
}

//==============================================================================
const String JuceDemoPluginAudioProcessor::getName() const                            { return "AudioPluginDemo"; }
bool JuceDemoPluginAudioProcessor::acceptsMidi() const                                 { return true; }
bool JuceDemoPluginAudioProcessor::producesMidi() const                                { return true; }
double JuceDemoPluginAudioProcessor::getTailLengthSeconds() const                      { return 0.0; }

//==============================================================================
int JuceDemoPluginAudioProcessor::getNumPrograms()                                     { return 0; }
int JuceDemoPluginAudioProcessor::getCurrentProgram()                                  { return 0; }
void JuceDemoPluginAudioProcessor::setCurrentProgram (int)                             {}
const String JuceDemoPluginAudioProcessor::getProgramName (int)                        { return {}; }
void JuceDemoPluginAudioProcessor::changeProgramName (int, const String&)              {}

//==============================================================================
void JuceDemoPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // Store an xml representation of our state.
    if (auto xmlState = state.copyState().createXml())
        copyXmlToBinary (*xmlState, destData);
}

void JuceDemoPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // Restore our plug-in's state from the xml representation stored in the above
    // method.
    if (auto xmlState = getXmlFromBinary (data, sizeInBytes))
        state.replaceState (ValueTree::fromXml (*xmlState));
}

//==============================================================================
void JuceDemoPluginAudioProcessor::updateTrackProperties (const TrackProperties& properties)
{
    {
        const ScopedLock sl (trackPropertiesLock);
        trackProperties = properties;
    }

    MessageManager::callAsync ([this]
    {
        if (auto* editor = dynamic_cast<JuceDemoPluginAudioProcessorEditor*> (getActiveEditor()))
             editor->updateTrackProperties();
    });
}

JuceDemoPluginAudioProcessor::TrackProperties JuceDemoPluginAudioProcessor::getTrackProperties() const
{
    const ScopedLock sl (trackPropertiesLock);
    return trackProperties;
}


//==============================================================================
template <typename FloatType>
void JuceDemoPluginAudioProcessor::process (AudioBuffer<FloatType>& buffer, MidiBuffer& midiMessages, AudioBuffer<FloatType>& delayBuffer)
{
    auto gainParamValue  = state.getParameter ("gain") ->getValue();
    auto delayParamValue = state.getParameter ("delay")->getValue();
    auto modParamValue = state.getParameter ("mod")->getValue();
    auto numParamValue = state.getParameter ("indexNum")->getValue();
    auto denParamValue = state.getParameter ("indexDen")->getValue();
    auto chebyshevAmp1ParamValue = state.getParameter ("chebyshevAmp1")->getValue();
    auto chebyshevAmp2ParamValue = state.getParameter ("chebyshevAmp2")->getValue();
    auto chebyshevAmp3ParamValue = state.getParameter ("chebyshevAmp3")->getValue();
    auto chebyshevAmp4ParamValue = state.getParameter ("chebyshevAmp4")->getValue();
    auto chebyshevAmp5ParamValue = state.getParameter ("chebyshevAmp5")->getValue();
    auto chebyshevAmp6ParamValue = state.getParameter ("chebyshevAmp6")->getValue();
    auto chebyshevAmp7ParamValue = state.getParameter ("chebyshevAmp7")->getValue();
    auto chebyshevAmp8ParamValue = state.getParameter ("chebyshevAmp8")->getValue();
    auto chebyshevAmp9ParamValue = state.getParameter ("chebyshevAmp9")->getValue();

    auto att = state.getParameter ("attack")->getValue();
    auto sus = state.getParameter ("sustain")->getValue();
    auto rel = state.getParameter ("release")->getValue();
    
    auto matt = state.getParameter ("mattack")->getValue();
    auto msus = state.getParameter ("msustain")->getValue();
    auto mrel = state.getParameter ("mrelease")->getValue();
    
    
    auto lexenv = state.getParameter ("expLineEnv")->getValue();
    auto lexmenv = state.getParameter ("expLinModEnv")->getValue();


    auto numSamples = buffer.getNumSamples();

    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (auto i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear (i, 0, numSamples);

    //synth.defineModulation(1.0, delayParamValue);
    // Now pass any incoming midi messages to our keyboard state object, and let it
    // add messages to the buffer if the user is clicking on the on-screen keys
    keyboardState.processNextMidiBuffer (midiMessages, 0, numSamples, true);

    for (int i = 0; i < synth.getNumVoices(); i++) {
        (synth.getVoice(i))->controllerMoved(0, 100 * modParamValue);
        (synth.getVoice(i))->controllerMoved(1, 100 * numParamValue);
        (synth.getVoice(i))->controllerMoved(2, 100 * denParamValue);
        (synth.getVoice(i))->controllerMoved(3, 100 * att);
        (synth.getVoice(i))->controllerMoved(4, 100 * sus);

        (synth.getVoice(i))->controllerMoved(5, 65 + 35 * (rel));
        
        
        (synth.getVoice(i))->controllerMoved(6, 100 * matt);
        (synth.getVoice(i))->controllerMoved(7, 100 * msus);
        (synth.getVoice(i))->controllerMoved(8, 65 + 35 * (mrel));
        (synth.getVoice(i))->controllerMoved(14, 100 * chebyshevAmp1ParamValue);
        (synth.getVoice(i))->controllerMoved(15, 100 * chebyshevAmp2ParamValue);
        (synth.getVoice(i))->controllerMoved(16, 100 * chebyshevAmp3ParamValue);
        (synth.getVoice(i))->controllerMoved(17, 100 * chebyshevAmp4ParamValue);
        (synth.getVoice(i))->controllerMoved(18, 100 * chebyshevAmp5ParamValue);
        (synth.getVoice(i))->controllerMoved(19, 100 * chebyshevAmp6ParamValue);
        (synth.getVoice(i))->controllerMoved(20, 100 * chebyshevAmp7ParamValue);
        (synth.getVoice(i))->controllerMoved(21, 100 * chebyshevAmp8ParamValue);
        (synth.getVoice(i))->controllerMoved(22, 100 * chebyshevAmp9ParamValue);
        
        
        //This warrants an explanation....
        for (int j = 9; j < 13; j++){
            if (lexenv < 2) {
                if (j % 2== lexenv) {
                    (synth.getVoice(i))->controllerMoved(j, lexenv);
                } else {
                    (synth.getVoice(i))->controllerMoved(j, lexenv);
                }
            } else {
                if (j % 2 == lexmenv) {
                    (synth.getVoice(i))->controllerMoved(j, lexmenv);
                } else {
                    (synth.getVoice(i))->controllerMoved(j, lexmenv);
                }
            }
        }
    }
    // and now get our synth to process these midi events and generate its output.
    synth.renderNextBlock (buffer, midiMessages, 0, numSamples);

    // Apply our delay effect to the new output..
    applyDelay (buffer, delayBuffer, delayParamValue);

    // Apply our gain change to the outgoing data..
    applyGain (buffer, delayBuffer, gainParamValue);
    

    // Now ask the host for the current time so we can store it to be displayed later...
    updateCurrentTimeInfoFromHost();
}

template <typename FloatType>
void JuceDemoPluginAudioProcessor::applyGain (AudioBuffer<FloatType>& buffer, AudioBuffer<FloatType>& delayBuffer, float gainLevel)
{
    ignoreUnused (delayBuffer);

    for (auto channel = 0; channel < getTotalNumOutputChannels(); ++channel)
        buffer.applyGain (channel, 0, buffer.getNumSamples(), gainLevel);
}

template <typename FloatType>
void JuceDemoPluginAudioProcessor::applyDelay (AudioBuffer<FloatType>& buffer, AudioBuffer<FloatType>& delayBuffer, float delayLevel)
{
    auto numSamples = buffer.getNumSamples();

    auto delayPos = 0;

    for (auto channel = 0; channel < getTotalNumOutputChannels(); ++channel)
    {
        auto channelData = buffer.getWritePointer (channel);
        auto delayData = delayBuffer.getWritePointer (jmin (channel, delayBuffer.getNumChannels() - 1));
        delayPos = delayPosition;

        for (auto i = 0; i < numSamples; ++i)
        {
            auto in = channelData[i];
            channelData[i] += delayData[delayPos];
            delayData[delayPos] = (delayData[delayPos] + in) * delayLevel;

            if (++delayPos >= delayBuffer.getNumSamples())
                delayPos = 0;
        }
    }
    delayPosition = delayPos;
}

void JuceDemoPluginAudioProcessor::initialiseSynth()
{
    auto numVoices = 8;

    // Add some voices...
    for (auto i = 0; i < numVoices; ++i)
        synth.addVoice (new SineWaveVoice());

    // ..and give the synth a sound to play
    synth.addSound (new SineWaveSound());
}

void JuceDemoPluginAudioProcessor::updateCurrentTimeInfoFromHost()
{
    const auto newInfo = [&]
    {
        if (auto* ph = getPlayHead())
        {
            AudioPlayHead::CurrentPositionInfo result;

            if (ph->getCurrentPosition (result))
                return result;
        }

        // If the host fails to provide the current time, we'll just use default values
        AudioPlayHead::CurrentPositionInfo result;
        result.resetToDefault();
        return result;
    }();

    lastPosInfo.set (newInfo);
}

juce::AudioProcessor::BusesProperties JuceDemoPluginAudioProcessor::getBusesProperties()
{
    return BusesProperties().withInput  ("Input",  AudioChannelSet::stereo(), true)
                            .withOutput ("Output", AudioChannelSet::stereo(), true);
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JuceDemoPluginAudioProcessor();
}
