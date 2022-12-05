#include "SubscaleRoutesImpl.h"
#include <Remote/Remote.h>

namespace Server
{
    Status SubscaleRoutesImpl::RemoteSubscale(ServerContext *context, const RemoteSubscaleRequest *request, RemoteSubspaceResponse *response)
    {
        std::cout << "server address: " << addr << std::endl;
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
        response->set_dimensionssize(table->getDimensionsSize());

        response->set_tablesize(std::get<1>(result));

        return Status::OK;
    }
}