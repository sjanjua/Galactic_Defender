#include "World.hpp"

World::World( sf::RenderWindow& window )
	: m_window( window )
	, m_camera( window.getDefaultView() )
	, m_worldBounds( 0, -Util::LevelLength, Util::V_Width, Util::LevelLength + Util::V_Height  )
	, m_spawnPosition( Util::V_Width / 2, Util::V_Height / 2 )
	, m_scrollSpeed( 0.0f )
	, m_player( nullptr )
	, m_debug( nullptr )
	, m_stream()
	, m_numEnemies( 20 )
	, m_enemies( m_numEnemies )
	, m_killCounter( 0 )
	, m_powerUps( 4 )
	, m_currentState( World::GameState::MainMenu )
	, m_init( false )
	,m_buttons(2)
{
	//loadResources();
	//buildScene();

	m_camera.setCenter( m_spawnPosition );
}

void World::update( sf::Time dt )
{
	switch ( m_currentState )
	{
	case GameState::MainMenu:
		{
			if ( !m_init )
			{
				loadResources();
				buildScene();
				m_init = true;
			}

			else
			{
				updateMainMenu( dt );
			}
		}
		break;

	case GameState::Game:
		{
			if ( !m_init )
			{
				loadResources();
				buildScene();
				m_init = true;
			}

			else
			{
				updateGame( dt );
			}
		}
		break;

	case GameState::GameOver:
		{
			if ( !m_init )
			{
				loadResources();
				buildScene();
				m_init = true;
			}

			else
			{
				updateGameOver( dt );
			}
		}
		break;
	}

}

void World::render()
{
	m_window.setView( m_camera );

	switch(m_currentState)
	{
	case GameState::MainMenu:
		{
			m_window.draw( m_menuGraph );
		}
		break;
	case GameState::Game:
		{

			m_window.draw( m_sceneGraph );
		}
		break;
	case GameState::GameOver:
		{
			m_window.draw( m_gameoverGraph );
		}
		break;
	}

}

void World::loadResources()
{
	switch ( m_currentState )
	{
	case GameState::MainMenu:
		{
			m_textureManager.load( Texture::Player, "Resources/blue_ship.png" );
			m_textureManager.load( Texture::Enemy,  "Resources/enemy.png" );
			m_textureManager.load( Texture::Space, "Resources/space.png" );
			m_textureManager.load( Texture::Laser , "Resources/player_laser.png" );
			m_textureManager.load( Texture::FireRate_PU, "Resources/firerate_powerup.png" );
			m_textureManager.load( Texture::Repair_PU, "Resources/repair_powerup.png" );
			m_textureManager.load( Texture::Explosion, "Resources/Explosion.png" );
			m_textureManager.load(Texture::Button, "Resources/Button.png");
			m_fontManager.load( Font::Digital, "Resources/digital.ttf" );

			m_soundManager.load( Sound::Shoot, "Resources/laser_shoot.wav" );

			m_themeMusic.openFromFile( "Resources/space_theme.wav" );
		}
		break;

	case GameState::Game:
		{

		}
		break;

	case GameState::GameOver:
		{

		}
		break;
	}
}

