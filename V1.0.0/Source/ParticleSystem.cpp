#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem()
	: m_numParticles( 0 )
	, m_emitter( 0, 0 )
	, m_clock()
	, m_elapsed( sf::Time::Zero )
	, m_delay( sf::Time::Zero )
{

}

ParticleSystem::ParticleSystem( int particles )
	: m_numParticles( particles )
	, m_emitter( 0, 0 )
	, m_clock()
	, m_elapsed( sf::Time::Zero )
	, m_delay( sf::Time::Zero )
{

	m_particles.resize( m_numParticles );

	m_delay = sf::milliseconds( 300 );
}

/**
 * Initializes the particle system by looping 
 * through all of the particles it contains and
 * initializing them as well. Pass a texture into it
 * so that it can pass it on to the particles.
*/
void ParticleSystem::init( sf::Texture& texture )
{
	for ( Particle& p : m_particles )
	{
		p.init( texture );
		p.setPosition( m_emitter );
	}
}

/**
 * Updates the particle system. Loops through all
 * of the particles and updates them if they are
 * alive.
*/
void ParticleSystem::update( sf::Time dt, sf::View& view )
{
	for ( int i = 0; i < m_particles.size(); i++ )
	{
		Particle &p = m_particles[ i ];

		if ( p.isAlive() )
		{
			p.update( dt );

			if ( ( p.getPosition().y + p.getTexture().getSize().y ) <= view.getCenter().y - ( Util::V_Height / 2 ) )
			{
				reset( i );
			}
		}

		else
		{
			reset( i );
		}
	}
}

/**
 * Resets the particles back to the emitter's
 * position and set's their "alive" status to
 * false.
*/
void ParticleSystem::reset( int i )
{
	m_particles[ i ].setAlive( false );
	m_particles[ i ].setPosition( m_emitter );
	m_particles[ i ].setVelocity( 0.0f, 0.0f );
}