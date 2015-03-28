#include "Game.hpp"

Game::Game()
	: m_window( sf::VideoMode( Util::V_Width, Util::V_Height ), Util::Title )
	, m_world( m_window )
	, m_event()
	, m_clock()
	, m_timeSinceUpdate( sf::Time::Zero )
{
	
}

/**
 * Start running the game
 */
void Game::run()
{
	while ( m_window.isOpen() )
	{
		handleEvents();

		m_timeSinceUpdate += m_clock.restart();

		while ( m_timeSinceUpdate > Util::TimePerFrame )						
		{
			m_timeSinceUpdate -= Util::TimePerFrame;

			m_world.update( Util::TimePerFrame );
		}

		m_window.clear();
		m_world.render();
		m_window.display();
	}
}

/**
 * Handle basic input such as closing the window
 * and exiting the application
 */
void Game::handleEvents()
{
	while ( m_window.pollEvent( m_event ) )
	{
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) || m_event.type == sf::Event::Closed )
		{
			m_window.close();
		}
	}
}