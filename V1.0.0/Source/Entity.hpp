#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include "SceneNode.hpp"

class Entity : public SceneNode
{
public:

	Entity() : m_velocity( 0, 0 ) {}

	virtual void updateCurrent( sf::Time dt, sf::View& view );

	void         setVelocity( float x, float y )  { m_velocity = sf::Vector2f( x, y ); }
	void         setVelocity( sf::Vector2f vel )  { m_velocity = vel; }

	sf::Vector2f getVelocity() const              { return m_velocity; }

protected:

	sf::Vector2f m_velocity;
};

#endif //ENTITY_HPP