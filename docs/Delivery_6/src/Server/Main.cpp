#include <grpc++/grpc++.h>
#include <iostream>
#include "SubscaleRoutesImpl.h"

using grpc::ServerBuilder;

int main(int argc, char* argv[])
{
    std::string port;
    if (argc > 1)
        port.assign(argv[argc - 1]);
    else
        port.assign("2510");

    std::string server_address = "localhost:";
    server_address.append(port);
    Server::SubscaleRoutesImpl service(server_address);

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<grpc::Server> server{builder.BuildAndStart()};

    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
    return 0;
}
