#ifndef SCENE_NODE_HPP
#define SCENE_NODE_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <assert.h>

class SceneNode : public sf::Drawable, public sf::Transformable
{
public:

	typedef std::unique_ptr< SceneNode > NodePtr;

	SceneNode();

	void                 update( sf::Time dt, sf::View& view);
	virtual void         updateCurrent( sf::Time dt, sf::View& view);
	void                 updateChildren( sf::Time dt, sf::View& view );

	void                 attachChild( NodePtr child );
	NodePtr              detachChild( const SceneNode& node );

	sf::Transform        getWorldTransform();
	sf::Vector2f         getWorldPosition();

protected:

	virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;
	virtual void drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const;

	std::vector< NodePtr > m_children;
	SceneNode*			   m_parent;
};

#endif //SCENE_NODE_HPP