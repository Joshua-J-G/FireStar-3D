#include "GameWindow.h"
#include <Windows.h>
#include"Vector3D.h"
#include"Matrix4x4.h"
#include "InputSystem.h"
#include <iostream>
#include <fstream>
using namespace std;
struct vertex
{
	Vector3D position;
	Vector2D texcoord;
};


__declspec(align(16))
struct Constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_projection;
	unsigned int m_time;
};


GameWindow::GameWindow()
{
}

void GameWindow::Update()
{
	Constant cc;
	cc.m_time = ::GetTickCount();

	m_delta_pos += m_delta_time / 10.0f;
	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;
	
	Matrix4x4 temp;



	
	m_delta_scale += m_delta_time / 0.55f;

	//cc.m_world.setScale(Vector3D::lerp(Vector3D(0.8, 0.8, 0), Vector3D(2, 2, 0), (sin(m_delta_scale)*1.0f)/2.0f));

	//temp.setTranslation(Vector3D::lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f, 1.5f, 0), m_delta_pos));


	//cc.m_world *= temp;
	/*
	cc.m_world.setScale(Vector3D(m_scale_cube, m_scale_cube, m_scale_cube));

	temp.setIdentity();
	temp.setRotationZ(0.0f);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationX(m_rot_x);
	cc.m_world *= temp; */

	cc.m_world.setIdentity();

	Matrix4x4 world_cam;
	world_cam.setIdentity();
	temp.setIdentity();
	temp.setRotationX(m_rot_x);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	world_cam *= temp;

	Vector3D new_pos = m_world_cam.getTranslation() + world_cam.getZDirection() * (m_forward * 0.1f);

	new_pos = new_pos + world_cam.getXDirection() * (m_Right * 0.1f);


	world_cam.setTranslation(new_pos);
	m_world_cam = world_cam;
	world_cam.inverse();



	cc.m_view = world_cam;
	/*cc.m_projection.setOrthoLH
	(
		(this->getClientWindowRect().right - this->getClientWindowRect().left) / 300.0f,
		(this->getClientWindowRect().bottom - this->getClientWindowRect().top) / 300.0f,
		-4.0f,
		4.0f
	);*/
	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);

	cc.m_projection.SetPerspectiveFovLH(1.56f, ((float)width / (float)height), 0.1f, 100.0f);

	m_cb->update(GraphicsEngine::get()->getrendersystem()->getImmediateDeviceContext(), &cc);





}

GameWindow::~GameWindow()
{
}

