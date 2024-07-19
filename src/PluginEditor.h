#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"
#include "ipc/Routes.h"

//==============================================================================
class AudioPluginAudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
  explicit AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &);
  ~AudioPluginAudioProcessorEditor() override;

  //==============================================================================
  void paint(juce::Graphics &) override;
  void resized() override;

  std::optional<juce::WebBrowserComponent::Resource> getResource(const juce::String &url);

private:
  // This reference is provided as a quick way for your editor to
  // access the processor object that created it.
  AudioPluginAudioProcessor &processorRef;

  juce::WebBrowserComponent webComponent;

  Routes routes;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)
};
