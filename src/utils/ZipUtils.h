#pragma once

#include <juce_core/juce_core.h>

#include <vector>
#include <string>
#include <unordered_map>
#include <cstddef>

class ZipUtils
{
private:
  //
public:
  static juce::ZipFile *getClientZip();

  static std::vector<std::byte> bufferFrom(juce::InputStream &stream);

  static const char *getMimeType(const juce::String &filename);
};
