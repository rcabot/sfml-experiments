#include "Platform/PlatformHelper.hpp"
#include "TileMap.cpp"
#include "Character.cpp"

int main()
{

	const float FPS = 60.0f; //The desired FPS. (The number of updates each second).
	PlatformHelper platform;
	sf::RenderWindow window;
	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());
	// Use the screenScalingFactor
	window.create(sf::VideoMode(200.0f * screenScalingFactor, 200.0f * screenScalingFactor),
		"Rachel's very special game!");
    window.setFramerateLimit(FPS);

	platform.setIcon(window.getSystemHandle());

	// define the level with an array of tile indices
    const int level[] =
    {
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
        0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
    };

    // create the tilemap from the level definition
    TileMap map;
    if (!map.load("content/colored_tilemap_packed.png", sf::Vector2u(16, 16), level, 16, 8))
	{
		return -1;
	}

    Character character;
	character.load("content/colored_tilemap_packed.png", sf::Vector2u(16, 16),16);
    character.setOrigin(10.0f, 10.0f);
    character.setPosition(0, 150.0f);

	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			window.close();
		}

		character.move(1.0f,0.0f);

		window.clear();
		//window.draw(map);
		window.draw(character);
		window.display();
	}

	return 0;
}
