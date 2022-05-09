//
//  PluginProcessorEditor.hpp
//  AudioPluginDemo - All
//
//  Copyright © 2022 JUCE. All rights reserved.
//

#include "PluginEditor.h"




JuceDemoPluginAudioProcessorEditor::JuceDemoPluginAudioProcessorEditor(JuceDemoPluginAudioProcessor& owner)
    : AudioProcessorEditor(owner),
    knobPanel(),
     midiKeyboard         (owner.keyboardState, MidiKeyboardComponent::horizontalKeyboard),
     gainAttachment       (owner.state, "gain",  gainSlider),
     delayAttachment      (owner.state, "delay", delaySlider),
     modAttachment        (owner.state, "mod", modSlider),
     iNumAttachment       (owner.state, "indexNum", iNumBox),
     iDenAttachment       (owner.state, "indexDen", iDenBox),
     attackAttachment     (owner.state, "attack", attackSlider),
     sustainAttachment    (owner.state, "sustain", sustainSlider),
     releaseAttachment    (owner.state, "release", releaseSlider),
     mattackAttachment    (owner.state, "mattack", mattackSlider),
     msustainAttachment   (owner.state, "msustain", msustainSlider),
     mreleaseAttachment   (owner.state, "mrelease", mreleaseSlider),
     iEnvAttachment       (owner.state, "expLineEnv", iEnvBox),
     iModEnvAttachment    (owner.state, "expLinModEnv", iModBox),
     presetsAttachment    (owner.state, "presets", presetsBox),
     chebyshevAmpAttachment1   (owner.state, "chebyshevAmp1", chebyshevAmpSlider1),
     chebyshevAmpAttachment2   (owner.state, "chebyshevAmp2", chebyshevAmpSlider2),
     chebyshevAmpAttachment3   (owner.state, "chebyshevAmp3", chebyshevAmpSlider3),
     chebyshevAmpAttachment4   (owner.state, "chebyshevAmp4", chebyshevAmpSlider4),
     chebyshevAmpAttachment5   (owner.state, "chebyshevAmp5", chebyshevAmpSlider5),
     chebyshevAmpAttachment6   (owner.state, "chebyshevAmp6", chebyshevAmpSlider6),
     chebyshevAmpAttachment7   (owner.state, "chebyshevAmp7", chebyshevAmpSlider7),
     chebyshevAmpAttachment8   (owner.state, "chebyshevAmp8", chebyshevAmpSlider8),
     chebyshevAmpAttachment9   (owner.state, "chebyshevAmp9", chebyshevAmpSlider9)


   {
        //TODO: Is it possible to convert this to a for loop?
        // add some sliders..

    

     
    Knob *gainKnob = new Knob(&gainSlider, "Gain");
    knobPanel.addToPanel(gainKnob);
    Knob* delayKnob = new Knob(&delaySlider, "Delay");
    knobPanel.addToPanel(delayKnob);
    Knob* modKnob = new Knob(&modSlider, "Mod");
    knobPanel.addToPanel(modKnob);
    Knob* attackKnob = new Knob(&attackSlider, "Attack");
    knobPanel.addToPanel(attackKnob);
    Knob* sustainKnob = new Knob(&sustainSlider, "Sustain");
    knobPanel.addToPanel(sustainKnob);
    Knob* releaseKnob = new Knob(&releaseSlider, "Release");
    knobPanel.addToPanel(releaseKnob);
    Knob* mattackKnob = new Knob(&mattackSlider, "mAttack");
    knobPanel.addToPanel(mattackKnob);
    Knob* msustainKnob = new Knob(&msustainSlider, "mSustain");
    knobPanel.addToPanel(msustainKnob);
    Knob* mreleaseKnob = new Knob(&mreleaseSlider, "mRelease");
    knobPanel.addToPanel(mreleaseKnob);

    Knob* chebyshevAmpKnob1 = new Knob(&chebyshevAmpSlider1, "CA1");
    knobPanel.addToPanel(chebyshevAmpKnob1);
    Knob* chebyshevAmpKnob2 = new Knob(&chebyshevAmpSlider2, "CA2");
    knobPanel.addToPanel(chebyshevAmpKnob2);
    Knob* chebyshevAmpKnob3 = new Knob(&chebyshevAmpSlider3, "CA3");
    knobPanel.addToPanel(chebyshevAmpKnob3);
    Knob* chebyshevAmpKnob4 = new Knob(&chebyshevAmpSlider4, "CA4");
    knobPanel.addToPanel(chebyshevAmpKnob4);
    Knob* chebyshevAmpKnob5 = new Knob(&chebyshevAmpSlider5, "CA5");
    knobPanel.addToPanel(chebyshevAmpKnob5);
    Knob* chebyshevAmpKnob6 = new Knob(&chebyshevAmpSlider6, "CA6");
    knobPanel.addToPanel(chebyshevAmpKnob6);
    Knob* chebyshevAmpKnob7 = new Knob(&chebyshevAmpSlider7, "CA7");
    knobPanel.addToPanel(chebyshevAmpKnob7);
    Knob* chebyshevAmpKnob8 = new Knob(&chebyshevAmpSlider8, "CA8");
    knobPanel.addToPanel(chebyshevAmpKnob8);
    Knob* chebyshevAmpKnob9 = new Knob(&chebyshevAmpSlider9, "CA9");
    knobPanel.addToPanel(chebyshevAmpKnob9);

    addAndMakeVisible(knobPanel);

    menuPanel.addToPanel(&resetEnvelope);
    resetEnvelope.setButtonText("Reset Envelope.");
    resetEnvelope.addListener(this);
    menuPanel.addToPanel(&resetModEnvelope);
    resetModEnvelope.setButtonText("Reset Modulation Envelope.");
    resetModEnvelope.addListener(this);
    menuPanel.addToPanel(&savePreset);
    savePreset.setButtonText("Save Preset");
    savePreset.addListener(this);

    menuPanel.addToPanel(&iNumBox);

    for (int i = 2; i < 100; i++)
    {
        iNumBox.addItem(std::to_string(i), i);
    }

    menuPanel.addToPanel(&iDenBox);
    for (int i = 2; i <= 20; i++)
    {
        iDenBox.addItem(std::to_string(i), i);
    }

    menuPanel.addToPanel(&presetsBox);

    iDenBox.setSelectedId(2);
    iNumBox.setSelectedId(2);


    menuPanel.addToPanel(&iEnvBox);
    iEnvBox.addItem("Lin Att. - Lin Dec.", 0);
    iEnvBox.addItem("Exp Att.. - Lin Dec.", 1);
    iEnvBox.addItem("Lin Att.. - Exp Dec.", 2);

    iEnvBox.addItem("Exp Att.. - Exp Dec.", 3);

    menuPanel.addToPanel(&iModBox);
    iModBox.addItem("Lin Att. - Lin Dec.", 0);
    iModBox.addItem("Exp Att.. - Lin Dec.", 1);
    iModBox.addItem("Lin Att.. - Exp Dec.", 2);

    iModBox.addItem("Exp Att.. - Exp Dec.", 3);

    addAndMakeVisible(menuPanel);
       // add the midi keyboard component..
       addAndMakeVisible (midiKeyboard);
       
       // add a label that will display the current timecode and status..
       addAndMakeVisible (timecodeDisplayLabel);
       timecodeDisplayLabel.setFont (Font (Font::getDefaultMonospacedFontName(), 15.0f, Font::plain));

       // set resize limits for this plug-in
       setResizeLimits (950, 500, 2048, 7000);

       lastUIWidth .referTo (owner.state.state.getChildWithName ("uiState").getPropertyAsValue ("width",  nullptr));
       lastUIHeight.referTo (owner.state.state.getChildWithName ("uiState").getPropertyAsValue ("height", nullptr));

       // set our component's initial size to be the last one that was stored in the filter's settings
       setSize (lastUIWidth.getValue(), lastUIHeight.getValue());

       lastUIWidth. addListener (this);
       lastUIHeight.addListener (this);

       updateTrackProperties();

       // start a timer which will keep our timecode display updated
       startTimerHz (30);
   }
   
   

   JuceDemoPluginAudioProcessorEditor::~JuceDemoPluginAudioProcessorEditor(){}
   void JuceDemoPluginAudioProcessorEditor::buttonClicked (juce::Button* button)  // [2]
   {
       if (button == &resetEnvelope)                                                      // [3]
       {
         
            
         
              // [6]
              releaseSlider.setValue(0.0);
              sustainSlider.setValue(100.0);
              attackSlider.setValue(0.0);

       }else  if (button == &resetModEnvelope)  {                                                    // [3]
         
      
         
              // [6]
              mreleaseSlider.setValue(0.0);
              msustainSlider.setValue(100.0);
              mattackSlider.setValue(0.0);

      }
   }

   //============ ==================================================================
   void JuceDemoPluginAudioProcessorEditor::paint (Graphics& g)
   {
       g.setColour (backgroundColour);
       g.fillAll();
   }

   void JuceDemoPluginAudioProcessorEditor::resized()
   {
       auto r = getLocalBounds().reduced(8);
       timecodeDisplayLabel.setBounds(r.removeFromTop(26));
       midiKeyboard.setBounds(r.removeFromBottom(80));
       r.removeFromBottom(10);
       r.removeFromTop(20);

       FlexBox fb;

       FlexItem left ((float)r.getWidth() * 0.6f, (float)r.getHeight(), knobPanel);
       FlexItem right((float)r.getWidth() * 0.4f, (float)r.getHeight(), menuPanel);
       fb.items.addArray({left, right});
       fb.performLayout(r.toFloat());
       
   }

   void JuceDemoPluginAudioProcessorEditor::timerCallback()
   {
       updateTimecodeDisplay (getProcessor().lastPosInfo.get());
   }

   void JuceDemoPluginAudioProcessorEditor::hostMIDIControllerIsAvailable (bool controllerIsAvailable)
   {
       midiKeyboard.setVisible (! controllerIsAvailable);
   }

   int JuceDemoPluginAudioProcessorEditor::getControlParameterIndex (Component& control)
   {
       if (&control == &gainSlider)
           return 0;

       if (&control == &delaySlider)
           return 1;

       return -1;
   }

   void JuceDemoPluginAudioProcessorEditor::updateTrackProperties()
   {
       auto trackColour = getProcessor().getTrackProperties().colour;
       auto& lf = getLookAndFeel();

       backgroundColour = (trackColour == Colour() ? lf.findColour (ResizableWindow::backgroundColourId)
                                                   : trackColour.withAlpha (1.0f).withBrightness (0.266f));
       repaint();
   }


   //==============================================================================
   JuceDemoPluginAudioProcessor& JuceDemoPluginAudioProcessorEditor::getProcessor() const
   {
       return static_cast<JuceDemoPluginAudioProcessor&> (processor);
   }

   //==============================================================================
   // quick-and-dirty function to format a timecode string
   String JuceDemoPluginAudioProcessorEditor::timeToTimecodeString (double seconds)
   {
       auto millisecs = roundToInt (seconds * 1000.0);
       auto absMillisecs = std::abs (millisecs);

       return String::formatted ("%02d:%02d:%02d.%03d",
                                 millisecs / 3600000,
                                 (absMillisecs / 60000) % 60,
                                 (absMillisecs / 1000)  % 60,
                                 absMillisecs % 1000);
   }

   // quick-and-dirty function to format a bars/beats string
   String JuceDemoPluginAudioProcessorEditor::quarterNotePositionToBarsBeatsString (double quarterNotes, int numerator, int denominator)
   {
       if (numerator == 0 || denominator == 0)
           return "1|1|000";

       auto quarterNotesPerBar = (numerator * 4 / denominator);
       auto beats  = (fmod (quarterNotes, quarterNotesPerBar) / quarterNotesPerBar) * numerator;

       auto bar    = ((int) quarterNotes) / quarterNotesPerBar + 1;
       auto beat   = ((int) beats) + 1;
       auto ticks  = ((int) (fmod (beats, 1.0) * 960.0 + 0.5));

       return String::formatted ("%d|%d|%03d", bar, beat, ticks);
   }

   // Updates the text in our position label.
   void JuceDemoPluginAudioProcessorEditor::updateTimecodeDisplay (AudioPlayHead::CurrentPositionInfo pos)
   {
       MemoryOutputStream displayText;

       displayText << "[" << SystemStats::getJUCEVersion() << "]   "
       << String (pos.bpm, 2) << " bpm, "
       << pos.timeSigNumerator << '/' << pos.timeSigDenominator
       << "  -  " << timeToTimecodeString (pos.timeInSeconds)
       << "  -  " << quarterNotePositionToBarsBeatsString (pos.ppqPosition,
                                                           pos.timeSigNumerator,
                                                           pos.timeSigDenominator);

       if (pos.isRecording)
           displayText << "  (recording)";
       else if (pos.isPlaying)
           displayText << "  (playing)";

       timecodeDisplayLabel.setText (displayText.toString(), dontSendNotification);
   }

   // called when the stored window size changes
   void JuceDemoPluginAudioProcessorEditor::valueChanged (Value&)
   {
       setSize (lastUIWidth.getValue(), lastUIHeight.getValue());
   }
