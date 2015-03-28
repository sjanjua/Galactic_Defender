#include "Powerup.hpp"

PowerUp::PowerUp( sf::Texture& texture )
	: m_sprite( texture )
	, m_rect()
	, m_collected( false )
{
	sf::FloatRect bounds = m_sprite.getLocalBounds();

	m_sprite.setOrigin( bounds.width / 2, bounds.height / 2 );
}

void PowerUp::updateCurrent( sf::Time dt, sf::View& view )
{
	if ( isCollected() == false )
	{
		m_rect.left   = getPosition().x - ( m_sprite.getTexture() -> getSize().x / 2 );
		m_rect.top    = getPosition().y - ( m_sprite.getTexture() -> getSize().y / 2 );
		m_rect.width  = m_sprite.getTexture() -> getSize().x;
		m_rect.height = m_sprite.getTexture() -> getSize().y;
	}
}

void PowerUp::drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const
{
	if ( isCollected() == false )
	{
		target.draw( m_sprite, states );
	}
}