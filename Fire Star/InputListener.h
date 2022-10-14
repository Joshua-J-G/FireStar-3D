#pragma once
#include "Point.h"

class InputListener
{
public:
	InputListener()
	{

	}
	~InputListener()
	{
	}

	//Keybaord Callback Functions

	virtual void onKeyDown(int key) = 0;
	virtual void onKeyUp(int key) = 0;

	//Mouse Callback Functions
	virtual void onMouseMove(const Point& mouse_pos) = 0;


	virtual void OnLeftMouseDown(const Point& mouse_pos) = 0;
	virtual void OnLeftMouseUp(const Point& mouse_pos) = 0;

	virtual void OnRightMouseDown(const Point& mouse_pos) = 0;
	virtual void OnRightMouseUp(const Point& mouse_pos) = 0;

};