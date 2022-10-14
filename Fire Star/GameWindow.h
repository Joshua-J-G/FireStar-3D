#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "swapchain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "InputListener.h"
#include "Matrix4x4.h"

class GameWindow: public Window,public InputListener
{
public:
	GameWindow();

	void Update();

	~GameWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void OnKillFocus() override;

	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& mouse_pos) override;


	virtual void OnLeftMouseDown(const Point& mouse_pos) override;
	virtual void OnLeftMouseUp(const Point& mouse_pos) override;

	virtual void OnRightMouseDown(const Point& mouse_pos) override;
	virtual void OnRightMouseUp(const Point& mouse_pos) override;
private: 
	SwapCahinPtr m_swap_chain;
	VertexBufferPtr m_vb;
	VertexShaderPtr m_vs;
	PixelShaderPtr m_ps;
	ConstantBufferPtr m_cb;
	IndexBufferPtr m_ib;
	TexturePtr m_wood_tex;
private:
	float m_old_delta;
	float m_new_delta;
	float m_delta_time;


	float m_delta_pos;
	float m_delta_scale;
	float m_delta_rot;
	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;

	float m_scale_cube = 1;
	float m_forward = 0.0f;
	float m_Right = 0.0f;
	Matrix4x4 m_world_cam;
};

