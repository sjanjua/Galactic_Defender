#include "Text.hpp"

Text::Text( const sf::Font& font )
	: m_font()
	, m_text()
	, m_offset( 0.0f, 0.0f )
{
	m_font = font;

	m_text.setFont( m_font );
}

void Text::updateCurrent( sf::Time dt, sf::View& view )
{
	sf::Vector2f position = getPosition();

	position.x = m_offset.x + ( view.getCenter().x - ( Util::V_Width / 2 ) );
	position.y = m_offset.y + ( view.getCenter().y - ( Util::V_Height / 2 ) );

	setPosition( position );
}

void Text::drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const 
{
	target.draw( m_text, states );
}
