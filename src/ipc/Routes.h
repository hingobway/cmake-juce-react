#pragma once

#include <unordered_map>
#include <string>

#include <JuceHeader.h>

class Routes
{
private:
  std::unordered_map<std::string, std::function<juce::var(juce::var &)>> routes;

  juce::var _defaultRoute();

  // ROUTES

  juce::var routeAnnounce(juce::var &);

public:
  Routes();

  juce::var runRoute(juce::String route, juce::var &params);

  /**
   * return a string error to be thrown.
   * @param code a `CODE_STRING` to be thrown.
   * @return a std::string based on the code
   */
  static std::string err(juce::String code);
};
