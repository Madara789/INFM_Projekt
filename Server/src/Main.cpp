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
private:
    std::string addr;
public:
    SubscaleRoutesImpl(std::string addr) : addr(addr) {};
    Status RemoteSubscale(ServerContext *context, const RemoteSubscaleRequest *request, RemoteSubspaceResponse *response) override
    {
        std::cout << "server address: " << addr << std::endl;
        auto result = Remote::calculateRemote({std::begin(request->labels()), std::end(request->labels())}, request->minsignature(), request->maxsignature());
        auto table = std::get<0>(result);
        auto numberOfEntries = std::get<1>(result);
        
        // auto tablesize = 0;

    /* auto ids = result->getIdsVec(i)
    auto dimensions = result->getDimensionsVec(i) */
    // https: // prod.liveshare.vsengsaas.visualstudio.com/join?25C872B39986B581DBDCE84D1555A57400B9

        // For u to number entries

         /* auto ids = result->getIdsVec(i)
            auto dimensions = result->getDimensionsVec(i) */

            // if ids.size == 0 || dimensions.size == 0 
                // continue

            // Create entry with ids and dimension 
            // tablesize ++
        
        // set table size 

        // auto idsSize = result->getIdsSize();
        // auto dimensionSize = table->getDimensionsSize()

        // Setze werte in response 


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
        response->set_dimensionssize(table->getDimensionsSize());

        response->set_tablesize(std::get<1>(result));

        return Status::OK;
    }
};

int main(int argc, char* argv[])
{
    std::string port;
    if (argc > 1)
        port.assign(argv[argc - 1]);
    else
        port.assign("2510");

    std::string server_address = "localhost:";
    server_address.append(port);
    SubscaleRoutesImpl service(server_address);

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server{builder.BuildAndStart()};

    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
    return 0;
}
