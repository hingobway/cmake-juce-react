#include "PluginEditor.h"

#include "PluginProcessor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor& p)
  : AudioProcessorEditor(&p), processorRef(p)
{
  juce::ignoreUnused(processorRef);
  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
  setSize(400, 300);

  this->webComponent.goToURL("http://localhost:5173");
  //this->webComponent.goToURL(juce::WebBrowserComponent::getResourceProviderRoot());

  addAndMakeVisible(this->webComponent);


  DBG("\n\nARE WE HERE??\n\n");

}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint(juce::Graphics& g)
{
  // (Our component is opaque, so we must completely fill the background with a solid colour)
  g.fillAll(juce::Colour(0xff18181b));

}

void AudioPluginAudioProcessorEditor::resized()
{
  this->webComponent.setBounds(getLocalBounds());
}

std::optional<juce::WebBrowserComponent::Resource> AudioPluginAudioProcessorEditor::getResource(const juce::String& url)
{

  juce::ignoreUnused(url);

  // return std::optional<juce::WebBrowserComponent::Resource>();
  return std::nullopt;
}
