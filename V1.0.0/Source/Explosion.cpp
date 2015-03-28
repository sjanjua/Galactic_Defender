#include "Explosion.hpp"

Explosion::Explosion( sf::Texture& texture )
	: m_sprite( texture )
	, m_animator( 64, 64, 5, 5, Util::TimePerFrame.asSeconds() )
{
	sf::IntRect bounds = m_animator.returnRect();

	m_sprite.setOrigin( bounds.width / 2, bounds.height / 2 );
}

void Explosion::updateCurrent( sf::Time dt, sf::View& view )
{
	m_animator.update( dt );

		m_sprite.setTextureRect( m_animator.returnRect() );
}

void Explosion::drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const
{
	target.draw( m_sprite, states );
}