void World::buildScene()
{
	// Initialize all the layers in the game


	switch( m_currentState )
	{
	case GameState::MainMenu:
		{
			std::unique_ptr< Text > title( new Text( m_fontManager.getResource( Font::Digital ) ) );
			m_title = title.get();
			m_title -> setString( "GALACTIC \t\t\t DEFENDER" );
			m_title -> setSize( 50 );
			m_title -> setColor( sf::Color::Cyan );
			m_title -> setOffset( 15, m_spawnPosition.y - 420 );
			m_menuGraph.attachChild( std::move( title ) );

			int count = 0;
			for(Button*& b : m_buttons)
			{
				if(count == 0)
				{
					std::unique_ptr< Button > buttons(new Button(Button::Type::BUTTON,m_textureManager,m_fontManager,"EXIT"));
					b = buttons.get();
					b->setPosition(m_spawnPosition);
					m_menuGraph.attachChild(std::move(buttons));
				}

				else
				{
					std::unique_ptr< Button > buttons(new Button(Button::Type::BUTTON,m_textureManager,m_fontManager,"START"));
					b = buttons.get();
					b->setPosition(m_spawnPosition);
					m_menuGraph.attachChild(std::move(buttons));
				}

				count++;
			}

		}
		break;



	case GameState::Game:
		{
			m_elapsed = sf::Time::Zero;
			m_killCounter = 0;
			m_themeMusic.setPitch( 1.0f );

			// Create the background
			for ( int i = 0; i < Layer::LayerCount; i++ )
			{
				SceneNode::NodePtr layer( new SceneNode() );

				m_sceneLayers[ i ] = layer.get();

				m_sceneGraph.attachChild( std::move( layer ) );
			}

			sf::Texture& texture = m_textureManager.getResource( Texture::Space );
			sf::IntRect  textureRect( m_worldBounds );
			texture.setRepeated( true );

			std::unique_ptr< SpriteNode > background( new SpriteNode( texture, textureRect ) );
			background -> setPosition( m_worldBounds.left, m_worldBounds.top );
			m_sceneLayers[ Layer::Background ] -> attachChild( std::move( background ) );

			// Create the player

			std::unique_ptr< Ship > player( new Ship( Ship::Type::Player, m_textureManager ) );
			m_player = player.get();
			m_player -> setPosition( m_spawnPosition.x, Util::V_Height - ( m_player -> getSprite().getTexture() -> getSize().y / 2 ) - 1 );
			m_player -> getLaserSystem().setEmitter( m_spawnPosition.x, m_spawnPosition.y - ( m_player -> getSprite().getTexture() -> getSize().y / 2 ) );
			m_player -> setHealth( 100 );
			m_player -> getLaserSystem().init( m_textureManager.getResource( Texture::Laser ) );
			m_sceneLayers[ Layer::Air ] -> attachChild( std::move( player ) );

			// Create the Enemies

			for ( Ship*& s : m_enemies )
			{
				std::unique_ptr< Ship > enemies( new Ship( Ship::Type::Enemy, m_textureManager ) );
				s = enemies.get();
				s -> setPosition( m_spawnPosition );
				s -> getLaserSystem().setEmitter( s -> getPosition().x, s -> getPosition().y + ( s -> getSprite().getTexture() -> getSize().y / 2 ) );
				s -> getLaserSystem().init( m_textureManager.getResource( Texture::Laser ) );
				s -> getLaserSystem().setDelay( sf::milliseconds( 800 ) );
				s -> setHealth( 50 );
				m_sceneLayers[ Layer::Air ] -> attachChild( std::move( enemies ) );
			}
			for ( Ship*& s : m_enemies )
			{
				s ->setPosition(randomSpawner());
			}

			// Debug Info

#ifdef _DEBUG // Only executes below code in Debug mode, not in Release mode

			std::unique_ptr< Text > debug( new Text( m_fontManager.getResource( Font::Digital ) ) );
			m_debug = debug.get();
			m_debug -> setString( "X: \t\t\t\t\t Y: \t\t\t\t\t " );
			m_debug -> setSize( 25 );
			m_debug -> setOffset( 0.0f, 0.0f );
			m_sceneLayers[ Layer::GUI ] -> attachChild( std::move( debug ) );

#endif

			// Create GUI

			std::unique_ptr< Text > gameTime( new Text( m_fontManager.getResource( Font::Digital ) ) );
			m_gameTime = gameTime.get();
			m_gameTime -> setString( "0.0" );
			m_gameTime -> setSize( 25 );
			m_gameTime -> setOffset( Util::V_Width / 2 - ( m_gameTime -> getText().getCharacterSize() ), 0.0f );
			m_sceneLayers[ Layer::GUI ] -> attachChild( std::move( gameTime ) );

			std::unique_ptr< Text > health( new Text( m_fontManager.getResource( Font::Digital ) ) );
			m_health = health.get();
			m_health -> setString( "0" );
			m_health -> setSize( 30 );
			m_health -> setOffset( Util::V_Width - 55, 0.0f );
			m_sceneLayers[ Layer::GUI ] -> attachChild( std::move( health ) );

			std::unique_ptr<Text> score(new Text(m_fontManager.getResource(Font::Digital)));
			m_score = score.get();
			m_score ->setString("0");
			m_score ->setSize(25);
			m_score -> setOffset(0.0f,0.0f);
			m_sceneLayers[Layer::GUI] ->attachChild(std::move(score));

			// Create Powerups

			int temp = 0;

			for( PowerUp*& p: m_powerUps )
			{
				if ( temp < 2 )
				{
					std::unique_ptr< PowerUp > powerUp( new PowerUp( m_textureManager.getResource( Texture::FireRate_PU ) ) );
					p = powerUp.get();
					float x = 0;
					float y = 0;
					randomPowerUpSpawner(x,y);
					p->setPosition(x,y);

					p->setType(PowerUp::Type::FireRate );

					m_sceneLayers[ Layer::Air ] -> attachChild( std::move( powerUp ) );
				}

				else
				{
					std::unique_ptr< PowerUp > powerUp( new PowerUp( m_textureManager.getResource( Texture::Repair_PU ) ) );
					p = powerUp.get();

					float x = 0;
					float y = 0;
					randomPowerUpSpawner(x,y);
					p->setPosition(x,y);

					p->setType( PowerUp::Type::Health );

					m_sceneLayers[ Layer::Air ] -> attachChild( std::move( powerUp ) );
				}

				temp++;
			}

			// Create the music and sounds

			m_laserSound.setBuffer( m_soundManager.getResource( Sound::Shoot ) );
			m_laserSound.setVolume( 20.0f );

			m_themeMusic.setLoop( true );
			m_themeMusic.play();

		}
		break;

	case GameState::GameOver:
		{
			m_camera.setCenter( m_spawnPosition );
			std::unique_ptr< Text > title( new Text( m_fontManager.getResource( Font::Digital ) ) );
			m_title = title.get();
			m_title -> setString( "GAME \t\t\t OVER" );
			m_title -> setSize( 50 );
			m_title -> setColor( sf::Color::Cyan );
			m_title -> setOffset( 100, m_spawnPosition.y - 420 );
			m_gameoverGraph.attachChild( std::move( title ) );

			int count = 0;
			for(Button*& b : m_buttons)
			{
				if(count == 0)
				{
					std::unique_ptr< Button > buttons(new Button(Button::Type::BUTTON,m_textureManager,m_fontManager,"QUIT"));
					b = buttons.get();
					b->setPosition(m_spawnPosition);
					m_gameoverGraph.attachChild(std::move(buttons));
				}

				else
				{
					std::unique_ptr< Button > buttons(new Button(Button::Type::BUTTON,m_textureManager,m_fontManager,"REPLAY"));
					b = buttons.get();
					b->setPosition(m_spawnPosition);
					m_gameoverGraph.attachChild(std::move(buttons));
				}

				count++;
			}
		}
		break;
	}

}

