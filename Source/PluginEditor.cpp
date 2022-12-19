//
//  PluginProcessorEditor.hpp
//  AudioPluginDemo - All
//
//  Copyright © 2022 JUCE. All rights reserved.
//

#include "PluginEditor.h"




JuceDemoPluginAudioProcessorEditor::JuceDemoPluginAudioProcessorEditor (JuceDemoPluginAudioProcessor& owner)
   : AudioProcessorEditor       (owner),
     midiKeyboard               (owner.keyboardState, MidiKeyboardComponent::horizontalKeyboard),
     gainAttachment             (owner.state, "gain",  sliders[gainSlider]),
     delayAttachment            (owner.state, "delay", sliders[delaySlider]),
     modAttachment              (owner.state, "mod", sliders[modSlider]),
     iNumAttachment             (owner.state, "indexNum", comboBoxes[iNumBox]),
     iDenAttachment             (owner.state, "indexDen", comboBoxes[iDenBox]),
     attackAttachment           (owner.state, "attack", sliders[attackSlider]),
     sustainAttachment          (owner.state, "sustain", sliders[sustainSlider]),
     releaseAttachment          (owner.state, "release", sliders[releaseSlider]),
     mattackAttachment          (owner.state, "mattack", sliders[mattackSlider]),
     msustainAttachment         (owner.state, "msustain", sliders[msustainSlider]),
     mreleaseAttachment         (owner.state, "mrelease", sliders[mreleaseSlider]),
     iEnvAttachment             (owner.state, "expLineEnv", comboBoxes[iEnvBox]),
     iModEnvAttachment          (owner.state, "expLinModEnv", comboBoxes[iModBox]),
     presetsAttachment          (owner.state, "presets", comboBoxes[presetsBox]),
     chebyshevAmpAttachment1    (owner.state, "chebyshevAmp1", chebyshevAmpSliders[chebyshev1]),
     chebyshevAmpAttachment2    (owner.state, "chebyshevAmp2", chebyshevAmpSliders[chebyshev2]),
     chebyshevAmpAttachment3    (owner.state, "chebyshevAmp3", chebyshevAmpSliders[chebyshev3]),
     chebyshevAmpAttachment4    (owner.state, "chebyshevAmp4", chebyshevAmpSliders[chebyshev4]),
     chebyshevAmpAttachment5    (owner.state, "chebyshevAmp5", chebyshevAmpSliders[chebyshev5]),
     chebyshevAmpAttachment6    (owner.state, "chebyshevAmp6", chebyshevAmpSliders[chebyshev6]),
     chebyshevAmpAttachment7    (owner.state, "chebyshevAmp7", chebyshevAmpSliders[chebyshev7]),
     chebyshevAmpAttachment8    (owner.state, "chebyshevAmp8", chebyshevAmpSliders[chebyshev8]),
     chebyshevAmpAttachment9    (owner.state, "chebyshevAmp9", chebyshevAmpSliders[chebyshev9])


