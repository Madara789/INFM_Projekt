#include "SubscaleRoutesImpl.h"
#include <Remote/Remote.h>

using subscale::Entry;

namespace Server
{
    Status SubscaleRoutesImpl::RemoteSubscale(ServerContext *context, const RemoteSubscaleRequest *request, RemoteSubspaceResponse *response)
    {
        std::cout << "server address: " << addr << std::endl;
        auto result = Remote::calculateRemote({std::begin(request->labels()), std::end(request->labels())}, request->minsignature(), request->maxsignature());
        auto table = std::get<0>(result);
        auto numberOfEntries = std::get<1>(result);
        auto tableSize = 0;

        for (auto i = 0; i < numberOfEntries; i++) 
        {
            auto ids = table->getIdsVec(i);
            auto dimensions = table->getDimensionsVec(i);

            if (ids.size() == 0 || dimensions.size() == 0)
                continue;

            Entry* entry = response->add_entries();
            *entry->mutable_dimensions() = {dimensions.begin(), dimensions.end()};
            *entry->mutable_ids() = {ids.begin(), ids.end()};

            tableSize++;
        }
        response->set_idssize(table->getIdsSize());
        response->set_dimensionssize(table->getDimensionsSize());
        response->set_tablesize(tableSize);

        return Status::OK;
    }
}