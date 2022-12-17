#pragma once

#include <memory>
#include <grpc++/grpc++.h>
#include <generated/subscale.pb.h>
#include <generated/subscale.grpc.pb.h>
#include <Subscale/Subscale.h>
#include <tuple>

using grpc::Channel;
using subscale::RemoteSubspaceResponse;

namespace Client {
    class Client
    {
    public:
        Client(std::shared_ptr<Channel> channel): _stub{subscale::SubscaleRoutes::NewStub(channel)} {}

        RemoteSubspaceResponse remoteCalculation(std::vector<unsigned long long> lables, unsigned long long min, unsigned long long max);
    private:
        std::unique_ptr<subscale::SubscaleRoutes::Stub> _stub;
    };
}
