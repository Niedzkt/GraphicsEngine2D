#include "Engine.h"

// Funkcja `main` jest punktem wejściowym programu. Tworzy obiekt `engine` klasy `Engine`
// i wykonuje niezbędne kroki inicjalizacji. Jeśli inicjalizacja się nie powiedzie,
// wyświetla błąd i kończy program z kodem błędu -1. W przeciwnym razie, wchodzi do głównej pętli gry.
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