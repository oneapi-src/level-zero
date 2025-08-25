#pragma once
#include <unordered_map>
#include <string>
#include <thread>
#include <mutex>

namespace error_state
{
    extern std::unordered_map<std::thread::id, std::string> errorDescs;
    extern std::mutex errorDescsMutex;

    void setErrorDesc(const std::string &desc);

    void getErrorDesc(const char **ppString);
}