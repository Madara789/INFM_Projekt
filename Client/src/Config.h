#ifndef SUBSCALE_CONFIG_H
#define SUBSCALE_CONFIG_H

#include <nlohmann/json.hpp>

namespace Client {
    class Config
    {
    private:
        static Config* instance;
        nlohmann::json data;
        Config() = default;
    public:
        static Config* get();
        [[nodiscard]] const nlohmann::json &getData() const;
    };
}

#endif //SUBSCALE_CONFIG_H