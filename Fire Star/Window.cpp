#include "Window.h"
#include <exception>
#include <iostream>
//Window* window = nullptr;
using namespace std;

LRESULT CALLBACK WindProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		// see if window found 
		Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
		break;
	}

	case WM_SETFOCUS:
	{
		// Change Focus
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		if(window) window->onFocus();
		break;
	}

	case WM_KILLFOCUS:
	{
		// Lost Focus
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->OnKillFocus();
		break;
	}


	case WM_DESTROY:
	{
		// you destroyed a window 
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->onDestroy();
		::PostQuitMessage(0);
		break;
	}


	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}


	return NULL;
}


Window::Window()
{
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = TEXT("MyWindowClass");
	wc.lpszMenuName = TEXT("");
	wc.style = NULL;
	wc.lpfnWndProc = &WindProc;


	if (!::RegisterClassEx(&wc))
	{
		throw std::exception("Window not created successfully");
	}


	/*if (!window)
		window = this;*/


	m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, TEXT("MyWindowClass"), TEXT("FireStar Engine V0.1 Pre-Alpha"),
			WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
			NULL, NULL, NULL, NULL);

	//if the creation fail return false
	if (!m_hwnd)
		throw std::exception("Window not created successfully");


	//show up the window
	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);




	//set this flag to true to indicate that the window is initialized and running
	m_is_run = true;
	cout << "create window" << endl;
}



bool Window::broadcast()
{
	MSG msg;

	if (!this->m_is_init)
	{
		SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);
		this->onCreate();
		this->m_is_init = true;
	}

	this->onUpdate();

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Sleep(1);

	return true;
}



bool Window::isRun()
{
	if (m_is_run)
		broadcast();
	return m_is_run;
}
RECT Window::getClientWindowRect()
{
	RECT rc;
	::GetClientRect(this->m_hwnd, &rc);
	return rc;
}



void Window::onCreate()
{
}

void Window::onUpdate()
{
}
void Window::onDestroy()
{
	m_is_run = false;
}

void Window::onFocus()
{
}

void Window::OnKillFocus()
{
}

Window::~Window()
{
	

}
