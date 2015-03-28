#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include <SFML/Graphics.hpp>
#include "SceneNode.hpp"
#include "Animator.hpp"
#include "Constants.hpp"

class Explosion : public SceneNode
{
public:

	Explosion( sf::Texture& texture );

	virtual void updateCurrent( sf::Time dt, sf::View& view );
	virtual void drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const;

	Animator&    getAnimator() { return m_animator; }

private:

	sf::Sprite m_sprite;

	mutable Animator   m_animator;
};

#endif //EXPLOSION_HPP