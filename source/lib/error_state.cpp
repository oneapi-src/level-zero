#include "error_state.h"

namespace error_state
{
    std::unordered_map<std::thread::id, std::string> errorDescs;
    std::mutex errorDescsMutex;

    void setErrorDesc(const std::string &desc)
    {
        auto threadId = std::this_thread::get_id();
        std::lock_guard<std::mutex> errorDescsLock(errorDescsMutex);
        if (errorDescs.find(threadId) == errorDescs.end())
        {
            errorDescs[threadId] = desc;
        }
        else
        {
            errorDescs[threadId].clear();
            errorDescs[threadId] = desc;
        }
    }

    void getErrorDesc(const char **ppString)
    {
        auto threadId = std::this_thread::get_id();
        std::lock_guard<std::mutex> errorDescsLock(errorDescsMutex);
        if (errorDescs.find(threadId) == errorDescs.end())
        {
            errorDescs[threadId] = std::string();
        }
        if(ppString != nullptr) {
            *ppString = errorDescs[threadId].c_str();
        }
    }
}