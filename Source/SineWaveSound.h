//
//  SineWaveSound.h
//  AudioPluginDemo
//
//  Copyright © 2022 JUCE. All rights reserved.
//

//==============================================================================
/** A demo synth sound that's just a basic sine wave.. */
#pragma once

#include <JuceHeader.h>

class SineWaveSound : public SynthesiserSound
{
public:
    SineWaveSound();
    bool appliesToNote (int /*midiNoteNumber*/) override;
    bool appliesToChannel (int /*midiChannel*/) override;
};
