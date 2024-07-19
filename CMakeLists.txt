cmake_minimum_required(VERSION 3.22)

# project init
project(JUCE_CMAKE_TEST_PLUGIN VERSION 0.1.0)

add_subdirectory(_JUCE)

# juce init
juce_add_plugin(AudioPlugin
  COMPANY_NAME foster
  PLUGIN_MANUFACTURER_CODE Fost
  PLUGIN_CODE Fcm0

  NEEDS_WEBVIEW2 TRUE

  FORMATS VST3 Standalone
  PRODUCT_NAME "WebkitPlugin"
)

juce_generate_juce_header(AudioPlugin)

# compile options
target_compile_definitions(AudioPlugin
  PUBLIC
  JUCE_USE_CURL=0
  JUCE_VST3_CAN_REPLACE_VST2=0
  DONT_SET_USING_JUCE_NAMESPACE=1
  JUCE_WEB_BROWSER=1
  JUCE_USE_WIN_WEBVIEW2_WITH_STATIC_LINKING=1
)

file(GLOB_RECURSE HEADER_FILES src/*.h)

# add source files
target_sources(AudioPlugin
  PRIVATE
  ${HEADER_FILES} # make sure header files appear in solution

  src/PluginEditor.cpp
  src/PluginProcessor.cpp
  src/ipc/Routes.cpp
  src/utils/ZipUtils.cpp
)

# register source tree
# file(GLOB_RECURSE SOURCE_FILES src/*)
# source_group("0_SRC" TREE ../src PREFIX "0_SRC" FILES ${SOURCE_FILES})

# add binary data
juce_add_binary_data(AudioPluginData
  SOURCES
  assets/client.zip
)

target_link_libraries(AudioPlugin
  PRIVATE
  AudioPluginData
  juce::juce_audio_utils
  juce::juce_gui_extra

  PUBLIC
  juce::juce_recommended_config_flags
  juce::juce_recommended_lto_flags
  juce::juce_recommended_warning_flags
)
