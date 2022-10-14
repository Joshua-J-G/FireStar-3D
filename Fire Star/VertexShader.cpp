#include "VertexShader.h"
#include "RenderSystem.h"
#include <iostream> 
#include <exception>
using namespace std;
VertexShader::VertexShader(const void* shader_byte_code, size_t byte_code_size,RenderSystem* system): m_system(system)
{
	if (!SUCCEEDED(m_system->m_d3d_device->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, &m_vs)))
	{
		cout << "FAILED: Vertex Shader has failed to initalise (vertex) err09" << endl;
		throw std::exception("FAILED: Vertex Shader has failed to initalise (vertex) err09");
	}
	else
	{
		cout << "Vertex Shader sucsefuly launched" << endl;
	}
}



VertexShader::~VertexShader()
{
	m_vs->Release();
	cout << m_vs << endl;
}


