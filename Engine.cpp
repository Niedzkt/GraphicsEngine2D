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

	renderer.drawLine({ 100, 100 }, { 200, 300 }, sf::Color::Red, 5.0f);
	renderer.drawLineByBresenham({ 300, 300 }, { 200, 400 }, sf::Color::Magenta, 1.0f);
	renderer.drawRectangle({ 400, 100 }, { 150, 75 }, sf::Color::Green);
	renderer.drawCircle({ 600, 300 }, 50, sf::Color::Blue);
	for (const auto& segment : segments)
	{
		segment.draw(renderer, sf::Color::White, 2.0f, true);
	}

	renderer.drawPolyline(myPoints, sf::Color::Red, 2.0f, true); 
	renderer.drawClosedPolyline(myPoints, sf::Color::Blue, 2.0f, false);
	
	renderer.drawCircleBresenham(circleCenter.getX(), circleCenter.getY(), circleRadius, circleColor);

	point.draw(renderer);
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
	:window(sf::VideoMode(width, height), title),
	deltaTime(0.0f),
	backgroundColor(sf::Color::Black),
	renderer(window),
	point(200.0f, 150.0f)
{
	segments.emplace_back(Point2D(200.0f, 100.0f), Point2D(500.0f, 400.0f));
	segments.emplace_back(Point2D(300.0f, 200.0f), Point2D(400.0f, 450.0f));

	myPoints = { Point2D(100, 100), Point2D(150, 200), Point2D(200, 150) };
	myPoints = { Point2D(200, 200), Point2D(250, 300), Point2D(100, 350) };

	circleCenter = Point2D(width / 2, height / 2);
	circleRadius = 100.0f;
	circleColor = sf::Color::Red;

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
