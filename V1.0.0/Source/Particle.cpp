#include "Particle.hpp"

Particle::Particle()
	: m_velocity( 0, 0 )
	, m_alive( false )
{

}

/**
 * Initialize the particle by setting a texture
 * to it.
*/
void Particle::init( sf::Texture& texture )
{
	m_texture = texture;

	m_sprite.setTexture( m_texture );

	sf::FloatRect bounds = m_sprite.getLocalBounds();

	m_sprite.setOrigin( bounds.width / 2, bounds.height / 2 );
}

/**
 * Update's the particle every frame.
*/
void Particle::update( sf::Time dt )
{
	sf::Vector2f position = getPosition();
	position += m_velocity * dt.asSeconds();
	setPosition( position );

	m_rect.left   = getPosition().x - ( m_sprite.getTexture() -> getSize().x / 2 );
	m_rect.top    = getPosition().y - ( m_sprite.getTexture() -> getSize().y / 2 );
	m_rect.width  = m_sprite.getTexture() -> getSize().x;
	m_rect.height = m_sprite.getTexture() -> getSize().y;
}