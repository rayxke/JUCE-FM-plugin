//
//  SineWaveSound.cpp
//  AudioPluginDemo
//
//  Copyright © 2022 JUCE. All rights reserved.
//


#include "SineWaveSound.h"

//==============================================================================
SineWaveSound::SineWaveSound()
{
}
bool SineWaveSound::appliesToNote (int /*midiNoteNumber*/)   { return true; }
bool SineWaveSound::appliesToChannel (int /*midiChannel*/)   { return true; }
