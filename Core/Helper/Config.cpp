#include "Config.h"
#include <fstream>

Config* Config::instance = nullptr;

Config* Config::get()
{
    if (instance == nullptr)
    {
        instance = new Config();
        auto* f = new std::fstream("config.json");
        instance->data = nlohmann::json::parse(*f);
    }
    return instance;
}

const nlohmann::json &Config::getData() const
{
    return data;
}

uint32_t Config::getMinPoints()
{
    if (data.contains("minPoints")) {
        return data["minPoints"].get<uint32_t>();
    }

    return 2;
}

uint64_t Config::getMinLabel()
{
    if (data.contains("minLabel")) {
        return data["minLabel"].get<uint64_t>();
    }

    return 1e14;
}

uint64_t Config::getMaxLabel()
{
    if (data.contains("maxLabel")) {
        return data["maxLabel"].get<uint64_t>();
    }

    return 1e14;
}

double Config::getEpsilon()
{
    if (data.contains("epsilon")) {
        return data["epsilon"].get<double>();
    }

    return 0.5;
}
