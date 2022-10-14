#include "ResorceManager.h"
#include <iostream>
#include <filesystem>
#include <fstream>

ResorceManager::ResorceManager()
{
}

ResorceManager::~ResorceManager()
{
}

ResourcePtr ResorceManager::createResourceFromFile(const wchar_t* file_path)
{
   
    std::wstring full_path = std::filesystem::absolute(file_path);

    auto it = m_map_resources.find(full_path);

    if (it != m_map_resources.end())
        return it->second;

    Resource* raw_res = this->createRespirceFromFileConcrete(full_path.c_str());

    if (raw_res)
    {
        ResourcePtr res(raw_res);
        m_map_resources[full_path] = res;
        return res;
    }

    return nullptr;
}
