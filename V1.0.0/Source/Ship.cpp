#include "Ship.hpp"

Ship::Ship( Type type, ResourceManager< Texture::ID, sf::Texture >& textureManager )
	: m_type( type )
	, m_sprite( textureManager.getResource( toTextureID( type ) ) )
	, m_laserSystem( 25 )
	, m_prevPosition( 0.0f, 0.0f )
	, m_rect()
	, m_health( 0 )
	, m_alive( true )
{
	sf::FloatRect bounds = m_sprite.getLocalBounds();

	m_sprite.setOrigin( bounds.width / 2, bounds.height / 2 );
}

void Ship::updateCurrent( sf::Time dt, sf::View& view )
{
	if ( m_type == Type::Player )
	{
		m_laserSystem.setEmitter( getPosition().x, getPosition().y - ( m_sprite.getTexture() -> getSize().y / 2 ) );
	}

	else if ( m_type == Type::Enemy )
	{
		m_laserSystem.setEmitter( getPosition().x, getPosition().y + ( m_sprite.getTexture() -> getSize().y / 2 ) );
	}

	m_laserSystem.update( dt, view );

	m_prevPosition = getPosition();

	move( m_velocity * dt.asSeconds() );

	if ( getPosition().x <= 0 + ( m_sprite.getTexture() -> getSize().x / 2 ) )
	{
		setPosition( m_prevPosition );
	}	

	if ( getPosition().x + ( m_sprite.getTexture() -> getSize().x / 2 ) > Util::V_Width )
	{
		setPosition( m_prevPosition );
	}

	if ( getPosition().y + ( m_sprite.getTexture() -> getSize().y / 2 ) > ( view.getCenter().y + ( Util::V_Height / 2 ) ) )
	{
		setPosition( m_prevPosition );
	}

	m_rect.left   = getPosition().x - ( m_sprite.getTexture() -> getSize().x / 2 );
	m_rect.top    = getPosition().y - ( m_sprite.getTexture() -> getSize().y / 2 );
	m_rect.width  = m_sprite.getTexture() -> getSize().x;
	m_rect.height = m_sprite.getTexture() -> getSize().y;

	if ( m_type == Type::Enemy )
	{
		if ( getPosition().y > ( view.getCenter().y - ( Util::V_Height / 2 ) ) - ( this -> getSprite().getTextureRect().height / 2 ) &&
			 getPosition().y - this -> getSprite().getTexture() -> getSize().y / 2 < view.getCenter().y + Util::V_Height / 2 )
		{
			m_visible = true;
		}

		else
		{
			m_visible = false;
		}
	}

	else if ( m_type == Type::Player ) 
	{
		m_visible = true;
	}
}

void Ship::drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const 
{
	if ( m_type == Type::Player )
	{
		target.draw( m_sprite, states );

		for ( int i = 0; i < m_laserSystem.getNumParticles(); i++ )
		{
			if ( m_laserSystem.getParticles()[ i ].isAlive() )
			{
				target.draw( m_laserSystem.getParticles()[ i ].getSprite() );
			}
		}
	}

	else if ( m_type == Type::Enemy && m_visible == true )
	{
		target.draw( m_sprite, states );
	}

	for ( int i = 0; i < m_laserSystem.getNumParticles(); i++ )
	{
		if ( m_laserSystem.getParticles()[ i ].isAlive() )
		{
			target.draw( m_laserSystem.getParticles()[ i ].getSprite() );
		}
	}

}

Texture::ID Ship::toTextureID( Type type )
{
	switch ( type )
	{
	case Type::Player:
		{
			return Texture::Player;
		}
		break;

	case Type::Enemy:
		{
			return Texture::Enemy;
		}
		break;
	}
}

void Ship::fire( sf::Sound& sound )
{
	float shootSpeed = -1000;

	if ( m_type == Type::Enemy )
	{
		shootSpeed = 250;
	}

	for ( int i = 0; i < m_laserSystem.getNumParticles(); i++ )
	{
		if ( m_laserSystem.getParticles()[ i ].isAlive() == false )
		{
			m_laserSystem.addElapsed( m_laserSystem.getClock().restart() );

			if ( m_laserSystem.getElapsed() >= m_laserSystem.getDelay() )
			{
				m_laserSystem.getParticles()[ i ].setAlive( true );
				m_laserSystem.getParticles()[ i ].setVelocity( 0.0f, shootSpeed );
				m_laserSystem.subElapsed( m_laserSystem.getElapsed() );
				sound.play();
			}
		}
	}
}