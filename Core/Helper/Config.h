#ifndef SUBSCALE_CONFIGHELPER_H
#define SUBSCALE_CONFIGHELPER_H

#include <nlohmann/json.hpp>

class Config
{
private:
    static Config* instance;
    nlohmann::json data;
    Config() = default;
public:
    static Config* get();
    [[nodiscard]] const nlohmann::json &getData() const;

    uint32_t getMinPoints();
    uint64_t getMinLabel();
    uint64_t getMaxLabel();
    double getEpsilon();
    uint32_t getSplittingFactor();
};


#endif //SUBSCALE_CONFIGHELPER_H
