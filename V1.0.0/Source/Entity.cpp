#include "Entity.hpp"

void Entity::updateCurrent( sf::Time dt, sf::View& view )
{
	move( m_velocity * dt.asSeconds() );
}