#ifndef SUBSCALE_CONFIG_H
#define SUBSCALE_CONFIG_H

#include <nlohmann/json.hpp>
#include <string>

namespace Client {
    class Config
    {
    private:
        static Config* instance;
        nlohmann::json data;

        Config() = default;
        void readJson();
    public:
        static Config* get();
        [[nodiscard]] const nlohmann::json &getData() const;
    private:
        std::vector<std::string> servers;
    public:
        std::vector<std::string> getServers() { return this->servers; };
    };
}

#endif //SUBSCALE_CONFIG_H