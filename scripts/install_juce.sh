#!/bin/bash

# JUCE download URL
zip_url="https://github.com/juce-framework/JUCE/archive/refs/tags/8.0.0.zip"

# temp file path
file_path="./juce.tmp.zip"

# Download the zip file using wget
wget "$zip_url" -O "$file_path"

# # Extract the zip file into the extract directory
# unzip -q "$file_path" -d ./_JUCE

# # Delete the zip file
# rm "$file_path"
