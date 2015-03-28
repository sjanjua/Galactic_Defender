#ifndef PARTICLE_SYSTEM_HPP
#define PARTICLE_SYSTEM_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Particle.hpp"
#include "Constants.hpp"

/**
 * Manages an array of particles and updates them.
*/
class ParticleSystem
{
public:

	ParticleSystem();
	ParticleSystem( int particles );

	void init( sf::Texture& texture );
	void update( sf::Time dt, sf::View& view );
	void reset( int i );

	void addElapsed( sf::Time dt )                          { m_elapsed += dt; }
	void subElapsed( sf::Time dt )                          { m_elapsed -= dt; }

	int                      getNumParticles()              { return m_numParticles; }
	sf::Vector2f             getEmitter()                   { return m_emitter; }
	std::vector< Particle >& getParticles()                 { return m_particles; }
	sf::Clock&               getClock()						{ return m_clock; }
	sf::Time				 getElapsed()					{ return m_elapsed; }
	sf::Time				 getDelay()						{ return m_delay; }

	void                     setEmitter( float x, float y ) { m_emitter = sf::Vector2f( x, y ); }
	void                     setEmitter( sf::Vector2f e )   { m_emitter = e; }
	void                     setDelay( sf::Time delay )     { m_delay = delay; }
	void                     decreaseDelay( sf::Time mod )  { m_delay -= mod; }

private:

	int						m_numParticles;

	sf::Vector2f			m_emitter;

	std::vector< Particle > m_particles;

	sf::Clock				m_clock;
	sf::Time				m_elapsed;
	sf::Time				m_delay;
};

#endif //PARTICLE_SYSTEM_HPP