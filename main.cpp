#include "Engine.h"

int main()
{
    Engine engine;

	if (!engine.initialize())
	{
		std::cout << "ERROR::CANT INITIALIZE GAME ENGINE!" << std::endl;
		return -1;
	}

	engine.mainLoop();

    return 0;
}