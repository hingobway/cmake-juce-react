#pragma once

#include <JuceHeader.h>

namespace Obj
{
  using Ptr = juce::DynamicObject::Ptr;
}
#define JSON_OBJ(name) Obj::Ptr name = new juce::DynamicObject();
