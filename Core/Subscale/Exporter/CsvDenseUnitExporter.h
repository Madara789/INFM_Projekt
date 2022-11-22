#ifndef SUBSCALE_CSVDENSEUNITEXPORTER_H
#define SUBSCALE_CSVDENSEUNITEXPORTER_H

#include "CsvExporter.h"
#include "../DenseUnitGenerator/DenseUnit.h"

class CsvDenseUnitExporter: public CsvExporter
{
private:
    DenseUnits& denseUnits;
public:
    CsvDenseUnitExporter(std::string, DenseUnits&);
    void doExport() override;
};


#endif //SUBSCALE_CSVDENSEUNITEXPORTER_H
