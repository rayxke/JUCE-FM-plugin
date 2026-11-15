//
//  PluginProcessor.hpp
//  AudioPluginDemo - All
//
//  Copyright © 2022 JUCE. All rights reserved.
//
//==============================================================================

#pragma once

#include <JuceHeader.h>
#include "SpinLockedPosInfo.h"

/** As the name suggest, this class does the actual audio processing. */
class JuceDemoPluginAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    JuceDemoPluginAudioProcessor();

    ~JuceDemoPluginAudioProcessor() override = default;

    //==============================================================================
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void prepareToPlay (double newSampleRate, int /*samplesPerBlock*/) override;

    void releaseResources() override;

    void reset() override;


    //==============================================================================
    void processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override;

    void processBlock (AudioBuffer<double>& buffer, MidiBuffer& midiMessages) override;

    //==============================================================================
    bool hasEditor() const override;

    AudioProcessorEditor* createEditor() override;

    //==============================================================================
    const String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int) override;
    const String getProgramName (int) override;
    void changeProgramName (int, const String&) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;

    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================
    void updateTrackProperties (const TrackProperties& properties) override;

    TrackProperties getTrackProperties() const;
    
    //==============================================================================
    template <typename FloatType>
    void process (AudioBuffer<FloatType>& buffer, MidiBuffer& midiMessages, AudioBuffer<FloatType>& delayBuffer);
    
    template <typename FloatType>
    void applyGain (AudioBuffer<FloatType>& buffer, AudioBuffer<FloatType>& delayBuffer, float gainLevel);

    template <typename FloatType>
    void applyDelay (AudioBuffer<FloatType>& buffer, AudioBuffer<FloatType>& delayBuffer, float delayLevel);

    void initialiseSynth();

    void updateCurrentTimeInfoFromHost();

    static BusesProperties getBusesProperties();
    
    AudioBuffer<float> delayBufferFloat;
    AudioBuffer<double> delayBufferDouble;

    int delayPosition = 0;

    Synthesiser synth;

    CriticalSection trackPropertiesLock;
    TrackProperties trackProperties;

    //==============================================================================
    // These properties are public so that our editor component can access them
    // A bit of a hacky way to do it, but it's only a demo! Obviously in your own
    // code you'll do this much more neatly..

    // this is kept up to date with the midi messages that arrive, and the UI component
    // registers with it so it can represent the incoming messages
    MidiKeyboardState keyboardState;

    // this keeps a copy of the last set of time info that was acquired during an audio
    // callback - the UI component will read this and display it.
    SpinLockedPosInfo lastPosInfo;

    // Our plug-in's current state
    AudioProcessorValueTreeState state;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceDemoPluginAudioProcessor);
};
