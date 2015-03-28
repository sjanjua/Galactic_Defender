#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SFML/System.hpp>

#include <string>

/**
 * Just some general constants that will be used throughout
 * the game.
 */
namespace Util
{
	const std::string Title      = "Space Shooter";
	const std::string Version    = "v0.0.4";

	const float V_Width          = 480;
	const float V_Height         = 900; 

	const sf::Time TimePerFrame  = sf::seconds( 1 / 60.0f );

	const float CameraSpeed      = -100.0f;

	const int   LevelLength      = 10000;
};

#endif //CONSTANTS_HPP