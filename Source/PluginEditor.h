#pragma once

#include <JuceHeader.h>
#include <memory>


class RumbelAudioProcessor;


class CustomKnobLookAndFeel : public juce::LookAndFeel_V4
{
public:
    CustomKnobLookAndFeel(juce::Image knobImage) : image(knobImage) {}

    void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
        float sliderPos, float minSliderPos, float maxSliderPos,
        const juce::Slider::SliderStyle style, juce::Slider& slider) override
    {
        if (image.isValid())
        {
            

            
            const int knobWidth = image.getWidth();
            const int knobHeight = image.getHeight();

            g.drawImage(image,
                (int)(sliderPos - knobWidth / 2), y + height / 2 - knobHeight / 2, 
                knobWidth, knobHeight,                                            
                0, 0, image.getWidth(), image.getHeight());                      
        }
        else
        {
            
            juce::LookAndFeel_V4::drawLinearSlider(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
        }
    }

private:
    juce::Image image;
};

//==============================================================================
class RumbelAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    RumbelAudioProcessorEditor(RumbelAudioProcessor&);
    ~RumbelAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    
    RumbelAudioProcessor& audioProcessor;

    
    juce::Image backgroundImage;
    juce::Image tanhKnobImage;
    juce::Image arctanKnobImage;

    
    std::unique_ptr<CustomKnobLookAndFeel> tanhKnobLookAndFeel;
    std::unique_ptr<CustomKnobLookAndFeel> arctanKnobLookAndFeel;

    
    juce::Slider distortionSlider;
    juce::Slider arctanDistortionSlider;
    juce::Slider mixSlider;
    juce::Slider masterGainSlider;

    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> distortionAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> arctanDistortionAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> masterGainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RumbelAudioProcessorEditor)
};
