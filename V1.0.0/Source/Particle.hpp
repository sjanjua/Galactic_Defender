#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics.hpp>

/**
 * Contains the data that a single particle will
 * need. Updates itself every frame.
*/
class Particle
{
public:

	Particle();

	void init( sf::Texture& texture );

	void update( sf::Time dt );

	sf::Sprite&  getSprite()                     { return m_sprite; }
	sf::Texture& getTexture()                    { return m_texture; }
	sf::Vector2f getPosition()                   { return m_sprite.getPosition(); }
	sf::Vector2f getVelocity()                   { return m_velocity; }
	bool         isAlive()                       { return m_alive ? true : false; }
	sf::IntRect& getRect()						 { return m_rect; }

	void		 setPosition( float x, float y ) { m_sprite.setPosition( x, y ); }
	void		 setPosition( sf::Vector2f pos ) { m_sprite.setPosition( pos ); }
	void		 setVelocity( float x, float y ) { m_velocity = sf::Vector2f( x, y ); }
	void		 setVelocity( sf::Vector2f vel ) { m_velocity = vel; }
	void		 setAlive( bool alive )          { m_alive = alive; }

private:

	sf::Sprite   m_sprite;
	sf::Texture  m_texture;

	sf::Vector2f m_velocity;

	bool		 m_alive;

	sf::IntRect  m_rect;
};

#endif  PARTICLE_HPP