#ifndef SHIP_HPP
#define SHIP_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.hpp"
#include "ResourceManager.hpp"
#include "ParticleSystem.hpp"
#include "Constants.hpp"

class Ship : public Entity
{
public:

	enum Type
	{
		Player,
		Enemy
	};

	explicit        Ship( Type type, ResourceManager< Texture::ID, sf::Texture >& textureManager );

	virtual void    updateCurrent( sf::Time dt, sf::View& view );

	Texture::ID     toTextureID( Type type );

	void            fire( sf::Sound& sound );

	void            setHealth( int health )      { m_health = health; }
	void            modHealth( int mod )         { m_health += mod; }

	void            setAlive( bool alive )       { m_alive = alive; }

	sf::Sprite&     getSprite()                  { return m_sprite; }
	ParticleSystem& getLaserSystem()             { return m_laserSystem; }
	sf::IntRect&    getRect()                    { return m_rect; }
	int             getHealth()                  { return m_health; }
	bool            isAlive()                    { return m_alive ? true : false; }
	bool            isVisible()                  { return m_visible ? true : false; }
	Type            getType()                    { return m_type; }

private:

	virtual void drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const;

	Type                   m_type;

	sf::Sprite             m_sprite;

	mutable ParticleSystem m_laserSystem;

	sf::Vector2f           m_prevPosition;

	sf::IntRect            m_rect;

	int                    m_health;
	
	bool                   m_alive;

	bool                   m_visible;
};

#endif //SHIP_HPP