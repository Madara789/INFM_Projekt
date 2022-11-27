#include <generated/subscale.pb.h>
#include <generated/subscale.grpc.pb.h>
#include <grpc++/grpc++.h>
#include <iostream>
#include <Remote/Remote.h>

using grpc::Status;
using grpc::Server;
using grpc::ServerContext;
using grpc::ServerBuilder;
using grpc::ServerContext;
using subscale::RemoteSubscaleRequest;
using subscale::RemoteSubspaceResponse;
using subscale::SubscaleRoutes;

class SubscaleRoutesImpl final : public SubscaleRoutes::Service {
public:
    Status RemoteSubscale(ServerContext *context, const RemoteSubscaleRequest *request, RemoteSubspaceResponse *response) override
    {
        auto result = Remote::calculateRemote({std::begin(request->labels()), std::end(request->labels())}, request->minsignature(), request->maxsignature());
        auto table = std::get<0>(result);
        response->set_id(std::get<1>(result));
        for (int i = 0; i < table->getIdsSize(); ++i)
        {
            response->add_ids(table->getIds()[i]);
        }
        response->set_idssize(table->getIdsSize());

        for (int i = 0; i < table->getDimensionsSize(); ++i)
        {
            response->add_ids(table->getDimensions()[i]);
        }
        response->set_tablesize(table->getDimensionsSize());

        response->set_tablesize(table->getTableSize());

        return Status::OK;
    }
};

void RunServer() {
    std::string server_address{"localhost:2510"};
    SubscaleRoutesImpl service;

    // Build server
    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server{builder.BuildAndStart()};

    // Run server
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}

int main(int argc, char* argv[])
{
    RunServer();
    return 0;
}
