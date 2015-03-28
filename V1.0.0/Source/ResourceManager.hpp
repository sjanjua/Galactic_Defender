#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <map>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <assert.h>

/**
 * Different enum types from this namespace will be 
 * used to create different resource maps. The enum type
 * will be used as the key for the map.
 */
namespace Texture
{
	enum ID 
	{ 
		Space, 
		Player, 
		Enemy, 
		Laser, 
		Repair_PU, 
		FireRate_PU, 
		Explosion,
		Button,
		Button_Selected
	};
};

namespace Sound
{
	enum ID 
	{ 
		Shoot, 
		Explosion, 
		PowerUp 
	};
};

namespace Font
{
	enum ID { Digital };
};

/**
 * Generic template class to store all of the in game
 * resources. Use one of the enums from above as the key
 * and then use one of SFML's object types as the actual
 * resource type.
 */
template< typename ID, typename Resource >
class ResourceManager
{
public:

	ResourceManager();

	void      load( ID id, const std::string& file );
	Resource& getResource( ID id );

private:

	std::map< ID, std::unique_ptr< Resource > > m_resources;
};

#include "ResourceManager.inl"

#endif //RESOURCE_MANAGER_HPP