#include "Client.h"

using grpc::ClientContext;
using grpc::Status;
using subscale::RemoteSubscaleRequest;

namespace Client 
{
    RemoteSubspaceResponse Client::remoteCalculation(std::vector<unsigned long long> lables, unsigned long long min, unsigned long long max)
    {
        auto* request = new RemoteSubscaleRequest();
        request->set_minsignature(min);
        request->set_maxsignature(max);
        *request->mutable_labels() = {lables.begin(), lables.end()};

        RemoteSubspaceResponse response;
        ClientContext context;
        Status status;
        status = _stub->RemoteSubscale(&context, *request, &response);
        delete request;

        if (status.ok())
            return response;

        std::cout << "Error code: " <<status.error_code() << std::endl;
        std::cout << "Error Details: " << status.error_details() << std::endl;
        std::cout << "Error Message: " << status.error_message() << std::endl;
        throw std::runtime_error("GRPC Request Failed");
    }
}