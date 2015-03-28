#ifndef TEXT_HPP
#define TEXT_HPP

#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include "ResourceManager.hpp"
#include "SceneNode.hpp"
#include "Constants.hpp"

class Text : public SceneNode
{
public:
	
	Text( const sf::Font& font );

	virtual void updateCurrent( sf::Time dt, sf::View& view );

	virtual void drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const;

	sf::Text&    getText()                            { return m_text; }

	void         setString( const std::string& text ) { m_text.setString( text ); }
	void         setSize( int size )                  { m_text.setCharacterSize( size ); }
	void         setColor( sf::Color color )          { m_text.setColor( sf::Color( color ) ); }
	void         setOffset( float x, float y )        { m_offset = sf::Vector2f( x, y ); }			// Provides the same functionality as 'setPosition()'
	void         setOffset( sf::Vector2f pos )        { m_offset = pos; }							// Overloaded function, does the same thing ^^^

private:

	sf::Font      m_font;
	sf::Text      m_text;

	sf::Vector2f  m_offset;
};

#endif //TEXT_HPP