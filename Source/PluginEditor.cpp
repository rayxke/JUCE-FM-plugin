//
//  PluginProcessorEditor.hpp
//  AudioPluginDemo - All
//
//  Copyright © 2022 JUCE. All rights reserved.
//

#include "PluginEditor.h"




JuceDemoPluginAudioProcessorEditor::JuceDemoPluginAudioProcessorEditor (JuceDemoPluginAudioProcessor& owner)
   : AudioProcessorEditor (owner),
     midiKeyboard         (owner.keyboardState, MidiKeyboardComponent::horizontalKeyboard),
     gainAttachment       (owner.state, "gain",  gainSlider),
     delayAttachment      (owner.state, "delay", delaySlider),
     modAttachment        (owner.state, "mod", modSlider),
     iNumAttachment   (owner.state, "indexNum", iNumBox),
     iDenAttachment   (owner.state, "indexDen", iDenBox),
     attackAttachment (owner.state, "attack", attackSlider),
     sustainAttachment(owner.state, "sustain", sustainSlider),
     releaseAttachment (owner.state, "release", releaseSlider),
       mattackAttachment (owner.state, "mattack", mattackSlider),
       msustainAttachment(owner.state, "msustain", msustainSlider),
       mreleaseAttachment (owner.state, "mrelease", mreleaseSlider),
       iEnvAttachment   (owner.state, "expLineEnv", iEnvBox),
       iModEnvAttachment   (owner.state, "expLinModEnv", iModBox),
    presetsAttachment   (owner.state, "presets", presetsBox)

   {
       // add some sliders..
       addAndMakeVisible (gainSlider);
       gainSlider.setSliderStyle (Slider::Rotary);

       addAndMakeVisible (delaySlider);
       delaySlider.setSliderStyle (Slider::Rotary);
       
       addAndMakeVisible (modSlider);
       modSlider.setSliderStyle (Slider::Rotary);

       addAndMakeVisible(attackSlider);
       attackSlider.setSliderStyle(Slider::Rotary);

       addAndMakeVisible(sustainSlider);
       sustainSlider.setSliderStyle(Slider::Rotary);

       addAndMakeVisible(releaseSlider);
       releaseSlider.setSliderStyle(Slider::Rotary);
       
       addAndMakeVisible(mattackSlider);
       mattackSlider.setSliderStyle(Slider::Rotary);

       addAndMakeVisible(msustainSlider);
       msustainSlider.setSliderStyle(Slider::Rotary);

       addAndMakeVisible(mreleaseSlider);
       mreleaseSlider.setSliderStyle(Slider::Rotary);
       
       addAndMakeVisible (resetEnvelope);
       resetEnvelope.setButtonText ("Reset Envelope");
       resetEnvelope.addListener (this);
       
       addAndMakeVisible(resetModEnvelope);
       resetModEnvelope.setButtonText ("Reset Modulation");
       resetModEnvelope.addListener (this);      
       
       addAndMakeVisible(savePreset);
       savePreset.setButtonText("Save Preset");
       savePreset.addListener(this);
       
       /*addAndMakeVisible (iNumSlider);
       iNumSlider.setSliderStyle (Slider::Rotary);
       
       addAndMakeVisible (iDenSlider);
       iDenSlider.setSliderStyle (Slider::Rotary);*/
       
       addAndMakeVisible(presetsBox);

       addAndMakeVisible(iNumBox);
       
       for (int i = 2; i < 100; i++)
       { iNumBox.addItem(std::to_string(i), i);
       }
       
       addAndMakeVisible(iDenBox);
       for (int i = 2; i <= 20; i++)
       {
           iDenBox.addItem(std::to_string(i), i);
       }
       iDenBox.setSelectedId(2);
       iNumBox.setSelectedId(2);

       
       addAndMakeVisible(iEnvBox);
       iEnvBox.addItem("Lin Att. - Lin Dec.", 0);
       iEnvBox.addItem("Exp Att.. - Lin Dec.", 1);
       iEnvBox.addItem("Lin Att.. - Exp Dec.", 2);

       iEnvBox.addItem("Exp Att.. - Exp Dec.", 3);
       
       addAndMakeVisible(iModBox);
       iModBox.addItem("Lin Att. - Lin Dec.", 0);
       iModBox.addItem("Exp Att.. - Lin Dec.", 1);
       iModBox.addItem("Lin Att.. - Exp Dec.", 2);

       iModBox.addItem("Exp Att.. - Exp Dec.", 3);


               

       // add some labels for the sliders..
       gainLabel.attachToComponent (&gainSlider, false);
       gainLabel.setFont (Font (11.0f));

       delayLabel.attachToComponent (&delaySlider, false);
       delayLabel.setFont (Font (11.0f));
       
       modLabel.attachToComponent (&modSlider, false);
       modLabel.setFont (Font (11.0f));
       
       numLabel.attachToComponent (&iNumBox, false);
       numLabel.setFont (Font (11.0f));
       
       denLabel.attachToComponent (&iDenBox, false);
       denLabel.setFont (Font (11.0f));

       attackLabel.attachToComponent(&attackSlider, false);
       attackLabel.setFont(Font(11.0f));

       sustainLabel.attachToComponent(&sustainSlider, false);
       sustainLabel.setFont(Font(11.0f));

       releaseLabel.attachToComponent(&releaseSlider, false);
       releaseLabel.setFont(Font(11.0f));
       
       mattackLabel.attachToComponent(&mattackSlider, false);
       attackLabel.setFont(Font(11.0f));

       msustainLabel.attachToComponent(&msustainSlider, false);
       msustainLabel.setFont(Font(11.0f));

       mreleaseLabel.attachToComponent(&mreleaseSlider, false);
       mreleaseLabel.setFont(Font(11.0f));

       presetsLabel.attachToComponent(&presetsBox, false);
       presetsLabel.setFont(Font(11.0f));

       // add the midi keyboard component..
       addAndMakeVisible (midiKeyboard);

       // add a label that will display the current timecode and status..
       addAndMakeVisible (timecodeDisplayLabel);
       timecodeDisplayLabel.setFont (Font (Font::getDefaultMonospacedFontName(), 15.0f, Font::plain));

       // set resize limits for this plug-in
       setResizeLimits (800, 440, 1220, 440);

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
       // This lays out our child components...

       auto r = getLocalBounds().reduced (8);

       timecodeDisplayLabel.setBounds (r.removeFromTop (26));
       midiKeyboard        .setBounds (r.removeFromBottom (70));

       r.removeFromTop (20);
       auto area1 = r.removeFromTop(30);
       auto spacer1 = r.removeFromTop(30);
       int area1Width = area1.getWidth();
       auto area2 = r.removeFromTop (60);
       int area2SliderWidth = area2.getWidth() * 0.60;
       int area2IndexWidth = area2.getWidth() * 0.20;
       int area2PresetWidth = area2.getWidth() * 0.20;
       auto spacer2 = r.removeFromTop(20);
       auto area3 = r.removeFromTop (60);
       int area3SliderWidth = area3.getWidth() * 0.60;
       int area3IndexWidth = area3.getWidth() * 0.20;
       int area3PresetWidth = area3.getWidth() * 0.20;
       auto spacer3 = r.removeFromTop(20);
       auto area4 = r.removeFromTop (60);
       int area4SliderWidth = area4.getWidth() * 0.60;
       int area4IndexWidth = area4.getWidth() * 0.20;
       //int area4PresetWidth = area4.getWidth() * 0.20;

       presetsBox.setBounds(area1.removeFromLeft((area1Width * 0.2) + 5));
       auto boxSpacer_1a = area1.removeFromLeft(5);
       savePreset.setBounds(area1.removeFromLeft(120));

       gainSlider.setBounds  (area2.removeFromLeft (area2SliderWidth / 3));
       delaySlider.setBounds (area2.removeFromLeft (area2SliderWidth / 3));
       modSlider.setBounds (area2.removeFromLeft (area2SliderWidth / 3));
       iNumBox.setBounds(area2.removeFromLeft(110));
       //iNumBox.setBounds (area2.removeFromLeft ((area2IndexWidth / 2) - 20));
       auto boxSpacer_2a = area2.removeFromLeft(20);
       iDenBox.setBounds (area2.removeFromLeft (110));
       auto boxSpacer_2b = area2.removeFromLeft(20);
       //savePreset.setBounds(area2.removeFromLeft(area2PresetWidth));

       attackSlider.setBounds(area3.removeFromLeft(area3SliderWidth / 3));
       sustainSlider.setBounds(area3.removeFromLeft(area3SliderWidth / 3));
       releaseSlider.setBounds(area3.removeFromLeft(area3SliderWidth / 3));
       resetEnvelope.setBounds(area3.removeFromLeft(75));
       auto boxSpacer_3a = area3.removeFromLeft(20);
       iEnvBox.setBounds (area3.removeFromLeft (area3.getWidth()));
       auto boxSpacer_3b = area3.removeFromLeft(20);
       //presetsBox.setBounds(area3.removeFromLeft(area3PresetWidth));

       mattackSlider.setBounds(area4.removeFromLeft(area4SliderWidth / 3));
       msustainSlider.setBounds(area4.removeFromLeft(area4SliderWidth / 3));
       mreleaseSlider.setBounds(area4.removeFromLeft(area4SliderWidth / 3));
       resetModEnvelope.setBounds(area4.removeFromLeft(75));
       auto boxSpacer3 = area4.removeFromLeft(20);
       iModBox.setBounds (area4.removeFromLeft (area4.getWidth()));

       
       lastUIWidth  = getWidth();
       lastUIHeight = getHeight();
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
