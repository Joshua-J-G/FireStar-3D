#include "TextureManager.h"
#include "Texture.h"
#include<iostream>
#include <string>  


TextureManager::TextureManager(): ResorceManager()
{
}

TextureManager::~TextureManager()
{
}

TexturePtr TextureManager::createTextureFromFile(const wchar_t* file_path)
{
	return std::static_pointer_cast<Texture>(createResourceFromFile(file_path));
}

Resource* TextureManager::createRespirceFromFileConcrete(const wchar_t* file_path)
{

	Texture* tex = nullptr;
	try
	{
		tex = new Texture(file_path);
	}
	catch (...) {
		std::cout << "failed to load image at " << file_path << std::endl;
	}
	return tex;
}