{
    //Sliders
    for (int i = (int) gainSlider; i < numberOfSliders; i++)
    {
        container.addAndMakeVisible(sliders[i]);
        sliders[i].setSliderStyle(Slider::Rotary);
        sliders[i].setNumDecimalPlacesToDisplay(numDecimalPlaces);
        sliders[i].setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    }
    
    for (int i = (int) chebyshev1; i < numberOfChebyshevs; i++)
    {
        container.addAndMakeVisible(chebyshevAmpSliders[i]);
        chebyshevAmpSliders[i].addListener(this);
        chebyshevAmpSliders[i].setNumDecimalPlacesToDisplay(numDecimalPlaces);
        chebyshevAmpSliders[i].setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
        totalChart.setChebyshevAmplitudes(chebyshevAmpSliders[i].getValue(), (SineWaveVoice::ChebyshevLevels) (i+1));
        chebyshevChart.setChebyshevAmplitudes(chebyshevAmpSliders[i].getValue(), (SineWaveVoice::ChebyshevLevels) (i+1));
    }
    
    //Buttons
    for (int i = (int) savePreset; i < numberOfButtons; i++)
    {
        container.addAndMakeVisible (buttons[i]);
        buttons[i].addListener (this);
    }
    
    buttons[resetEnvelope].setButtonText ("Reset Envelope");
    buttons[resetModEnvelope].setButtonText ("Reset Modulation Envelope");
    buttons[savePreset].setButtonText("Save Preset");
    
    //Combo Boxes
    for (int i = (int) iNumBox; i < numberOfComboBoxes; i++)
    {
        container.addAndMakeVisible (comboBoxes[i]);
    }
   
    for (int i = 2; i < 100; i++)
    {
        comboBoxes[iNumBox].addItem(std::to_string(i), i);
    }
   
    
    for (int i = 2; i <= 20; i++)
    {
        comboBoxes[iDenBox].addItem(std::to_string(i), i);
    }
   
    comboBoxes[iDenBox].setSelectedId(2);
    comboBoxes[iNumBox].setSelectedId(2);

   
    
    comboBoxes[iEnvBox].addItem("Lin Att. - Lin Dec.", 1);
    comboBoxes[iEnvBox].addItem("Exp Att.. - Lin Dec.", 2);
    comboBoxes[iEnvBox].addItem("Lin Att.. - Exp Dec.", 3);
    comboBoxes[iEnvBox].addItem("Exp Att.. - Exp Dec.", 4);
   
    
    comboBoxes[iModBox].addItem("Lin Att. - Lin Dec.", 1);
    comboBoxes[iModBox].addItem("Exp Att.. - Lin Dec.", 2);
    comboBoxes[iModBox].addItem("Lin Att.. - Exp Dec.", 3);
    comboBoxes[iModBox].addItem("Exp Att.. - Exp Dec.", 4);

    
           

    // Add Labels to Sliders
    
    for (int i = (int) gainSlider; i < numberOfSliders; i++)
    {
        sliderLabels[i].setText(sliderLabelText[i], {});
        sliderLabels[i].attachToComponent (&sliders[i], false);
        sliderLabels[i].setFont (sliderLabelFont);
        sliderLabels[i].setJustificationType(juce::Justification::centred);
    }

    //Add Chebyshev Labels
    for (int i = (int) chebyshev1; i < numberOfChebyshevs; i++)
    {
        chebyshevLabels[i].setText("Chebyshev " + std::to_string(i+1), {});
        chebyshevLabels[i].attachToComponent(&chebyshevAmpSliders[i], false);
        chebyshevLabels[i].setFont(sliderLabelFont);
        chebyshevLabels[i].setJustificationType(juce::Justification::centred);
    }
    
    //Add Combo Box Labels
    //Add Chebyshev Labels
    for (int i = (int) iNumBox; i < numberOfComboBoxes; i++)
    {
        comboBoxLabels[i].setText(comboBoxLabelText[i], {});
        comboBoxLabels[i].attachToComponent(&comboBoxes[i], false);
        comboBoxLabels[i].setFont(sliderLabelFont);
        comboBoxLabels[i].setJustificationType(juce::Justification::centred);
    }
    
    
    //Add Charts
    container.addAndMakeVisible(totalChart);
    container.addAndMakeVisible(chebyshevChart);
    totalChart.setTitle("F(x)");
    chebyshevChart.setTitle("F(sin(2*PI*t))");
    totalChart.plotChebyshev(-1, 1, WaveshaperChart::straightChart);
    chebyshevChart.plotChebyshev(0, 1, WaveshaperChart::sinChart);
    
    //Add Midi Keyboard
    addAndMakeVisible (midiKeyboard);
    midiKeyboard.setScrollButtonWidth(getWidth()/20);

    // Add a label that will display the current timecode and status..
    addAndMakeVisible (timecodeDisplayLabel);
    timecodeDisplayLabel.setFont (Font (Font::getDefaultMonospacedFontName(), 30.0f, Font::plain));
    timecodeDisplayLabel.setJustificationType(juce::Justification::centred);
    

    lastUIWidth .referTo (owner.state.state.getChildWithName ("uiState").getPropertyAsValue ("width",  nullptr));
    lastUIHeight.referTo (owner.state.state.getChildWithName ("uiState").getPropertyAsValue ("height", nullptr));

    
    
    //Add Viewport
    myViewport.setViewedComponent(&container, false);
    addAndMakeVisible(myViewport);
    setResizable(true, true);
    setSize (lastUIWidth.getValue(), lastUIHeight.getValue());
    
    container.setBounds(0, 0, getWidth(), getHeight());
    myViewport.setBounds(0, timecodeDisplayLabel.getHeight(), getWidth(), getHeight() - midiKeyboard.getHeight() - timecodeDisplayLabel.getHeight() - 8);
    lastUIWidth. addListener (this);
    lastUIHeight.addListener (this);

    updateTrackProperties();
    

    // start a timer which will keep our timecode display updated
    startTimerHz (30);
}
   
   

JuceDemoPluginAudioProcessorEditor::~JuceDemoPluginAudioProcessorEditor(){}
void JuceDemoPluginAudioProcessorEditor::buttonClicked (juce::Button* button)
{
    if (button == &buttons[resetEnvelope])
    {
        sliders[releaseSlider].setValue(0.0);
        sliders[sustainSlider].setValue(100.0);
        sliders[attackSlider].setValue(0.0);
   }else  if (button == &buttons[resetModEnvelope])  {
       // [6]
       sliders[mreleaseSlider].setValue(0.0);
       sliders[msustainSlider].setValue(100.0);
       sliders[mattackSlider].setValue(0.0);
  }
    /*else if (button == &buttons[savePreset])
    {
        getProcessor()->getStateInformation();
    }*/
}

//===============================================================================
void JuceDemoPluginAudioProcessorEditor::paint (Graphics& g)
{
    g.setColour (backgroundColour);
    g.fillAll();
}

