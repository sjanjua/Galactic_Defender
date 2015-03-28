#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Constants.hpp"
#include "World.hpp"

/**
 * Contains all in game components needed to
 * run the game.
 */
class Game
{
public:

	Game();

	void run();

	void handleEvents();

private:

	sf::RenderWindow m_window;
	sf::Event        m_event;

	sf::Clock        m_clock;
	sf::Time         m_timeSinceUpdate;

	World            m_world;
};

#endif  //GAME_HPP