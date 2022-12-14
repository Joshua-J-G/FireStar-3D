#pragma once
#include <d3d11.h>

#include "PreRequisites.h"
class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context, RenderSystem* system);
	void clearRenderTargetColour(const SwapCahinPtr& swap_chain, float red, float green, float blue, float alpha);
	void setVertexBuffer(const VertexBufferPtr& vertex_buffer);
	void setIndexBuffer(const IndexBufferPtr& index_buffer);


	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);
	void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);

	void setViewportSize(UINT width, UINT height);

	void setVertexShader(const VertexShaderPtr& vertex_shader);
	void setPixelShader(const PixelShaderPtr& pixel_shader);

	void setTexture(const VertexShaderPtr& vertex_shader, const TexturePtr& texture);
	void setTexture(const PixelShaderPtr& pixel_shader, const TexturePtr& texture);

	void setContantBuffer(const VertexShaderPtr& vertex_shader, const ConstantBufferPtr& buffer);
	void setContantBuffer(const PixelShaderPtr& pixel_shader, const ConstantBufferPtr& buffer);

	~DeviceContext();
private:
	ID3D11DeviceContext* m_device_context;
	RenderSystem* m_system = nullptr;
private:
	friend class ConstantBuffer;

};