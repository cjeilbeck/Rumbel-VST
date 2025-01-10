#include "PluginProcessor.h"
#include "PluginEditor.h"

RumbelAudioProcessor::RumbelAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
    parameters(*this, nullptr, "PARAMETERS", createParameterLayout())
{
}
#endif

RumbelAudioProcessor::~RumbelAudioProcessor() {}

juce::AudioProcessorValueTreeState::ParameterLayout RumbelAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "DISTORTION", "Distortion (Tanh)", 1.0f, 10.0f, 1.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "ARCTAN_DISTORTION", "Distortion (Arctan)", 1.0f, 10.0f, 1.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "MIX", "Mix", 0.0f, 1.0f, 0.5f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "MASTER_GAIN", "Master Gain", 0.0f, 2.0f, 1.0f));

    return { params.begin(), params.end() };
}

void RumbelAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {}

void RumbelAudioProcessor::releaseResources() {}

#ifndef JucePlugin_PreferredChannelConfigurations
bool RumbelAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
}
#endif

void RumbelAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;

    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    float tanhAmount = parameters.getRawParameterValue("DISTORTION")->load();
    float arctanAmount = parameters.getRawParameterValue("ARCTAN_DISTORTION")->load();
    float mix = parameters.getRawParameterValue("MIX")->load();
    float masterGain = parameters.getRawParameterValue("MASTER_GAIN")->load();

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            float inputSample = channelData[sample];

            float tanhDistorted = std::tanh(tanhAmount * inputSample);
            float arctanDistorted = (2.0f / juce::MathConstants<float>::pi) * std::atan(arctanAmount * inputSample);

            float blendedSample = (1.0f - mix) * tanhDistorted + mix * arctanDistorted;

            channelData[sample] = blendedSample * masterGain;
        }
    }
}

void RumbelAudioProcessor::getStateInformation(juce::MemoryBlock& destData) {}

void RumbelAudioProcessor::setStateInformation(const void* data, int sizeInBytes) {}

const juce::String RumbelAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool RumbelAudioProcessor::acceptsMidi() const { return false; }
bool RumbelAudioProcessor::producesMidi() const { return false; }
bool RumbelAudioProcessor::isMidiEffect() const { return false; }
double RumbelAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int RumbelAudioProcessor::getNumPrograms() { return 1; }
int RumbelAudioProcessor::getCurrentProgram() { return 0; }
void RumbelAudioProcessor::setCurrentProgram(int index) {}
const juce::String RumbelAudioProcessor::getProgramName(int index) { return {}; }
void RumbelAudioProcessor::changeProgramName(int index, const juce::String& newName) {}

juce::AudioProcessorEditor* RumbelAudioProcessor::createEditor()
{
    return new RumbelAudioProcessorEditor(*this);
}

bool RumbelAudioProcessor::hasEditor() const { return true; }

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RumbelAudioProcessor();
}
