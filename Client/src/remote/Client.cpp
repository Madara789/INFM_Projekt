#include "Client.h"

using grpc::ClientContext;
using grpc::Status;
using subscale::RemoteSubscaleRequest;
using subscale::RemoteSubspaceResponse;

namespace Client 
{
    std::tuple<LocalSubspaceTable*, unsigned int> Client::remoteCalculation(std::vector<unsigned long long> lables, unsigned long long min, unsigned long long max)
    {
        RemoteSubscaleRequest request;
        request.set_minsignature(min);
        request.set_maxsignature(max);

        for (auto label : lables)
        {
            request.add_labels(label);
        }

        RemoteSubspaceResponse response;
        ClientContext context;
        Status status;
        status = _stub->RemoteSubscale(&context, request, &response);

        if (status.ok())
        {
            // TODO failed danach irgendwo
            std::cout << "in OK" << std::endl;
            LocalSubspaceTable* table = new LocalSubspaceTable(response.idssize(), response.dimensionssize(), response.tablesize());
            for (int i = 0; i < response.idssize(); ++i)
            {
                uint32_t id = response.ids(i);
                table->insertIds(&id, i);
            }
            std::cout << "after ids insert" << std::endl;

            for (int i = 0; i < response.dimensionssize(); ++i)
            {
                uint32_t dimension = response.dimensions(i);
                table->insertDimensions(&dimension, i);
            }
            std::cout << "after dimension insert" << std::endl;

            std::cout << "OK" << std::endl;
            return std::make_tuple(table, response.id());
        }

        std::cout << "Error code: " <<status.error_code() << std::endl;
        std::cout << "Error Details: " << status.error_details() << std::endl;
        std::cout << "Error Message: " << status.error_message() << std::endl;
        throw std::runtime_error("GRPC Request Failed");
    }
}