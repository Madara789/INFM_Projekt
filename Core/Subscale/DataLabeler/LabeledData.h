#ifndef SUBSCALE_LABELEDDATA_H
#define SUBSCALE_LABELEDDATA_H

#include <cstdint>

class LabeledData
{
private:
    uint64_t minSignature;
    uint64_t maxSignature;
    uint64_t* labels;

public:
    LabeledData(const uint64_t &minSignature, const uint64_t &maxSignature, uint64_t *labels);
    [[nodiscard]] uint64_t getMinSignature() const;
    [[nodiscard]] uint64_t getMaxSignature() const;
    [[nodiscard]] uint64_t *getLabels() const;
    ~LabeledData() { delete labels; }
};


#endif //SUBSCALE_LABELEDDATA_H
