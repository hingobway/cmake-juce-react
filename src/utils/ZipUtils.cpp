#include "ZipUtils.h"

#include <BinaryData.h>

juce::ZipFile *ZipUtils::getClientZip()
{
  static auto stream = std::make_unique<juce::MemoryInputStream>(BinaryData::client_zip, BinaryData::client_zipSize, false);

  static juce::ZipFile zf(stream.get(), false);

  return &zf;
}

std::vector<std::byte> ZipUtils::bufferFrom(juce::InputStream &stream)
{
  std::vector<std::byte> buffer((size_t)stream.getTotalLength());

  stream.setPosition(0);
  stream.read(buffer.data(), buffer.size());

  return buffer;
}

const char *ZipUtils::getMimeType(const juce::String &filename)
{

  auto ext = filename.fromLastOccurrenceOf(".", false, false).toLowerCase().toStdString();

  static std::unordered_map<std::string, const char *> mimeMap{
      {{"htm"}, "text/html"},
      {{"html"}, "text/html"},
      {{"txt"}, "text/plain"},
      {{"jpg"}, "image/jpeg"},
      {{"jpeg"}, "image/jpeg"},
      {{"svg"}, "image/svg+xml"},
      {{"ico"}, "image/vnd.microsoft.icon"},
      {{"json"}, "application/json"},
      {{"png"}, "image/png"},
      {{"css"}, "text/css"},
      {{"map"}, "application/json"},
      {{"js"}, "text/javascript"},
      {{"woff2"}, "font/woff2"}};

  if (mimeMap.find(ext) != mimeMap.end())
    return mimeMap[ext];

  return "";
}