void World::playerInput()
{
	sf::Vector2f velocity;

	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
	{
		velocity.x = -200.0f;
	}

	else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
	{
		velocity.x = 200.0f;
	}

	else
	{
		m_player -> setVelocity( 0.0f, 0.0f );
	}

	m_player -> setVelocity( velocity );

	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) )
	{
		m_player -> fire( m_laserSound );
	}
}

void World::enemyAI()
{
	for ( Ship*& s : m_enemies )
	{
		if ( s -> isVisible() )
		{
			if ( s -> getPosition().x < m_player -> getPosition().x + 10 && s -> getPosition().x > m_player -> getPosition().x - 10 )
			{
				s -> fire( m_laserSound );
			}
		}
	}
}

void World:: collisionCheck()
{
	// Player Laser vs. Enemy collision check

	for ( auto iter = 0; iter < m_player -> getLaserSystem().getParticles().size(); iter++ )
	{
		if ( m_player -> getLaserSystem().getParticles()[ iter ].isAlive() )
		{
			for ( Ship*& s : m_enemies )
			{
				if ( s -> getRect().intersects( m_player -> getLaserSystem().getParticles()[ iter ].getRect() ) )
				{
					m_player -> getLaserSystem().getParticles()[ iter ].setAlive( false );

					std::unique_ptr< Explosion > explosion( new Explosion( m_textureManager.getResource( Texture::Explosion ) ) );
					m_explosions.push_back( explosion.get() );
					m_explosions[ m_explosions.size() - 1 ] -> setPosition( s -> getPosition() );
					m_sceneLayers[ Layer::Air ] -> attachChild( std::move( explosion ) );

					s -> setPosition( randomSpawner() );

					m_killCounter++;
				}
			}
		}
	}

	// Player vs. Enemy Laser collision check

	for ( int i = 0; i < m_enemies.size(); i++ )
	{
		for ( int j = 0; j < m_enemies[ i ] -> getLaserSystem().getParticles().size(); j++ )
		{
			if ( m_enemies[ i ] -> getLaserSystem().getParticles()[ j ].isAlive() )
			{
				if ( m_enemies[ i ] -> getLaserSystem().getParticles()[ j ].getRect().intersects( m_player -> getRect() ) )
				{
					// Destroy Player

					m_enemies[ i ] -> getLaserSystem().getParticles()[ j ].setAlive( false );

					m_player -> setHealth( m_player -> getHealth() - 3 );
				}
			}
		}

		// Player vs. Enemy collision check

		if ( m_enemies[ i ] -> getRect().intersects( m_player -> getRect() ) )
		{
			// Destroy Player
		}
	}

	// Power Up vs Player Collision

	for ( int i = 0; i < m_powerUps.size(); i++)
	{
		if ( m_player -> getRect().intersects( m_powerUps[ i ] -> getRect() ) )
		{
			if ( !m_powerUps[ i ] -> isCollected() )
			{
				if ( m_powerUps[ i ] -> getType() == PowerUp::Type::FireRate )
				{
					m_powerUps[ i ]  -> setCollected( true );
					m_player -> getLaserSystem().decreaseDelay( sf::milliseconds( 100 ) );

				}

				else if ( m_powerUps[ i ] -> getType() == PowerUp::Type::Health )
				{
					m_powerUps[ i ] -> setCollected( true );
					m_player -> modHealth( 15 );
				}
			}
		}
	}
}

