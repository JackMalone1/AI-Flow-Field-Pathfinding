#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include "Tile.h"
class Game
{
public:
	Game();
	~Game();

	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	std::array<std::array<Tile*, 50>, 50> m_tiles;

	sf::RenderWindow m_window;
	sf::Font m_font;

	bool m_exitGame;

};

#endif 