#ifndef POWER_UP_HPP
#define POWER_UP_HPP

#include <SFML/Graphics.hpp>
#include "SceneNode.hpp"

class PowerUp : public SceneNode
{
public:

	enum Type
	{
		FireRate,
		Health
	};

	PowerUp( sf::Texture& texture );

	virtual void updateCurrent( sf::Time dt, sf::View& view );

	bool         isCollected() const    { return m_collected ? true : false; }

	sf::Sprite&  getSprite()            { return m_sprite; }
	sf::IntRect& getRect()              { return m_rect; }

	void         setCollected( bool c ) { m_collected = c; }
	void         setType( Type type )   { m_type = type; }
	Type         getType()              { return m_type; }

protected:

	virtual void drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const;

	sf::Sprite   m_sprite;

	sf::IntRect  m_rect;

	bool         m_collected;

	Type         m_type;
};

#endif //POWER_UP_HPP