sf::Vector2f World::randomSpawner()
{
	float temp  = 0;
	float temp2 = 0;

	setRandomVard( temp, temp2 );
	int i = 0;
	for ( i = 0; i < m_enemies.size(); i++)
	{
		bool checkx1 = //temp + m_textureManager.getResource(Texture::Enemy).getSize().x/2  > m_enemies[i] ->getPosition().x -  m_textureManager.getResource(Texture::Enemy).getSize().x/2;    
			temp  - m_textureManager.getResource(Texture::Enemy).getSize().x/2 > m_enemies[i] -> getPosition().x - m_textureManager.getResource(Texture::Enemy).getSize().x/2;
		bool checkx2 =  //temp2 -  m_textureManager.getResource(Texture::Enemy).getSize().y/2 < m_enemies[i] ->getPosition().y -  m_textureManager.getResource(Texture::Enemy).getSize().y/2;
			temp  - m_textureManager.getResource(Texture::Enemy).getSize().x/2 < m_enemies[i] -> getPosition().x + m_textureManager.getResource(Texture::Enemy).getSize().x/2;
		bool checkx3 = //temp2 +  m_textureManager.getResource(Texture::Enemy).getSize().y/2 > m_enemies[i]->getPosition().y +  m_textureManager.getResource(Texture::Enemy).getSize().y/2;
			temp  + m_textureManager.getResource(Texture::Enemy).getSize().x/2 > m_enemies[i] -> getPosition().x - m_textureManager.getResource(Texture::Enemy).getSize().x/2;
		bool checkx4 =// temp -  m_textureManager.getResource(Texture::Enemy).getSize().x/2 < m_enemies[i]->getPosition().y +  m_textureManager.getResource(Texture::Enemy).getSize().x/2;
			temp  + m_textureManager.getResource(Texture::Enemy).getSize().x/2 < m_enemies[i] -> getPosition().x + m_textureManager.getResource(Texture::Enemy).getSize().x/2;

		bool checky1 = //temp2 -  m_textureManager.getResource(Texture::Enemy).getSize().y/2 < m_enemies[i]->getPosition().y -  m_textureManager.getResource(Texture::Enemy).getSize().y/2; 
			temp2 - m_textureManager.getResource(Texture::Enemy).getSize().y/2 > m_enemies[i] -> getPosition().y - m_textureManager.getResource(Texture::Enemy).getSize().y/2;
		bool checky2 =// temp2 +  m_textureManager.getResource(Texture::Enemy).getSize().y/2 > m_enemies[i]->getPosition().y +  m_textureManager.getResource(Texture::Enemy).getSize().y/2; 
			temp2 - m_textureManager.getResource(Texture::Enemy).getSize().y/2 < m_enemies[i] -> getPosition().y + m_textureManager.getResource(Texture::Enemy).getSize().y/2;


		bool checky3 = temp2 + m_textureManager.getResource(Texture::Enemy).getSize().y/2 > m_enemies[i] -> getPosition().y - m_textureManager.getResource(Texture::Enemy).getSize().y/2;
		bool checky4 = temp2 + m_textureManager.getResource(Texture::Enemy).getSize().y/2 < m_enemies[i] -> getPosition().y + m_textureManager.getResource(Texture::Enemy).getSize().y/2;

		bool col = /*(((checkx1) &&
				   (checkx2 || checkx3)) || ((checkx4) &&
				   checky1|| checky2));*/
				   ( ( ( checkx1 && checkx2 ) ||
				   ( checkx3 && checkx4 ) ) &&
				   ( ( checky1 && checky2 ) ||
				   ( checky3 && checky4 ) ) );

		if ( col ) 
		{
			i = 0;
			setRandomVard( temp,temp2 );
		}

	}

	return ( sf::Vector2f( temp, temp2 ) );
}

