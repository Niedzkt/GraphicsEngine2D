#include "Engine.h"

void Engine::handleEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			window.close();
		}

		if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
		{
			handleKeyboardEvents(event);
		}
		if (event.type == sf::Event::MouseButtonPressed ||
			event.type == sf::Event::MouseButtonReleased ||
			event.type == sf::Event::MouseMoved)
		{
			handleMouseEvents(event);
		}
	}
}

void Engine::update()
{
	/*TODO*/
}

void Engine::draw()
{
	window.clear(backgroundColor);

	window.display();
}

void Engine::logError(const std::string& message)
{
	std::ofstream file("error_log.txt", std::ios::app);
	if (file.is_open())
	{
		file << message << "\n";
		file.close();
	}
	else
	{
		std::cerr << "ERROR::CANT OPEN error_log.txt!" << std::endl;
	}
}

void Engine::handleKeyboardEvents(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape)
		{
			window.close();
		}
	}
}

void Engine::handleMouseEvents(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			std::cout << "Left mouse button pressed" << std::endl;
		}
		if (event.mouseButton.button == sf::Mouse::Right)
		{
			std::cout << "Right mouse button pressed" << std::endl;
		}
	}

	if (event.type == sf::Event::MouseMoved)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	}
}

Engine::Engine(unsigned int width, unsigned height, const std::string& title)
	:window(sf::VideoMode(width, height), title), deltaTime(0.0f), backgroundColor(sf::Color::Green)
{
}

bool Engine::initialize()
{
	try
	{
		window.setFramerateLimit(60); //default frame limit
		window.setKeyRepeatEnabled(true); //default keyboard and mouse access
		return true;
	}
	catch (const std::exception& e)
	{
		logError(e.what());
		return false;
	}
}

void Engine::setFullscreen(bool fullscreen)
{
	if (isFullScreen != fullscreen)
	{
		isFullScreen = fullscreen;
		if (isFullScreen)
		{
			window.create(sf::VideoMode::getDesktopMode(), "Engine 2D", sf::Style::Fullscreen);
		}
		else
		{
			window.create(sf::VideoMode(800, 600), "Engine 2D");
		}
	}
}

void Engine::setFramerateLimit(unsigned int limit)
{
	window.setFramerateLimit(limit);
}

void Engine::mainLoop()
{
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		handleEvents();
		update();
		draw();
	}
}

void Engine::setBackgroundColor(const sf::Color& color)
{
	backgroundColor = color;
}

Engine::~Engine()
{
}
