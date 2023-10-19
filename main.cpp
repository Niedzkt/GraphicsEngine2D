#include <iostream>
#include "Engine.h"

int main()
{
    Engine gameEngine(800, 600, "MY 2D GameEngine");
    gameEngine.run();

    return 0;
}