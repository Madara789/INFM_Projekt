#pragma once

#include <generated/subscale.pb.h>
#include <generated/subscale.grpc.pb.h>

using grpc::Status;
using grpc::ServerContext;
using subscale::RemoteSubscaleRequest;
using subscale::RemoteSubspaceResponse;
using subscale::SubscaleRoutes;

namespace Server
{
    class SubscaleRoutesImpl final : public SubscaleRoutes::Service 
    {
    private:
        std::string addr;
    public:
        SubscaleRoutesImpl(std::string addr) : addr(addr) {};
        Status RemoteSubscale(ServerContext *context, const RemoteSubscaleRequest *request, RemoteSubspaceResponse *response) override;
    };
}
