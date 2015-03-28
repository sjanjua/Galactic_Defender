#include "Button.hpp"

Button::Button(Type type, ResourceManager<Texture::ID, sf::Texture>& textureManager, ResourceManager< Font::ID, sf::Font >& fontManager, const std::string& string)
	:m_sprite(textureManager.getResource(toTextureID( type )))
	,m_text( nullptr )
{
	sf::FloatRect bounds = m_sprite.getLocalBounds();

	m_sprite.setOrigin( bounds.width / 2, bounds.height / 2 );

	std::unique_ptr< Text > text( new Text( fontManager.getResource( Font::Digital ) ) );
	m_text = text.get();
	m_text -> setString( string );
	m_text -> setSize( 30 );
	m_text -> setColor( sf::Color::Cyan );
	attachChild( std::move( text ) );
}

void Button::updateCurrent( sf::Time dt, sf::View& view)
{
	m_text -> setOffset( -50, -25 );
}

void Button::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}

Texture::ID Button::toTextureID(Type type)
{
	switch( type )
	{
	case Type::BUTTON:
		{
			return Texture::Button;
		}
		break;
	case Type::BUTTON_SELECTED:
		{
			return Texture::Button_Selected;
		}
		break;
	}
}