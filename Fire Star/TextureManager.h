#pragma once
#include "ResorceManager.h"

class TextureManager : public ResorceManager
{
public:
	TextureManager();
	~TextureManager();
	TexturePtr createTextureFromFile(const wchar_t* file_path);
protected:
	virtual Resource* createRespirceFromFileConcrete(const wchar_t* file_path);
};