void GameWindow::onCreate()
{
	Window::onCreate();

	InputSystem::get()->addListener(this);
	InputSystem::get()->ShowCursor(false);
	

	m_wood_tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\wood.jpg");

	cout << TEXT("..\\Assets\\Textures\\wood.jpg") << endl;


	RECT rc = this->getClientWindowRect();

	m_swap_chain = GraphicsEngine::get()->getrendersystem()->createSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);




	m_world_cam.setTranslation(Vector3D(0, 0, -2));

	Vector3D position_list[] =
	{
		{ Vector3D(-0.5f,-0.5f,-0.5f)},
		{ Vector3D(-0.5f,0.5f,-0.5f) },
		{ Vector3D(0.5f,0.5f,-0.5f) },
		{ Vector3D(0.5f,-0.5f,-0.5f)},

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f) },
		{ Vector3D(0.5f,0.5f,0.5f) },
		{ Vector3D(-0.5f,0.5f,0.5f)},
		{ Vector3D(-0.5f,-0.5f,0.5f) }
	};

	Vector2D texcoord_list[] =
	{
		{ Vector2D(0.0f,0.0f) },
		{ Vector2D(0.0f,1.0f) },
		{ Vector2D(1.0f,0.0f) },
		{ Vector2D(1.0f,1.0f) }
	};



	vertex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{ position_list[0],texcoord_list[1] },
		{ position_list[1],texcoord_list[0] },
		{ position_list[2],texcoord_list[2] },
		{ position_list[3],texcoord_list[3] },


		{ position_list[4],texcoord_list[1] },
		{ position_list[5],texcoord_list[0] },
		{ position_list[6],texcoord_list[2] },
		{ position_list[7],texcoord_list[3] },


		{ position_list[1],texcoord_list[1] },
		{ position_list[6],texcoord_list[0] },
		{ position_list[5],texcoord_list[2] },
		{ position_list[2],texcoord_list[3] },

		{ position_list[7],texcoord_list[1] },
		{ position_list[0],texcoord_list[0] },
		{ position_list[3],texcoord_list[2] },
		{ position_list[4],texcoord_list[3] },

		{ position_list[3],texcoord_list[1] },
		{ position_list[2],texcoord_list[0] },
		{ position_list[5],texcoord_list[2] },
		{ position_list[4],texcoord_list[3] },

		{ position_list[7],texcoord_list[1] },
		{ position_list[6],texcoord_list[0] },
		{ position_list[1],texcoord_list[2] },
		{ position_list[0],texcoord_list[3] }


	};


	UINT size_list = ARRAYSIZE(vertex_list);

	unsigned int index_list[] =
	{
		//FRONT SIDE
			0,1,2,  //FIRST TRIANGLE
			2,3,0,  //SECOND TRIANGLE
			//BACK SIDE
			4,5,6,
			6,7,4,
			//TOP SIDE
			8,9,10,
			10,11,8,
			//BOTTOM SIDE
			12,13,14,
			14,15,12,
			//RIGHT SIDE
			16,17,18,
			18,19,16,
			//LEFT SIDE
			20,21,22,
			22,23,20
	};

	UINT size_index_list = ARRAYSIZE(index_list);
	m_ib = GraphicsEngine::get()->getrendersystem()->createIndexBuffer(index_list, size_index_list);



	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->getrendersystem()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->getrendersystem()->createVertexShader(shader_byte_code, size_shader);
	m_vb = GraphicsEngine::get()->getrendersystem()->createVertexBuffer(vertex_list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->getrendersystem()->releaseCompiledShader();


	GraphicsEngine::get()->getrendersystem()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->getrendersystem()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->getrendersystem()->releaseCompiledShader();

	Constant cc;
	cc.m_time = 0;

	m_cb = GraphicsEngine::get()->getrendersystem()->createConstantBuffer(&cc, sizeof(Constant));






}
//RenderPipeline 
void GameWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::get()->update();

	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getrendersystem()->getImmediateDeviceContext()->clearRenderTargetColour(this->m_swap_chain,
		1, 0, 0, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getrendersystem()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);


	Update();


	GraphicsEngine::get()->getrendersystem()->getImmediateDeviceContext()->setContantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getrendersystem()->getImmediateDeviceContext()->setContantBuffer(m_ps, m_cb);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->getrendersystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getrendersystem()->getImmediateDeviceContext()->setPixelShader(m_ps);


		GraphicsEngine::get()->getrendersystem()->getImmediateDeviceContext()->setTexture(m_ps, m_wood_tex);
	
	

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getrendersystem()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	//SET THE INDICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getrendersystem()->getImmediateDeviceContext()->setIndexBuffer(m_ib);


	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::get()->getrendersystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
	m_swap_chain->present(true);

	m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount();

	m_delta_time = (m_old_delta) ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;

}

void GameWindow::onDestroy()
{
	Window::onDestroy();

}

void GameWindow::onFocus()
{
	InputSystem::get()->addListener(this);
}

void GameWindow::OnKillFocus()
{
	InputSystem::get()->RemoveListener(this);
}


void GameWindow::onKeyDown(int key)
{
	if (key == 'W')
	{
		//m_rot_x += 3.14f * m_delta_time;
		m_forward = 1.0f;
	}
	else if (key == 'S')
	{
		//m_rot_x -= 3.14f * m_delta_time;
		m_forward = -1.0f;
	}
	else if (key == 'A')
	{
		//m_rot_y += 3.14f * m_delta_time;
		m_Right = -1.0f;
	}
	else if (key == 'D')
	{
		//m_rot_y -= 3.14f * m_delta_time;
		m_Right = 1.0f;
	}
}

void GameWindow::onKeyUp(int key)
{
	m_forward = 0.0f;
	m_Right = 0.0f;
}

void GameWindow::onMouseMove(const Point& mouse_pos)
{
	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);


	m_rot_x += (mouse_pos.m_y - (height / 2.0f)) *m_delta_time * 0.5f;
	m_rot_y += (mouse_pos.m_x - (width/2.0f))* m_delta_time * 0.5f;

	InputSystem::get()->setCursorPosition(Point(width / 2.0f, height / 2.0f));
}

void GameWindow::OnLeftMouseDown(const Point& mouse_pos)
{
	m_scale_cube = 0.5f;

}

void GameWindow::OnLeftMouseUp(const Point& mouse_pos)
{
	m_scale_cube = 1.0f;
}

void GameWindow::OnRightMouseDown(const Point& mouse_pos)
{
	m_scale_cube = 2.0f;
}

void GameWindow::OnRightMouseUp(const Point& mouse_pos)
{
	m_scale_cube = 1.0f;
}
