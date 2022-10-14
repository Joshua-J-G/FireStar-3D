#pragma once
#include <memory>

class swapchain;
class DeviceContext;
class ConstantBuffer;
class VertexBuffer;
class IndexBuffer;
class VertexShader;
class PixelShader;
class RenderSystem;
class GraphicsEngine;
class Resource;
class ResourceManger;
class Texture;
class TextureManager;

typedef std::shared_ptr<swapchain> SwapCahinPtr;
typedef std::shared_ptr<DeviceContext> DeviceContextPtr;
typedef std::shared_ptr<ConstantBuffer> ConstantBufferPtr;
typedef std::shared_ptr<VertexBuffer> VertexBufferPtr;
typedef std::shared_ptr<IndexBuffer> IndexBufferPtr;
typedef std::shared_ptr<VertexShader> VertexShaderPtr;
typedef std::shared_ptr<PixelShader> PixelShaderPtr;
typedef std::shared_ptr<RenderSystem> RenderSystemPtr;
typedef std::shared_ptr<GraphicsEngine> GraphicsEnginePtr;
typedef std::shared_ptr<Resource>ResourcePtr;
typedef std::shared_ptr<Texture>TexturePtr;

