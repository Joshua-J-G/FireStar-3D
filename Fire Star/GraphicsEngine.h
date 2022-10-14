#pragma once
#include <d3d11.h>
#include "RenderSystem.h"
#include"PreRequisites.h"
#include"TextureManager.h"


class GraphicsEngine
{
private:
	GraphicsEngine();
	//Inisiliase engine (i have no idea what im doing)
	~GraphicsEngine();

public:
	RenderSystem* getrendersystem();
	TextureManager* getTextureManager();

	
public:
	static GraphicsEngine* get();
	static void create();
	static void release();
private:
	RenderSystem* m_render_system = nullptr;
	TextureManager* m_tex_manager = nullptr;
	static GraphicsEngine* m_engine;
};

