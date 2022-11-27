#include "Config.h"
#include <fstream>
#include <iostream>

namespace Client {
    Config* Config::instance = nullptr;

    Config* Config::get()
    {
        if (instance == nullptr)
        {
            instance = new Config();
            auto* f = new std::fstream("Client/config.override.json");
            if (f->is_open())
            {
                std::cout << "found override Config" << std::endl;
                instance->data = nlohmann::json::parse(*f);
            }
            else
            {
                std::cout << "Using Standard Config" << std::endl;
                auto* f = new std::fstream("Client/config.json");
                instance->data = nlohmann::json::parse(*f);
            }
        }
        return instance;
    }

    const nlohmann::json &Config::getData() const
    {
        return data;
    }
}