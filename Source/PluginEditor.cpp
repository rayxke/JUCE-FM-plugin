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
       
       addAndMakeVisible(chebyshevAmpSlider1);
       chebyshevAmpSlider1.setSliderStyle(Slider::Rotary);
       
       addAndMakeVisible(chebyshevAmpSlider2);
       chebyshevAmpSlider2.setSliderStyle(Slider::Rotary);
       
       addAndMakeVisible(chebyshevAmpSlider3);
       chebyshevAmpSlider3.setSliderStyle(Slider::Rotary);
       
       addAndMakeVisible(chebyshevAmpSlider3);
       chebyshevAmpSlider3.setSliderStyle(Slider::Rotary);
       
       addAndMakeVisible(chebyshevAmpSlider4);
       chebyshevAmpSlider4.setSliderStyle(Slider::Rotary);
       
       addAndMakeVisible(chebyshevAmpSlider5);
       chebyshevAmpSlider5.setSliderStyle(Slider::Rotary);
       
       addAndMakeVisible(chebyshevAmpSlider6);
       chebyshevAmpSlider6.setSliderStyle(Slider::Rotary);
       
       addAndMakeVisible(chebyshevAmpSlider7);
       chebyshevAmpSlider7.setSliderStyle(Slider::Rotary);
       
       addAndMakeVisible(chebyshevAmpSlider8);
       chebyshevAmpSlider8.setSliderStyle(Slider::Rotary);
       
       addAndMakeVisible(chebyshevAmpSlider9);
       chebyshevAmpSlider9.setSliderStyle(Slider::Rotary);
       
       addAndMakeVisible (resetEnvelope);
       resetEnvelope.setButtonText ("Reset Envelope.");
       resetEnvelope.addListener (this);
       
       addAndMakeVisible(resetModEnvelope);
       resetModEnvelope.setButtonText ("Reset Modulation Envelope.");
       resetModEnvelope.addListener (this);      
       
       addAndMakeVisible(savePreset);
       savePreset.setButtonText("Save Preset");
       savePreset.addListener(this);
       
       /*addAndMakeVisible (iNumSlider);
       iNumSlider.setSliderStyle (Slider::Rotary);
       
       addAndMakeVisible (iDenSlider);
       iDenSlider.setSliderStyle (Slider::Rotary);*/
       
       addAndMakeVisible(loadPreset);
       loadPreset.setButtonText("Load Preset");
       loadPreset.addListener(this);

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
       
       chebyshevAmpLabel1.attachToComponent(&chebyshevAmpSlider1, false);
       chebyshevAmpLabel1.setFont(Font(11.0f));
       
       chebyshevAmpLabel2.attachToComponent(&chebyshevAmpSlider2, false);
       chebyshevAmpLabel2.setFont(Font(11.0f));
       
       chebyshevAmpLabel3.attachToComponent(&chebyshevAmpSlider3, false);
       chebyshevAmpLabel3.setFont(Font(11.0f));
       
       chebyshevAmpLabel3.attachToComponent(&chebyshevAmpSlider3, false);
       chebyshevAmpLabel3.setFont(Font(11.0f));
       
       chebyshevAmpLabel4.attachToComponent(&chebyshevAmpSlider4, false);
       chebyshevAmpLabel4.setFont(Font(11.0f));
       
       chebyshevAmpLabel5.attachToComponent(&chebyshevAmpSlider5, false);
       chebyshevAmpLabel5.setFont(Font(11.0f));
       
       chebyshevAmpLabel6.attachToComponent(&chebyshevAmpSlider6, false);
       chebyshevAmpLabel6.setFont(Font(11.0f));
       
       chebyshevAmpLabel7.attachToComponent(&chebyshevAmpSlider7, false);
       chebyshevAmpLabel7.setFont(Font(11.0f));
       
       chebyshevAmpLabel8.attachToComponent(&chebyshevAmpSlider8, false);
       chebyshevAmpLabel8.setFont(Font(11.0f));
       
       chebyshevAmpLabel9.attachToComponent(&chebyshevAmpSlider9, false);
       chebyshevAmpLabel9.setFont(Font(11.0f));

       // add the midi keyboard component..
       addAndMakeVisible (midiKeyboard);

       // add a label that will display the current timecode and status..
       addAndMakeVisible (timecodeDisplayLabel);
       timecodeDisplayLabel.setFont (Font (Font::getDefaultMonospacedFontName(), 15.0f, Font::plain));

       // set resize limits for this plug-in
       setResizeLimits (800, 400, 1024, 700);

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

   OptionalScopedPointer<PropertySet> settings;

   static String getFilePatterns(const String& fileSuffix)
   {
       if (fileSuffix.isEmpty())
           return {};

       return (fileSuffix.startsWithChar('.') ? "*" : "*.") + fileSuffix;
   }
   
   File getLastFile()
   {
       File f;

       if (settings != nullptr)
           f = File(settings->getValue("lastStateFile"));

       if (f == File())
           f = File::getSpecialLocation(File::userDocumentsDirectory);

       return f;
   }

   void setLastFile(const FileChooser& fc)
   {
       if (settings != nullptr)
           settings->setValue("lastStateFile", fc.getResult().getFullPathName());
   }

   /** Pops up a dialog letting the user save the processor's state to a file. */

   std::unique_ptr<FileChooser> stateFileChooser;
   //std::unique_ptr<JuceDemoPluginAudioProcessor> processor;
   JuceDemoPluginAudioProcessor processor;
   //std::unique_ptr<AudioProcessor> processor;
   //AudioProcessor *processor;
 
   void askUserToSaveState(const String& fileSuffix = String())
   {
       stateFileChooser = std::make_unique<FileChooser>(TRANS("Save current state"),
           getLastFile(),
           getFilePatterns(fileSuffix));
       auto flags = FileBrowserComponent::saveMode
           | FileBrowserComponent::canSelectFiles
           | FileBrowserComponent::warnAboutOverwriting;

       stateFileChooser->launchAsync(flags, [](const FileChooser& fc)
           {
               if (fc.getResult() == File{})
                   return;

               setLastFile(fc);

               MemoryBlock data;
               processor.getStateInformation(data);

               if (!fc.getResult().replaceWithData(data.getData(), data.getSize()))
                   AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon,
                       TRANS("Error whilst saving"),
                       TRANS("Couldn't write to the specified file!"));
           });
   }

   /** Pops up a dialog letting the user re-load the processor's state from a file. */
   void askUserToLoadState(const String& fileSuffix = String())
   {
       stateFileChooser = std::make_unique<FileChooser>(TRANS("Load a saved state"),
           getLastFile(),
           getFilePatterns(fileSuffix));
       auto flags = FileBrowserComponent::openMode
           | FileBrowserComponent::canSelectFiles;

       stateFileChooser->launchAsync(flags, [](const FileChooser& fc)
           {
               if (fc.getResult() == File{})
                   return;

               setLastFile(fc);

               MemoryBlock data;

               if (fc.getResult().loadFileAsData(data))
                   processor.setStateInformation(data.getData(), (int)data.getSize());
               else
                   AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon,
                       TRANS("Error whilst loading"),
                       TRANS("Couldn't read from the specified file!"));
           });
   }

   void savePluginState()
   {
       if (settings != nullptr)
       {
           MemoryBlock data;
           processor.getStateInformation(data);

           settings->setValue("filterState", data.toBase64Encoding());
       }
   }

   void reloadPluginState()
   {
       if (settings != nullptr)
       {
           MemoryBlock data;

           if (data.fromBase64Encoding(settings->getValue("filterState")) && data.getSize() > 0)
               processor.setStateInformation(data.getData(), (int)data.getSize());
       }
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

       } else  if (button == &resetModEnvelope)  {                                                    // [3]
         
      
         
              // [6]
              mreleaseSlider.setValue(0.0);
              msustainSlider.setValue(100.0);
              mattackSlider.setValue(0.0);

       }
       else if (button == &savePreset) {
           askUserToSaveState();
       }

       else if (button == &loadPreset) {
           askUserToLoadState();
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
       auto sliderArea = r.removeFromTop (60);
       auto spacer = r.removeFromTop(20);
       auto sliderArea2 = r.removeFromTop (60);
       auto spacer2 = r.removeFromTop(20);
       auto sliderArea3 = r.removeFromTop (60);
       auto sliderArea4 = r.removeFromTop (60);
       auto sliderArea5 = r.removeFromTop (60);
       auto sliderArea6 = r.removeFromTop (60);

       gainSlider.setBounds  (sliderArea.removeFromLeft (jmin (180, sliderArea.getWidth() / 2)));
       delaySlider.setBounds (sliderArea.removeFromLeft (jmin (180, sliderArea.getWidth())));
       modSlider.setBounds (sliderArea.removeFromLeft (jmin (180, sliderArea.getWidth())));
       iNumBox.setBounds (sliderArea.removeFromLeft (jmin (180, sliderArea.getWidth()/2)));
       auto boxSpacer_1a = sliderArea.removeFromLeft(20);
       iDenBox.setBounds (sliderArea.removeFromLeft (jmin (180, sliderArea.getWidth())));
       auto boxSpacer_1b = sliderArea.removeFromLeft(20);
       savePreset.setBounds(sliderArea.removeFromLeft(jmin(180, sliderArea.getWidth())));

       attackSlider.setBounds(sliderArea2.removeFromLeft(jmin(180, sliderArea2.getWidth())));
       sustainSlider.setBounds(sliderArea2.removeFromLeft(jmin(180, sliderArea2.getWidth())));
       releaseSlider.setBounds(sliderArea2.removeFromLeft(jmin(180, sliderArea2.getWidth())));
       resetEnvelope.setBounds(sliderArea2.removeFromLeft(jmin(180, sliderArea2.getWidth() /2)));
       auto boxSpacer_2a = sliderArea2.removeFromLeft(20);
       iEnvBox.setBounds (sliderArea2.removeFromLeft (jmin (180, sliderArea2.getWidth())));
       auto boxSpacer_2b = sliderArea2.removeFromLeft(20);
       loadPreset.setBounds(sliderArea2.removeFromLeft(jmin(180, sliderArea2.getWidth())));

       mattackSlider.setBounds(sliderArea3.removeFromLeft(jmin(180, sliderArea3.getWidth())));
       msustainSlider.setBounds(sliderArea3.removeFromLeft(jmin(180, sliderArea3.getWidth())));
       mreleaseSlider.setBounds(sliderArea3.removeFromLeft(jmin(180, sliderArea3.getWidth())));
       resetModEnvelope.setBounds(sliderArea3.removeFromLeft(jmin(180, sliderArea3.getWidth())));
       auto boxSpacer3a = sliderArea3.removeFromLeft(20);
       iModBox.setBounds (sliderArea3.removeFromLeft (jmin (180, sliderArea3.getWidth())));
       auto boxSpacer3b = sliderArea3.removeFromLeft(20);
       
       
       chebyshevAmpSlider1.setBounds(sliderArea4.removeFromLeft(jmin(180, sliderArea4.getWidth())));
       chebyshevAmpSlider2.setBounds(sliderArea4.removeFromLeft(jmin(180, sliderArea4.getWidth())));
       chebyshevAmpSlider3.setBounds(sliderArea4.removeFromLeft(jmin(180, sliderArea4.getWidth())));
       
       chebyshevAmpSlider4.setBounds(sliderArea5.removeFromLeft(jmin(180, sliderArea5.getWidth())));
       chebyshevAmpSlider5.setBounds(sliderArea5.removeFromLeft(jmin(180, sliderArea5.getWidth())));
       chebyshevAmpSlider6.setBounds(sliderArea5.removeFromLeft(jmin(180, sliderArea5.getWidth())));
       
       chebyshevAmpSlider7.setBounds(sliderArea6.removeFromLeft(jmin(180, sliderArea6.getWidth())));
       chebyshevAmpSlider8.setBounds(sliderArea6.removeFromLeft(jmin(180, sliderArea6.getWidth())));
       chebyshevAmpSlider9.setBounds(sliderArea6.removeFromLeft(jmin(180, sliderArea6.getWidth())));

       
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
