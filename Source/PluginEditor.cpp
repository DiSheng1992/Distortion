/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
DistortionAudioProcessorEditor::DistortionAudioProcessorEditor (DistortionAudioProcessor& p)
    : AudioProcessorEditor (p), gainLabel_("","Gain:")
{
    // Set up the sliders
    addAndMakeVisible (&gainSlider_);
    gainSlider_.setSliderStyle (Slider::Rotary);
    gainSlider_.addListener (this);
    gainSlider_.setRange (1, 10.0, 0.01);
    gainLabel_.attachToComponent(&gainSlider_,false);     //Attach label to component (slider)
    gainLabel_.setFont(Font (11.0f));
    
    //Set up the combo box
    addAndMakeVisible(&typeComboBox_);
    typeComboBox_.addListener(this);
    typeComboBox_.setEditableText (false);
    typeComboBox_.setJustificationType (Justification::centredLeft);
    typeComboBox_.setTextWhenNothingSelected (String::empty);
    typeComboBox_.setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    typeComboBox_.addItem (TRANS("Soft clipping (poly)"), 1);
    typeComboBox_.addItem (TRANS("Soft clipping (exp)"), 2);
    typeComboBox_.addItem (TRANS("Full-wave rectifier"), 3);
    typeComboBox_.addItem (TRANS("Half-wave rectifier"), 4);
    typeComboBox_.addItem (TRANS("Hard clipping"), 5);
   

    
    // add the triangular resizer component for the
    // bottom-right of the UI
    addAndMakeVisible(resizer_ = new ResizableCornerComponent (this, &resizeLimits_));
    resizeLimits_.setSizeLimits(370, 140, 500, 300);
    
    
    
    // set our component’s initial size to be the last one that was stored in the filter’s settings
    setSize(p.lastUIWidth_,p.lastUIHeight_);
    
    
    
    startTimer(50); // a timer is start that causes the timeCallback method to be called by the system every 50 ms to keeping the on-screen controls synchronized with the values of each parameter in the DelayAudioProcessor object.
    
}

DistortionAudioProcessorEditor::~DistortionAudioProcessorEditor()
{

}

//==============================================================================
void DistortionAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);

    g.setColour (Colours::black);
    g.setFont (15.0f);
   // g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void DistortionAudioProcessorEditor::resized()
{
    
    gainSlider_.setBounds (20, 20, 150, 40);
    typeComboBox_.setBounds (170, 20, 150, 40);
    resizer_->setBounds(getWidth() - 16, getHeight() - 16, 16, 16);
    getProcessor().lastUIWidth_ = getWidth();
    getProcessor().lastUIHeight_ = getHeight();
}

void DistortionAudioProcessorEditor::timerCallback()
{
    DistortionAudioProcessor& ourProcessor = getProcessor();
    gainSlider_.setValue(ourProcessor.gainControl_,
                                dontSendNotification);

}

void DistortionAudioProcessorEditor::sliderValueChanged(Slider* slider){
    
    if (slider == &gainSlider_)
    {
        getProcessor().setParameterNotifyingHost(DistortionAudioProcessor::kGainControl,(float)gainSlider_.getValue());
     
    }
  
    
}

void DistortionAudioProcessorEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
   DistortionAudioProcessor& ourProcessor = getProcessor();
    //[/UsercomboBoxChanged_Pre]
    
    if (comboBoxThatHasChanged == &typeComboBox_)
    {
        //[UserComboBoxCode_typeComboBox] -- add your combo box handling code here..
        ourProcessor.SetType((DistortionAudioProcessor::Types) typeComboBox_.getSelectedItemIndex());
        //[/UserComboBoxCode_typeComboBox]
      
        
    }
    
    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}
