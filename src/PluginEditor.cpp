#include "PluginEditor.h"

#include <map>

#include "PluginProcessor.h"
#include "CONSTANTS.h"
#include "utils/json.h"
#include "utils/ZipUtils.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &p)
    : AudioProcessorEditor(&p), processorRef(p), routes(),
      webComponent{
          juce::WebBrowserComponent::Options{}
              .withBackend(juce::WebBrowserComponent::Options::Backend::webview2)
              .withWinWebView2Options(juce::WebBrowserComponent::Options::WinWebView2{}.withUserDataFolder(juce::File::getSpecialLocation(juce::File::SpecialLocationType::tempDirectory)))
              .withNativeIntegrationEnabled()

              .withResourceProvider([this](const auto &url)
                                    { return this->getResource(url); })

              .withNativeFunction(
                  "command", [this](auto &vars, auto resolve)
                  {
                  try
                  {
                    const juce::Array<juce::var> &v = vars;
                    juce::var input = v[0];

                    if (!input.isObject())
                      throw Routes::err("INVALID_REQUEST");

                    // get command type
                    auto ts = input.getProperty("type", juce::var::undefined());
                    if (!ts.isString())
                      throw Routes::err("INVALID_TYPE");

                    juce::String type = ts.toString();
                    auto params = input.getProperty("data", juce::var::undefined());

                    // TYPE ROUTER
                    auto data = this->routes.runRoute(type, params);

                    JSON_OBJ(out)
                    {
                      out->setProperty("data", data);
                    }

                    return resolve(juce::JSON::toString(juce::var(out), true));
                  }
                  catch(const std::string& e)
                  {
                    JSON_OBJ(out)
                    {
                      out->setProperty("error", juce::String(e));
                    }

                    return resolve(juce::JSON::toString(juce::var(out), true));
                  }

                  /*  */ })}
{
  juce::ignoreUnused(processorRef);

  setSize(800, 500);

  #ifdef JUCE_DEBUG
    this->webComponent.goToURL(OPTS::DEV_URL);
  #else
    this->webComponent.goToURL(juce::WebBrowserComponent::getResourceProviderRoot());
  #endif

  addAndMakeVisible(this->webComponent);

  DBG("\n\nMOUNTED\n\n");
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint(juce::Graphics &g)
{
  g.fillAll(juce::Colour(0xff18181b));
}

void AudioPluginAudioProcessorEditor::resized()
{
  this->webComponent.setBounds(getLocalBounds());
}

std::optional<juce::WebBrowserComponent::Resource> AudioPluginAudioProcessorEditor::getResource(const juce::String &url)
{
  try
  {

    // get path
    juce::String path = url == "/" ? "index.html" : url.fromFirstOccurrenceOf("/", /* includeSubstring: */ false, false);

    // attempt to find in zip archive
    auto *zip = ZipUtils::getClientZip();
    if (zip)
    {
      auto *entry = zip->getEntry(path, true);
      if (!entry)
        throw 0;

      auto stream = juce::rawToUniquePtr(zip->createStreamForEntry(*entry));
      auto buffer = ZipUtils::bufferFrom(*stream);
      auto mime = ZipUtils::getMimeType(entry->filename);

      return juce::WebBrowserComponent::Resource{std::move(buffer), std::move(mime)};
    }
  }
  catch (int &)
  {
  }
  return std::nullopt;
}
