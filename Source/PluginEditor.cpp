#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "BinaryData.h" 

//==============================================================================
RumbelAudioProcessorEditor::RumbelAudioProcessorEditor(RumbelAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    setSize(700, 700);

    
    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::flatbackground_jpg, BinaryData::flatbackground_jpgSize);
    tanhKnobImage = juce::ImageCache::getFromMemory(BinaryData::Sagebrush_jpg, BinaryData::Sagebrush_jpgSize);
    arctanKnobImage = juce::ImageCache::getFromMemory(BinaryData::RIVERORANGE_jpg, BinaryData::RIVERORANGE_jpgSize);

    
    tanhKnobLookAndFeel = std::make_unique<CustomKnobLookAndFeel>(tanhKnobImage);
    arctanKnobLookAndFeel = std::make_unique<CustomKnobLookAndFeel>(arctanKnobImage);

    
    distortionSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    distortionSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 150, 20);
    distortionSlider.setLookAndFeel(tanhKnobLookAndFeel.get());
    addAndMakeVisible(distortionSlider);
    distortionAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.parameters, "DISTORTION", distortionSlider);

    
    arctanDistortionSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    arctanDistortionSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 150, 20);
    arctanDistortionSlider.setLookAndFeel(arctanKnobLookAndFeel.get());
    addAndMakeVisible(arctanDistortionSlider);
    arctanDistortionAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.parameters, "ARCTAN_DISTORTION", arctanDistortionSlider);

    
    mixSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    mixSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 150, 20);
    mixSlider.setLookAndFeel(tanhKnobLookAndFeel.get());
    addAndMakeVisible(mixSlider);
    mixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.parameters, "MIX", mixSlider);

    
    masterGainSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    masterGainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 150, 20);
    masterGainSlider.setLookAndFeel(arctanKnobLookAndFeel.get());
    addAndMakeVisible(masterGainSlider);
    masterGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.parameters, "MASTER_GAIN", masterGainSlider);
}

RumbelAudioProcessorEditor::~RumbelAudioProcessorEditor()
{
    
    distortionSlider.setLookAndFeel(nullptr);
    arctanDistortionSlider.setLookAndFeel(nullptr);
}

void RumbelAudioProcessorEditor::paint(juce::Graphics& g)
{
    
    g.drawImage(backgroundImage, getLocalBounds().toFloat());
}

void RumbelAudioProcessorEditor::resized()
{
    
    const int sliderWidth = 500;  
    const int sliderHeight = 40; 
    const int centerX = getWidth() / 2;
    const int verticalSpacing = 20; 

    int currentY = 100; 

    
    distortionSlider.setBounds(centerX - (sliderWidth / 2), currentY, sliderWidth, sliderHeight);
    currentY += sliderHeight + verticalSpacing;

    arctanDistortionSlider.setBounds(centerX - (sliderWidth / 2), currentY, sliderWidth, sliderHeight);
    currentY += sliderHeight + verticalSpacing;

    mixSlider.setBounds(centerX - (sliderWidth / 2), currentY, sliderWidth, sliderHeight);
    currentY += sliderHeight + verticalSpacing;

    masterGainSlider.setBounds(centerX - (sliderWidth / 2), currentY, sliderWidth, sliderHeight);
}

