#include "GameWindow.h"
#include "InputSystem.h"


int main()
{
	
	try
	{
		GraphicsEngine::create();
		InputSystem::create();
	}
	catch (...) { return -1; }

	{
		try
		{
			GameWindow game;
			while (game.isRun());
		}
		catch (...) {
			InputSystem::release();
			GraphicsEngine::release();
			return -2;
		}
	}

	InputSystem::release();
	GraphicsEngine::release();

	return 0;
}