void World::setRandomVard( float& a, float& b )
{
	std::random_device rd;
	std::mt19937       eng( rd() );

	int tempxMin = m_player -> getSprite().getTextureRect().width / 2;
	int tempxMax = Util::V_Width - m_player ->getSprite().getTextureRect().width / 2 ;

	int tempyMin = m_camera.getCenter().y - ( Util::V_Height / 2 )  * 5;
	int tempyMax = m_camera.getCenter().y - ( Util::V_Height / 2);

	std::uniform_int_distribution<> distX( tempxMin, tempxMax );
	std::uniform_int_distribution<> distY( tempyMin, tempyMax );

	a = distX( eng );
	b = distY( eng );
}

void World::updateExplosions()
{
	for ( auto iter = m_explosions.begin(); iter != m_explosions.end(); iter++ )
	{
		if ( (*iter) -> getAnimator().isDoneAnimating() )
		{
			m_sceneLayers[ Layer::Air ] -> detachChild( **iter );
			m_explosions.erase( iter );
			break;
		}
	}
}

void World::updateMainMenu( sf::Time dt )
{
	
	for(int i =0; i< m_buttons.size(); i++)
	{
		if(i == 0)
		{
			m_buttons[i]->setPosition(Util::V_Width/2, (Util::V_Height/2 + 100));
		}else{
			m_buttons[i]->setPosition(Util::V_Width/2, (Util::V_Height/2 - 100));
		}
	}

	CheckButtonPress("START");

	m_menuGraph.update( dt, m_camera );
}

