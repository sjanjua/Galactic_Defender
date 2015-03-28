#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.hpp"
#include "ResourceManager.hpp"
#include "Text.hpp"

class Button :public Entity
{
public:
	enum Type
	{
		 BUTTON
		,BUTTON_SELECTED
	};
	Button(Type type,ResourceManager<Texture::ID,sf::Texture> & textureManager, ResourceManager< Font::ID, sf::Font >& fontManager, const std::string& string);

	virtual void		updateCurrent( sf::Time dt, sf::View& view );
	void				setText(std::string _text)		 { m_text->setString(_text); }
	Text*			    getText()						 { return m_text; }

private:
	virtual void		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	Texture::ID			toTextureID( Type type );
	
	Text*				m_text;
	sf::Sprite			m_sprite;
};
#endif