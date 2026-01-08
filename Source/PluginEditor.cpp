#include "PluginProcessor.h"
#include "juce_events/juce_events.h"
#include "juce_graphics/juce_graphics.h"
#include "juce_gui_basics/juce_gui_basics.h"
#include "BinaryData.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p)
    , processorRef (p)
    , freqSliderAttachment(processorRef.getState(), "freqHz", frequencySlider)
    , playButtonAttachment(processorRef.getState(), "play", playButton)
    , ampSliderAttachment(processorRef.getState(), "amp", amplitudeSlider)
{
    juce::ignoreUnused (processorRef);

    // Load bkg img from binary data
    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::theremin_jpg, BinaryData::theremin_jpgSize);

    // freq slider setup
    frequencySlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    frequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 50);
    // frequencySlider.setRange(0.0f, 1.0f, 0.01f);
    addAndMakeVisible(frequencySlider);
    
    // set up freq label
    // frequencyLabel.setColour(juce::Label::ColourIds::outlineColourId, juce::Colours::wheat);
    frequencyLabel.setJustificationType(juce::Justification::centred);    
    addAndMakeVisible(frequencyLabel);

    // amp slider setup
    amplitudeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    amplitudeSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 100, 50);
    addAndMakeVisible(amplitudeSlider);

    // play Button Setup
    playButton.setButtonText("Play");
    playButton.setToggleState(true, juce::NotificationType::dontSendNotification); 
    playButton.setClickingTogglesState(true);

    playButton.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::forestgreen);
    playButton.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::rebeccapurple);

    playButton.onClick = [this]()
    {
        // change state of the button when it is clicked
        const bool isPlaying = playButton.getToggleState();
        playButton.setButtonText(isPlaying ? "Playing": "Bypassed");
    };
    addAndMakeVisible(playButton);



    setSize (710, 947);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    if (backgroundImage.isValid())
    {
        g.drawImage(backgroundImage, getLocalBounds().toFloat(), juce::RectanglePlacement::stretchToFit);
    }
    else
    {
        g.fillAll (juce::Colours::black);
    }
}

void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    // square.setBounds(50, 250, 300, 100);
    // frequencyLabel.setBounds (getWidth() / 2 - 50, getHeight() / 2 - 120, 100, 20);
    frequencySlider.setBounds(getWidth() / 2 - 100, getHeight() / 2 - 50, 200, 100);
    playButton.setBounds(getWidth() / 2 - 50, getHeight() / 2 + 100, 100, 30);
    amplitudeSlider.setBounds(getWidth() / 2 - 300, getHeight() / 2 - 100, 100, 200);
}
