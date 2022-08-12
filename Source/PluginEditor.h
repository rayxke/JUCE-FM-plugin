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

    virtual JuceDemoPluginAudioProcessorEditor* getPluginHolder() { return pluginHolder.get(); }

    std::unique_ptr<JuceDemoPluginAudioProcessorEditor> pluginHolder;
    //std::unique_ptr<JuceDemoPluginAudioProcessor> processor;
    //std::unique_ptr<juce::AudioProcessor> processor;

    private:
        MidiKeyboardComponent midiKeyboard;

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
            presetsLabel{ {}, "Presets" },
            chebyshevAmpLabel1{ {}, "Chebyshev Amplitude 1" },
            chebyshevAmpLabel2{ {}, "Chebyshev Amplitude 2" },
            chebyshevAmpLabel3{ {}, "Chebyshev Amplitude 3" },
            chebyshevAmpLabel4{ {}, "Chebyshev Amplitude 4" },
            chebyshevAmpLabel5{ {}, "Chebyshev Amplitude 5" },
            chebyshevAmpLabel6{ {}, "Chebyshev Amplitude 6" },
            chebyshevAmpLabel7{ {}, "Chebyshev Amplitude 7" },
            chebyshevAmpLabel8{ {}, "Chebyshev Amplitude 8" },
            chebyshevAmpLabel9{ {}, "Chebyshev Amplitude 9" };

        Slider gainSlider, delaySlider, modSlider, attackSlider, sustainSlider, releaseSlider, mattackSlider, msustainSlider, mreleaseSlider, chebyshevAmpSlider1, chebyshevAmpSlider2, chebyshevAmpSlider3, chebyshevAmpSlider4, chebyshevAmpSlider5, chebyshevAmpSlider6, chebyshevAmpSlider7, chebyshevAmpSlider8, chebyshevAmpSlider9;
        
        ComboBox iNumBox, iDenBox, iEnvBox, iModBox;
        
        juce::TextButton resetEnvelope, resetModEnvelope, savePreset, loadPreset;
        
        AudioProcessorValueTreeState::SliderAttachment gainAttachment, delayAttachment, modAttachment, attackAttachment, sustainAttachment, releaseAttachment, mattackAttachment, msustainAttachment, mreleaseAttachment, chebyshevAmpAttachment1, chebyshevAmpAttachment2, chebyshevAmpAttachment3, chebyshevAmpAttachment4, chebyshevAmpAttachment5, chebyshevAmpAttachment6, chebyshevAmpAttachment7, chebyshevAmpAttachment8, chebyshevAmpAttachment9;
        
        AudioProcessorValueTreeState::ComboBoxAttachment iNumAttachment, iDenAttachment, iEnvAttachment, iModEnvAttachment;
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
