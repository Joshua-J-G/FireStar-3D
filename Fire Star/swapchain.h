#pragma once
#include <d3d11.h>
#include "PreRequisites.h"
class swapchain
{
public:
	swapchain(HWND hwnd, UINT width, UINT height,RenderSystem* system);
	// what do you mean the chains a swaping they shouldent be doing that 

	// no dont let go 

	bool present(bool vsync);




	~swapchain();

private:
	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* m_rendtargview;
	ID3D11DepthStencilView* m_dsv;
	RenderSystem* m_system = nullptr;
private:
	friend class DeviceContext;

};

