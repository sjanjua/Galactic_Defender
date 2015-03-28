#include "SpriteNode.hpp"

void SpriteNode::drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const 
{
	target.draw( m_sprite, states );
}