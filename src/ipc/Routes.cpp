#include "Routes.h"

#include "../utils/json.h"

Routes::Routes()
{
  routes["announce"] = [this](auto &p)
  { return routeAnnounce(p); };
}

// --------------------------------------------
// ROUTES

juce::var Routes::routeAnnounce(juce::var &params)
{
  // get params
  auto name = params.getProperty("name", juce::var::undefined());
  if (!name.isString() || !name.toString().length())
    throw err("MISSING_NAME");

  // return
  JSON_OBJ(data)
  {
    data->setProperty("text", "hello world!");
    data->setProperty("username", name);
    data->setProperty("t_computed", juce::Time().currentTimeMillis());
  }
  return juce::var(data);
}

// --------------------------------------------

juce::var Routes::runRoute(juce::String rin, juce::var &params)
{
  auto route = rin.toStdString();
  if (routes.find(route) != routes.end())
    return routes[route](params);

  return _defaultRoute();
}

juce::var Routes::_defaultRoute()
{
  throw err("ROUTE_NOT_FOUND");
}

std::string Routes::err(juce::String code)
{
  return code.toStdString();
}
