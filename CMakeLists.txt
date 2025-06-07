cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ----------------------------------------
# VARIABLES
set(PROJECT_NAME "CMAKE_JUCE_REACT")
set(TARGET_NAME "WebJucePlugin")
set(VERSION_NUMBER 0.1.0)

# ----------------------------------------

# PROJECT INIT
project(${PROJECT_NAME} VERSION ${VERSION_NUMBER})

# PACKAGE INCLUDE
add_subdirectory(include/JUCE JUCE)

# JUCE CONFIG
juce_add_plugin(${TARGET_NAME}
  PRODUCT_NAME "${TARGET_NAME}"

  # manufacturer
  COMPANY_NAME "foster"
  PLUGIN_MANUFACTURER_CODE "Fost"
  BUNDLE_ID "audio.foster.webjuce"

  # plugin
  PLUGIN_NAME "CMake JUCE React"
  PLUGIN_CODE "Fcm0"
  VST3_CATEGORIES Fx
  AU_MAIN_TYPE kAudioUnitType_Effect

  # executable
  FORMATS Standalone VST3 AU Standalone
  COPY_PLUGIN_AFTER_BUILD TRUE
  NEEDS_WEBVIEW2 TRUE
)

target_compile_definitions(${TARGET_NAME}
  PUBLIC
  JUCE_WEB_BROWSER=1
  JUCE_USE_WIN_WEBVIEW2_WITH_STATIC_LINKING=1
  JUCE_USE_CURL=0
  JUCE_VST3_CAN_REPLACE_VST2=0

  DONT_SET_USING_JUCE_NAMESPACE=1

  CMAKE_BUILD_TYPE="${CMAKE_BUILD_TYPE}"
  VERSION="${CURRENT_VERSION}"

  PRODUCT_NAME_WITHOUT_VERSION="${TARGET_NAME}"
)

# ADD FILES
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)
target_sources(${TARGET_NAME} PRIVATE ${SOURCE_FILES})

# BINARY DATA
file(GLOB_RECURSE BINARY_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/assets/*")
list(FILTER BINARY_FILES EXCLUDE REGEX "/\\.DS_Store$")
juce_add_binary_data(BinaryData SOURCES ${BINARY_FILES})

# ADD LIBRARIES
target_link_libraries(${TARGET_NAME}
  PRIVATE
  BinaryData

  juce::juce_audio_devices
  juce::juce_audio_formats
  juce::juce_audio_utils
  juce::juce_audio_processors
  juce::juce_gui_basics
  juce::juce_gui_extra

  PUBLIC
  juce::juce_recommended_config_flags
  juce::juce_recommended_lto_flags
  juce::juce_recommended_warning_flags
)