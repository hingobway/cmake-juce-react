#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"

//==============================================================================
class AudioPluginAudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
  explicit AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor&);
  ~AudioPluginAudioProcessorEditor() override;

  //==============================================================================
  void paint(juce::Graphics&) override;
  void resized() override;

  std::optional<juce::WebBrowserComponent::Resource> getResource(const juce::String& url);

private:
  // This reference is provided as a quick way for your editor to
  // access the processor object that created it.
  AudioPluginAudioProcessor& processorRef;

  juce::WebBrowserComponent webComponent{
      juce::WebBrowserComponent::Options{}
          .withBackend(juce::WebBrowserComponent::Options::Backend::webview2)
          .withWinWebView2Options(juce::WebBrowserComponent::Options::WinWebView2{}.withUserDataFolder(juce::File::getSpecialLocation(juce::File::SpecialLocationType::tempDirectory)))
          .withNativeIntegrationEnabled()

          .withResourceProvider([this](const auto& url)
                                { return this->getResource(url); })

          .withNativeFunction("runTest", [](auto& vars, auto resolve) {
            auto& a = vars;
            DBG("RECEIVED");

            for (auto& it : a) {
              auto dd = juce::JSON::toString(it, juce::JSON::FormatOptions().withMaxDecimalPlaces(4));

              DBG(dd);

              auto str = it.toString();
              DBG(str);

              auto b = it.getProperty("c", 0);
              if (!b.equalsWithSameType(juce::var(0)))
              {
                DBG("c: " << b.toString());
                if (b.isBool()) DBG("it's a boolean!");
              }
            }

            // PREP RESPONSE

            auto obj = new juce::DynamicObject();
            obj->setProperty("type", "announce");
            {
              auto data = new juce::DynamicObject();
              obj->setProperty("data", data);

              data->setProperty("message", "hello world!");
              data->setProperty("text_2", false);
              data->setProperty("undef", juce::var::undefined());
            }

            resolve(juce::JSON::toString(obj, true));
          })

    //
  };

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)
};
