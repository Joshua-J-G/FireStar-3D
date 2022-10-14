#include "swapchain.h"
#include "RenderSystem.h"
#include <iostream> 
#include <exception>
using namespace std;
swapchain::swapchain(HWND hwnd, UINT width, UINT height, RenderSystem* system) : m_system(system)
{
	ID3D11Device* device = m_system->m_d3d_device;

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;
	//still swap chain
	HRESULT hr = m_system->m_dxgi_factory->CreateSwapChain(device, &desc, &m_swap_chain);

	if (FAILED(hr))
	{
		cout << "FAILED: SwapChain has failed (Memory issues found) err06" << endl;
		throw std::exception("FAILED: SwapChain has failed (Memory issues found) err06");
	}

	if (SUCCEEDED(hr))
	{
		cout << "SwapChain Sucsefuly launched" << endl;
		
	}

	ID3D11Texture2D* buffer = NULL;
	hr = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

	if (FAILED(hr))
	{
		cout << "FAILED: SwapChain has failed (Buffer) err07" << endl;
		throw std::exception("FAILED: SwapChain has failed (Buffer) err07");
	}

	if (SUCCEEDED(hr))
	{
		cout << "SwapChain Succeeded to launch" << endl;

	}

	hr = device->CreateRenderTargetView(buffer, NULL, &m_rendtargview);
	buffer->Release();

	if (FAILED(hr))
	{
		cout << "FAILED: Could not create Render target err08" << endl;
		throw std::exception("FAILED: Could not create Render target err08");
	}
	if (SUCCEEDED(hr))
	{
		cout << "Rendered target" << endl;

	}

}


bool swapchain::present(bool vsync)
{
	m_swap_chain->Present(vsync, NULL);


	return true;
}



swapchain::~swapchain()
{
	m_rendtargview->Release();
	m_swap_chain->Release();
}