void JuceDemoPluginAudioProcessorEditor::resized()
{
    const float flexBoxWidth  = getWidth()/ 9;
    const float flexBoxHeight  = getHeight()/ 9;
    const Font  myFont = Font(getHeight()/40);
    const int textBoxWidth  = getWidth()/20;
    const int textBoxHeight = myFont.getHeight();
    auto appBounds  = getLocalBounds();
    
    container.setBounds(0, 0, getWidth(), getHeight());
    myViewport.setBounds(0, timecodeDisplayLabel.getHeight(), getWidth(), getHeight() - midiKeyboard.getHeight() - timecodeDisplayLabel.getHeight() - 8);
    
    auto bounds         = container.getLocalBounds();
    auto left           = bounds.removeFromLeft(bounds.getWidth()/2);
    auto topLeft        = left.removeFromTop(left.getHeight()/2);
    auto bottomLeft     = left;
    auto right          = bounds;
    auto topRight       = right.removeFromTop(right.getHeight()/2);
    auto bottomRight    = right;
    
    auto totalChartBounds       = bottomRight.removeFromLeft(bottomRight.getWidth()/2);
    auto chebyshevChartBounds   = bottomRight.removeFromLeft(bottomRight.getWidth());
    
        
    timecodeDisplayLabel.setBounds (appBounds.removeFromTop (30));
    midiKeyboard        .setBounds (appBounds.removeFromBottom (70));
    midiKeyboard.setScrollButtonWidth(getWidth()/20);
    
    juce::FlexBox sliderFlexBox;
    sliderFlexBox.flexWrap = juce::FlexBox::Wrap::wrap;
    sliderFlexBox.justifyContent = juce::FlexBox::JustifyContent::spaceAround;
    sliderFlexBox.alignContent = juce::FlexBox::AlignContent::spaceAround;
    sliderFlexBox.flexDirection = juce::FlexBox::Direction::row;
    
    juce::FlexBox comboBoxFlexBox;
    comboBoxFlexBox.flexWrap = juce::FlexBox::Wrap::wrap;
    comboBoxFlexBox.justifyContent = juce::FlexBox::JustifyContent::spaceAround;
    comboBoxFlexBox.alignContent = juce::FlexBox::AlignContent::spaceAround;
    comboBoxFlexBox.flexDirection = juce::FlexBox::Direction::row;
    
    juce::FlexBox chebyshevFlexBox;
    chebyshevFlexBox.flexWrap = juce::FlexBox::Wrap::wrap;
    chebyshevFlexBox.justifyContent = juce::FlexBox::JustifyContent::spaceAround;
    chebyshevFlexBox.alignContent = juce::FlexBox::AlignContent::spaceAround;
    chebyshevFlexBox.flexDirection = juce::FlexBox::Direction::row;
    
    for (int i = (int) gainSlider; i < numberOfSliders; i++)
    {
        sliderLabels[i].setFont(myFont);
        sliders[i].setTextBoxStyle(juce::Slider::TextBoxBelow, true, textBoxWidth, textBoxHeight);
        sliders[i].setNumDecimalPlacesToDisplay(0);
        sliderFlexBox.items.add(juce::FlexItem (sliders[i]).withMinWidth (flexBoxWidth).withMinHeight (flexBoxHeight));
    }
    
    for (int i= chebyshev1; i < numberOfChebyshevs; i++)
    {
        chebyshevLabels[i].setFont(myFont);
        chebyshevAmpSliders[i].setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
        chebyshevFlexBox.items.add(juce::FlexItem (chebyshevAmpSliders[i]).withMinWidth (flexBoxWidth).withMinHeight (flexBoxHeight));
        
    }
    
    for (int i= iNumBox; i < numberOfComboBoxes; i++)
    {
        comboBoxFlexBox.items.add(juce::FlexItem (comboBoxes[i]).withMinWidth (flexBoxWidth).withMinHeight (flexBoxHeight));
    }
    
    for (int i= savePreset; i < numberOfButtons; i++)
    {
        comboBoxFlexBox.items.add(juce::FlexItem (buttons[i]).withMinWidth (flexBoxWidth).withMinHeight (flexBoxHeight));
    }
    
    
    
    sliderFlexBox.performLayout(topLeft);
    chebyshevFlexBox.performLayout(bottomLeft);
    comboBoxFlexBox.performLayout(topRight);
    totalChart.setBounds(totalChartBounds);
    chebyshevChart.setBounds(chebyshevChartBounds);
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
    if (&control == &sliders[gainSlider])
        return 0;
    if (&control == &sliders[delaySlider])
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

    displayText << String (pos.bpm, 2) << " BPM "
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

void JuceDemoPluginAudioProcessorEditor::sliderValueChanged (juce::Slider * slider)
{
    
    for (int i= chebyshev1; i < numberOfChebyshevs; i++)
    {
        if (slider == &chebyshevAmpSliders[i])
        {
            totalChart.setChebyshevAmplitudes(chebyshevAmpSliders[i].getValue(), (SineWaveVoice::ChebyshevLevels) (i+1));
            chebyshevChart.setChebyshevAmplitudes(chebyshevAmpSliders[i].getValue(), (SineWaveVoice::ChebyshevLevels) (i+1));
            return;
        }
    }
    
}
// called when the stored window size changes
void JuceDemoPluginAudioProcessorEditor::valueChanged (Value&)
{
    setSize (lastUIWidth.getValue(), lastUIHeight.getValue());
}
