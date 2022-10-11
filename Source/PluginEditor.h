//
//  PluginProcessorEditor.hpp
//  AudioPluginDemo - All
//
//  Copyright © 2022 JUCE. All rights reserved.
//
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
  class JuceDemoPluginAudioProcessorEditor  : public AudioProcessorEditor,
                                                private Timer,
                                                private Value::Listener,//,
                                                public Button::Listener
{
public:
    JuceDemoPluginAudioProcessorEditor (JuceDemoPluginAudioProcessor& owner);
  
    ~JuceDemoPluginAudioProcessorEditor() override;

    
//==============================================================================
    void paint (Graphics& g) override;
    void resized() override;
    void timerCallback() override;
    void hostMIDIControllerIsAvailable (bool controllerIsAvailable) override;
    int getControlParameterIndex (Component& control) override;
    void updateTrackProperties();
    void buttonClicked (juce::Button* button) override;

    private:
        MidiKeyboardComponent midiKeyboard;
        enum chebyshevSliders {
            chebyshev1, chebyshev2, chebyshev3,
            chebyshev4, chebyshev5, chebyshev6,
            chebyshev7, chebyshev8, chebyshev9,
            numberOfChebyshevs};

        Label timecodeDisplayLabel,
            gainLabel{ {}, "Throughput level:" },
            delayLabel{ {}, "Delay:" },
            modLabel{ {}, "Freq Mod (deviation):" },
            numLabel{ {},  "Index Numerator:" },
            denLabel{ {},  "Index Denominator:" },
            attackLabel{ {}, "Attack Speed:" },
            sustainLabel{ {}, "Sustain Magnitude:" },
            releaseLabel{ {}, "Release Speed:" },
            mattackLabel{ {}, "Mod Attack Speed:" },
            msustainLabel{ {}, "Mod Sustain Magnitude:" },
            mreleaseLabel{ {}, "Mod Release Speed:" },
        presetsLabel{ {}, "Presets" };

        Label chebyshevLabels[numberOfChebyshevs];

        Slider gainSlider, delaySlider, modSlider, attackSlider, sustainSlider, releaseSlider, mattackSlider, msustainSlider, mreleaseSlider;
        Slider chebyshevAmpSliders[numberOfChebyshevs];
        
        ComboBox iNumBox, iDenBox, iEnvBox, iModBox, presetsBox;
        
        juce::TextButton resetEnvelope, resetModEnvelope, savePreset;
        
        AudioProcessorValueTreeState::SliderAttachment gainAttachment, delayAttachment, modAttachment, attackAttachment, sustainAttachment, releaseAttachment, mattackAttachment, msustainAttachment, mreleaseAttachment, chebyshevAmpAttachment1, chebyshevAmpAttachment2, chebyshevAmpAttachment3, chebyshevAmpAttachment4, chebyshevAmpAttachment5, chebyshevAmpAttachment6, chebyshevAmpAttachment7, chebyshevAmpAttachment8, chebyshevAmpAttachment9;
        
        AudioProcessorValueTreeState::ComboBoxAttachment iNumAttachment, iDenAttachment, iEnvAttachment, iModEnvAttachment, presetsAttachment;
        Colour backgroundColour;

        // these are used to persist the UI's size - the values are stored along with the
        // filter's other parameters, and the UI component will update them when it gets
        // resized.
        Value lastUIWidth, lastUIHeight;

        //==============================================================================
        JuceDemoPluginAudioProcessor& getProcessor() const;

        //==============================================================================
        // quick-and-dirty function to format a timecode string
        static String timeToTimecodeString (double seconds);

        // quick-and-dirty function to format a bars/beats string
        static String quarterNotePositionToBarsBeatsString (double quarterNotes, int numerator, int denominator);

        // Updates the text in our position label.
        void updateTimecodeDisplay (AudioPlayHead::CurrentPositionInfo pos);

        // called when the stored window size ;
        void updateCurrentTimeInfoFromHost();
        void valueChanged (Value&) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceDemoPluginAudioProcessorEditor)
};
