#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>
#include "SceneNode.hpp"
#include "SpriteNode.hpp"
#include "Ship.hpp"
#include "ResourceManager.hpp"
#include "Constants.hpp"
#include "Text.hpp"
#include "Powerup.hpp"
#include "Explosion.hpp"
#include "Button.hpp"
#include <sstream>
#include <random>

class World
{
public:

	enum GameState 
	{
		MainMenu,
		Game,
		GameOver
	};

	explicit       World( sf::RenderWindow& window );

	void           update( sf::Time dt );
	void           render();
		           
	void           loadResources();
	void           buildScene();
		           
	void           playerInput();
	void           enemyAI();
		           
	void           collisionCheck();
	sf::Vector2f   randomSpawner();
	void           setRandomVard( float& a, float& b );

	void           updateExplosions();

	void           updateMainMenu( sf::Time dt );
	void		   updateGame( sf::Time dt );
	void           updateGameOver( sf::Time dt );

	std::string    toString( int num   );
	std::string    toString( float num );

	sf::FloatRect& getRect() { return m_rect; }

	enum Layer
	{
		Background,
		Air,
		GUI,
		LayerCount
	};

	typedef ResourceManager< Texture::ID, sf::Texture >   TextureManager;
	typedef ResourceManager< Font::ID, sf::Font >         FontManager;
	typedef ResourceManager< Sound::ID, sf::SoundBuffer > SoundManager;

private:

	sf::RenderWindow&                           m_window;
	sf::View                                    m_camera;

	TextureManager                              m_textureManager;
	FontManager                                 m_fontManager;
	SoundManager								m_soundManager;

	SceneNode                                   m_sceneGraph;
	SceneNode									m_menuGraph;
	SceneNode									m_gameoverGraph;
	std::array< SceneNode*, Layer::LayerCount > m_sceneLayers;

	sf::FloatRect								m_worldBounds;
	sf::FloatRect                               m_rect;
	sf::Vector2f                                m_spawnPosition;
	float                                       m_scrollSpeed;

	Ship*										m_player;

	const int                                   m_numEnemies;
	std::vector< Ship* >                        m_enemies;

	std::vector< Explosion* >                   m_explosions;

	Text*                                       m_gameTime;
	sf::Time                                    m_elapsed;

	Text*										m_title;
	Text*                                       m_health;
	Text*										m_score;
	
	int											m_killCounter;

	std::vector< PowerUp* >                     m_powerUps;
	std::vector< Button* >					    m_buttons;

	Text*										m_debug;

	std::stringstream                           m_stream;

	sf::Sound									m_laserSound;
	sf::Music									m_themeMusic;

	GameState									m_currentState;

	bool										m_init;

	void randomPowerUpSpawner(float& _a, float& _b);

	void World::CheckButtonPress(const std::string& s1);
};

#endif //WORLD_HPP