#include "SequentialDenseUnitCombiner.h"
#include <fstream>
#include <sstream>

DenseUnits *SequentialDenseUnitCombiner::getDenseUnits(uint32_t slices)
{
    auto denseUnits = new DenseUnits();
    for (uint32_t i = 0; i <= slices; i++)
    {
        std::stringstream s;
        s << "temp/slice-" << i << ".csv";
        auto* slice = new std::ifstream(s.str());

        std::string row;
        while (std::getline(*slice, row))
        {
            std::stringstream ss(row);
            uint64_t signature = 0;
            ss >> signature;
            ss.ignore();
            uint32_t dimension = 0;
            ss >> dimension;
            ss.ignore(3);

            std::string token;
            Points points;
            while (std::getline(ss, token, '['))
            {
                std::stringstream values(token);
                uint64_t pointSignature = 0;
                values >> pointSignature;
                values.ignore();
                double value = 0.0;
                values >> value;

                points.push_back(new Point(value, pointSignature));
            }

            if (points.size() > 1)
                denseUnits->push_back(DenseUnit(points, signature, dimension));
        }
    }
    return denseUnits;
}
