#include <iostream>
#include <SDL.h>

#include "Engine.h"
#include "Color.h"

// #DG: add game object class next

int main(int argc, char** argv)
{
	Engine engine;
	int errorCode = engine.Init();

	if (errorCode == 0)
	{
		engine.Update();

		// Teardown
		engine.Teardown();
	}

	return errorCode;
}


