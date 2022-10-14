#pragma once
#include <unordered_map>
#include<string>
#include "PreRequisites.h"
#include "Resource.h"
class ResorceManager
{
public:
	ResorceManager();
	virtual ~ResorceManager();
	ResourcePtr createResourceFromFile(const wchar_t* file_path);
protected:
	virtual Resource* createRespirceFromFileConcrete(const wchar_t* file_path) = 0;
private:
	std::unordered_map<std::wstring, ResourcePtr> m_map_resources;
};