void World::updateGame( sf::Time dt )
{
	m_elapsed += dt;

	m_gameTime -> setString( toString( m_elapsed.asSeconds() ) ); 
	m_health   -> setString( toString( m_player -> getHealth() ) );
	m_score    -> setString( "SCORE:\t\t\t " + toString( m_killCounter ) );

	if ( m_camera.getCenter().y - ( Util::V_Height / 2 ) <= -Util::LevelLength )
	{
		m_camera.move( 0.0f, 0.0f );
	}

	else
	{
		m_camera.move( 0.0f, Util::CameraSpeed * dt.asSeconds() );
	}

	m_player -> move( 0.0f, Util::CameraSpeed * dt.asSeconds() );

	playerInput();
	enemyAI();
	collisionCheck();

	for ( Ship*& e : m_enemies )
	{
		if ( e -> getType() == Ship::Type::Enemy )
		{
			if ( e -> getPosition().y - ( e -> getSprite().getTexture() -> getSize().y / 2 ) > m_camera.getCenter().y + ( Util::V_Height / 2 ) )
			{
				e -> setPosition( randomSpawner() );
			}
		}
	}

	m_sceneGraph.update( dt, m_camera );
	updateExplosions();


	if ( m_player->getHealth() <= 0 || m_player->getPosition().y <= -(Util::LevelLength))
	{

		m_init = false;
		m_currentState = GameState::GameOver;
	}

#ifdef _DEBUG // Only executes below code if in Debug mode, not in Release mode

	m_stream << "\n\n\nX: \t\t\t\t\t\t\t" << m_player -> getPosition().x << "\nY : \t\t\t\t\t\t\t" << m_player -> getPosition().y;
	m_debug -> setString( m_stream.str() );
	m_stream.str( std::string() );

#endif
	
}

void World::updateGameOver( sf::Time dt )
{
	m_themeMusic.setPitch( 0.7f );

	for(int i =0; i< m_buttons.size(); i++)
	{
		if(i == 0)
		{
			m_buttons[i]->setPosition(Util::V_Width/2, (Util::V_Height/2 + 100));
		}
		
		else
		{
			m_buttons[i]->setPosition(Util::V_Width/2, (Util::V_Height/2 - 100));
		}
	}

	CheckButtonPress("REPLAY");

	m_gameoverGraph.update( dt, m_camera );
}

std::string World::toString( int num )
{
	std::stringstream ss;

	ss << num;

	return ss.str();
}

std::string World::toString( float num )
{
	std::stringstream ss;

	ss.precision( 3 );
	ss << num;

	return ss.str();
}

void World::randomPowerUpSpawner(float& _a, float& _b)
{
	std::random_device rd;
	std::mt19937       eng( rd() );

	int tempxMin = m_player->getSprite().getTextureRect().width/2;
	int tempxMax = Util::V_Width - m_player->getSprite().getTextureRect().width/2;
	int tempyMin =  m_player->getPosition().y - Util::LevelLength;
	int tempyMax = m_player->getPosition().y - (Util::V_Height * 2);

	std::uniform_int_distribution<> distX( tempxMin, tempxMax );
	std::uniform_int_distribution<> distY( tempyMin, tempyMax );
	_a =distX( eng );
	_b =distY( eng );
}

void World::CheckButtonPress( const std::string& s1 )
{
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i pos = sf::Mouse::getPosition(m_window);
		for(Button*& b: m_buttons)
		{
			std::cout << "Mouse Pos: " << pos.x << " , " <<pos.y << " " <<std::endl <<" Button POS " <<  b->getPosition().x << " , " << b->getPosition().y << std::endl;
			if(pos.x > b->getPosition().x - m_textureManager.getResource(Texture::Button).getSize().x/2 &&
				pos.x < b->getPosition().x + m_textureManager.getResource(Texture::Button).getSize().x/2 &&
				pos.y > b->getPosition().y - m_textureManager.getResource(Texture::Button).getSize().y/2 &&
				pos.y < b->getPosition().y + m_textureManager.getResource(Texture::Button).getSize().y/2)
			{
				if(b-> getText() -> getText().getString() == s1 )
				{
					m_currentState = GameState::Game;
					m_init = false;
				}else{
					m_window.close();
				}
			}
		}

	}
}