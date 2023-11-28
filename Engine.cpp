#include "Engine.h"

// Funkcja `handleEvents` klasy `Engine` jest odpowiedzialna za obs�ug� zdarze� generowanych przez u�ytkownika.
// W tej funkcji przetwarzane s� zdarzenia zwi�zane z oknem aplikacji (takie jak zamkni�cie okna),
// klawiatur� (naci�ni�cie lub zwolnienie klawisza) oraz mysz� (naci�ni�cie przycisku myszy, zwolnienie
// przycisku myszy, ruch mysz�). Dla ka�dego z tych zdarze�, funkcja wywo�uje odpowiedni� metod�
// do ich obs�ugi: `handleKeyboardEvents` dla zdarze� klawiatury i `handleMouseEvents` dla zdarze� myszy.
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

// Funkcja `update` klasy `Engine` jest odpowiedzialna za aktualizacj� stanu gry lub aplikacji.
// W tej funkcji wywo�ywane s� metody aktualizuj�ce r�ne elementy gry, takie jak ruchome linie,
// animowane bitmapy, ruchome prostok�ty i ko�a. Aktualizacja ka�dego z tych element�w
// zale�y od up�ywu czasu, kt�ry jest reprezentowany przez `deltaTime`.
// Funkcja ta jest typowym miejscem, gdzie umieszcza si� logik� aktualizacji stanu gry
// w ka�dej klatce animacji lub cyklu gry.
void Engine::update()
{
	movingLine.update(deltaTime);
	animatedBitmap.update(deltaTime);
	movingRectangle.update(deltaTime);
	movingCircle.update(deltaTime);
	for (auto& rect : movingRectangles) {
		rect.update(deltaTime);
	}
}

// Funkcja `draw` klasy `Engine` jest odpowiedzialna za renderowanie wszystkich element�w graficznych gry.
// W tej funkcji najpierw czy�ci okno, wy��cza transformacje translacji, a nast�pnie wykonuje szereg operacji rysowania,
// takich jak rysowanie linii, prostok�t�w, ko�a oraz obs�uga bitmap i animowanych bitmap.
// Renderuje r�wnie� r�ne elementy zwi�zane z fizyk� gry, jak ruchome prostok�ty i ko�a.
// Na ko�cu funkcja wy�wietla zaktualizowan� zawarto�� okna.
void Engine::draw()
{
	window.clear(backgroundColor);
	renderer.disableTranslationTransform();
	renderer.setRotation(20.0f).drawLine(movingLine, sf::Color::Red, 5.0f, 200.0f);
	//renderer.resetTransformation();
	renderer.setScale(5.0f,5.0f).drawLine({ 100, 100 }, { 200, 300 }, sf::Color::Red, 5.0f);
	renderer.setRotation(20.0f).drawRectangle({400, 100}, {150, 75}, sf::Color::Green);
	renderer.setScale(2.0f,2.0f).drawCircle({600, 300}, 50, sf::Color::Blue);
	bitmapRenderer.setRotation(20.0f).draw(window);
	animatedBitmap.draw(window);
	movingRectangle.ax = -100.0f;
	renderer.drawPhysicsRectangle(movingRectangle);
	renderer.drawPhysicsCircle(movingCircle);
	for (auto& rect : movingRectangles) {
        renderer.drawPhysicsRectangle(rect);
    }

/*
	renderer.setScale(20.0f,20.0f).drawLine({ 100, 100 }, { 200, 300 }, sf::Color::Red, 5.0f);
	renderer.drawLineByBresenham({ 300, 300 }, { 200, 400 }, sf::Color::Magenta, 1.0f);
	renderer.drawRectangle({ 400, 100 }, { 150, 75 }, sf::Color::Green);
	renderer.drawCircle({ 600, 300 }, 50, sf::Color::Blue);
	for (const auto& segment : segments)
	{
		segment.draw(renderer, sf::Color::White, 2.0f, true);
	}

	renderer.drawPolyline(myPoints, sf::Color::Red, 2.0f, true); 
	renderer.drawClosedPolyline(myPoints, sf::Color::Blue, 2.0f, false);
	renderer.drawCircleAlgorithm(300, 200, 50, sf::Color::Green);
	renderer.drawEllipse(400.0f, 300.0f, 200.0f, 100.0f, sf::Color::Cyan);
	renderer.drawPolygon(polygonPoints, sf::Color::Red);
	renderer.fillRectangle(200.0f, 100.0f, 100.0f, 400.0f, sf::Color::Cyan);
	renderer.fillCircle(400.0f, 500.0f, 300.0f, sf::Color::Green);
	renderer.fillPolygon(polygonPoints, sf::Color::Red);
	point.draw(renderer); */
	window.display();
}

// Funkcja `logError` klasy `Engine` jest wykorzystywana do zapisywania komunikat�w o b��dach do pliku.
// Funkcja otwiera plik "error_log.txt" w trybie dopisywania i zapisuje przekazany komunikat.
// W przypadku problem�w z otwarciem pliku, b��d jest wypisywany na standardowe wyj�cie b��d�w.
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

