//
//  SineWaveVoice.hpp
//  AudioPluginDemo - All
//  Copyright © 2022 JUCE. All rights reserved.
//
//==============================================================================
/** A simple demo synth voice that just plays a sine wave.. */

#pragma once

#include <JuceHeader.h>

class SineWaveVoice   : public SynthesiserVoice
{
public:
    SineWaveVoice();

    bool canPlaySound (SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity,
                    SynthesiserSound* /*sound*/, int) override;
    void stopNote (float /*velocity*/, bool allowTailOff) override;
    float chebyshevCalulation(int chebyshev, float x);
    void pitchWheelMoved (int /*newValue*/) override;
    void controllerMoved (int paramNum, int value) override;
    void renderNextBlock (AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
    
    using SynthesiserVoice::renderNextBlock;

private:
    //sine parameters
      double currentAngle = 0.0;
      double angleDelta   = 0.0;
      double level        = 1.0;
      //adsr parameters
      int att_is_exp = 0;
      int dec_is_exp = 0;
      int modatt_is_exp = 1;
      int moddec_is_exp = 1;
      double attack_param       = 0.5;
      //TODO: add decay, sustain, etc.
      double sustain_param      = 1.0;
      double decay_param      = 1.0;
      double release_param     = 0.5;
      
      double release       = 0.0;
      double attack = .01;
    
      double mattack = 0.1;
      double mrelease = 0.0;
      
      juce::ADSR adsr;
      juce::ADSR::Parameters adsrParams;
      juce::ADSR::Parameters modAdsrParams;
      //FM parameters
      double modCurrentAngle = 0.0;
      double modAngleDelta = 0.0;
      double modIndex = 0.0;
      int freqDev = 50;
      enum ChebyshevLevels{
        chebyshevLevel0,
        chebyshevLevel1,
        chebyshevLevel2,
        chebyshevLevel3,
        chebyshevLevel4,
        chebyshevLevel5,
        chebyshevLevel6,
        chebyshevLevel7,
        chebyshevLevel8,
        chebyshevLevel9,
        chebyshevLevelEnd
      };
      float chebyshevAmplitudes[chebyshevLevelEnd];
      int modRatioNum = 1;
      int modRatioDen = 1;
      double modRatio = 1.0;
};
