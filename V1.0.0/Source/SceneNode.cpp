#include "SceneNode.hpp"
#include <iostream>

SceneNode::SceneNode()
	: m_parent( nullptr )
{

}

void SceneNode::update( sf::Time dt, sf::View& view )
{
	updateCurrent( dt, view );
	updateChildren( dt, view );
}

void SceneNode::updateCurrent( sf::Time dt, sf::View& view )
{

}

void SceneNode::updateChildren( sf::Time dt, sf::View& view )
{
	for ( const NodePtr& p : m_children )
	{
		p -> update( dt, view );
	}
}

void SceneNode::attachChild( SceneNode::NodePtr child )
{
	child -> m_parent = this;

	m_children.push_back( std::move( child ) );
}

SceneNode::NodePtr SceneNode::detachChild( const SceneNode& node )
{
	auto found = std::find_if( m_children.begin(), m_children.end(), [ & ] ( NodePtr& p ) -> bool { return p.get() == &node; } );

	assert( found != m_children.end() );

	NodePtr result = std::move( *found );

	result -> m_parent = nullptr;

	m_children.erase( found );

	return result;
}

void SceneNode::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
	states.transform *= getTransform();

	drawCurrent( target, states );

	for ( const NodePtr& p : m_children )
	{
		p -> draw( target, states );
	}
}

void SceneNode::drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const
{

}

sf::Transform SceneNode::getWorldTransform()
{
	sf::Transform transform = sf::Transform::Identity;

	for ( const SceneNode* node = this; node != nullptr; node = node -> m_parent )
	{
		transform = node -> getTransform() * transform;
	}

	return transform;
}

sf::Vector2f SceneNode::getWorldPosition()
{
	return getWorldTransform() * sf::Vector2f();
}