// Funkcja `handleKeyboardEvents` klasy `Engine` jest odpowiedzialna za obs�ug� zdarze� klawiatury.
// Reaguje na naci�ni�cia klawiszy, takich jak Escape (zamkni�cie okna), Space oraz inne, uruchamiaj�c
// odpowiednie d�wi�ki i wy�wietlaj�c komunikaty o aktualnie odtwarzanej muzyce.
void Engine::handleKeyboardEvents(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape)
		{
			window.close();
		}
		if (event.key.code == sf::Keyboard::Space) 
		{
			soundManager.playSound("stableRonaldo");
			std::cout << "Currently playing: stableRonaldo" << std::endl;
			logError("test w stableRonaldo");
		}
		if (event.key.code == sf::Keyboard::S)
		{
			soundManager.playSound("shrek");
			std::cout << "Currently playing: shreksophone" << std::endl;
		}
		if (event.key.code == sf::Keyboard::O)
		{
			soundManager.playSound("omfg");
			std::cout << "Currently playing: omfg hello" << std::endl;
		}
		if (event.key.code == sf::Keyboard::W)
		{
			soundManager.playSound("wide");
			std::cout << "Currently playing: wide" << std::endl;
		}
		if (event.key.code == sf::Keyboard::C)
		{
			soundManager.playSound("candyland");
			std::cout << "Currently playing: candyland" << std::endl;
		}
		if (event.key.code == sf::Keyboard::P)
		{
			soundManager.stopSound("stableRonaldo");
			soundManager.stopSound("candyland");
			soundManager.stopSound("wide");
			soundManager.stopSound("omfg");
			soundManager.stopSound("shrek");
			std::cout << "All music stops playing" << std::endl;
		}
	}
}

// Funkcja `handleMouseEvents` klasy `Engine` obs�uguje zdarzenia myszy, takie jak naci�ni�cia przycisk�w myszy.
// W przypadku naci�ni�cia lewego przycisku myszy, tworzy nowy ruchomy prostok�t z losowymi parametrami i dodaje go do listy.
void Engine::handleMouseEvents(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			std::cout << "Left mouse button pressed" << std::endl;
			float x = static_cast<float>(event.mouseButton.x);
			float y = static_cast<float>(event.mouseButton.y);
			sf::Color color(std::rand() % 256, std::rand() % 256, std::rand() % 256); 

			MovingRectangle newRect(x, y, 50, 50, color); 
			newRect.vx = std::rand() % 200 - 100; 
			newRect.vy = std::rand() % 200 - 100; 
			newRect.ax = std::rand() % 200 - 100; 
			newRect.ay = std::rand() % 200 - 100; 

			movingRectangles.push_back(newRect);
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

//getter dla rozmiaru okna
sf::Vector2u Engine::getWindowSize() const
{
	return window.getSize();
}

// Konstruktor klasy `Engine` inicjalizuje g��wne komponenty silnika, takie jak okno, kolory t�a,
// r�ne renderery, jak r�wnie� wczytuje d�wi�ki i ustawia ich g�o�no��.
Engine::Engine(unsigned int width, unsigned height, const std::string& title)
	:window(sf::VideoMode(width, height), title),
	deltaTime(0.0f),
	backgroundColor(sf::Color::Black),
	renderer(window),
	point(200.0f, 150.0f),
	movingLine(100.0f, 100.0f, 200.0f, 250.0f),
	bitmapRenderer("textures/shrek.jpg", sf::Vector2f(100,100)),
	animatedBitmap("textures/test_player.png", sf::Vector2i(64, 64), 4, 0.1f, sf::Vector2f(100, 100)),
	movingRectangle(100,100,50,50,sf::Color::Red),
	movingCircle(300,300,30, sf::Color::Yellow)
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	segments.emplace_back(Point2D(200.0f, 100.0f), Point2D(500.0f, 400.0f));
	segments.emplace_back(Point2D(300.0f, 200.0f), Point2D(400.0f, 450.0f));

	myPoints = { Point2D(100, 100), Point2D(150, 200), Point2D(200, 150) };
	myPoints = { Point2D(200, 200), Point2D(250, 300), Point2D(100, 350) };

	circleCenter = Point2D(width / 2, height / 2);
	circleRadius = 100.0f;
	circleColor = sf::Color::Red;

	polygonPoints.push_back(Point2D(100, 200));
	polygonPoints.push_back(Point2D(50, 100));
	polygonPoints.push_back(Point2D(500, 1000));
	polygonPoints.push_back(Point2D(400, 500));

	soundManager.loadSound("stableRonaldo", "music/music.wav");
	soundManager.loadSound("omfg", "music/omfg.wav");
	soundManager.loadSound("shrek", "music/shrek.wav");
	soundManager.loadSound("wide", "music/wide.wav");
	soundManager.loadSound("candyland", "music/candyland.wav");
	soundManager.setVolume(50.0f);
	
}

// Funkcja `initialize` klasy `Engine` ustawia podstawowe parametry okna, takie jak limit klatek na sekund�,
// i zwraca status inicjalizacji. W przypadku b��du, zapisuje komunikat b��du do logu.
bool Engine::initialize()
{
	try
	{
		window.setFramerateLimit(60); 
		window.setKeyRepeatEnabled(true); 
		return true;
	}
	catch (const std::exception& e)
	{
		logError(e.what());
		return false;
	}
}
// Funkcja `setFullscreen` klasy `Engine` pozwala na prze��czanie trybu pe�noekranowego.
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
// Funkcja `setFramerateLimit` klasy `Engine` pozwala na ustawienie limitu klatek na sekund� dla okna.
void Engine::setFramerateLimit(unsigned int limit)
{
	window.setFramerateLimit(limit);
}

// Funkcja `mainLoop` klasy `Engine` zawiera g��wn� p�tl� gry, gdzie odbywa si� obs�uga zdarze�, aktualizacja stanu gry i rysowanie.
void Engine::mainLoop()
{
	sf::Vector2u windowSize = window.getSize();
	GameObject::setWindowSize(windowSize);

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		handleEvents();
		update();
		draw();
	}
}

// Funkcja `setBackgroundColor` klasy `Engine` pozwala na zmian� koloru t�a okna.
void Engine::setBackgroundColor(const sf::Color& color)
{
	backgroundColor = color;
}
// Destruktor klasy `Engine` wykonuje niezb�dne czynno�ci podczas niszczenia obiektu klasy `Engine`.
Engine::~Engine()
{
}
