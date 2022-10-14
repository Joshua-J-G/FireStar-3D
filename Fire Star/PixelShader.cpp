#include "PixelShader.h"
#include "RenderSystem.h"
#include <iostream> 
using namespace std;
#include <exception>
PixelShader::PixelShader(const void* shader_byte_code, size_t byte_code_size,RenderSystem* system) : m_system(system)
{
	if (!SUCCEEDED(m_system->m_d3d_device->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, &m_ps)))
	{
		cout << "FAILED: Pixel Shader has failed to initialize (Pixel) err05" << endl;
		throw std::exception("FAILED: Pixel Shader has failed to initialize (Pixel) err05");
		
	}
	else
	{
		cout << "Pixel Shader sucsefuly launched" << endl;
	}

}


PixelShader::~PixelShader()
{
	m_ps->Release();
	cout << m_ps << endl;
}

