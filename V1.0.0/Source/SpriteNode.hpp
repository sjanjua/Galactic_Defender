#ifndef SPRITE_NODE_HPP
#define SPRITE_NODE_HPP

#include "SceneNode.hpp"

class SpriteNode : public SceneNode
{
public:

	SpriteNode( sf::Texture& texture ) : m_sprite( texture ) {}
	SpriteNode( sf::Texture& texture, sf::IntRect rect ) : m_sprite( texture, rect ) {} 

private:

	virtual void drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const;

	sf::Sprite   m_sprite;
};

#endif //SPRITE_NODE_HPP