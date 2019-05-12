#include"game.h"
#include"Graphic/window.h"
#include"EskeletorCreator.h"
#include"TurretCreator.h"
#include"ShotGliderCreator.h"
#include"GliderCreator.h"
#include"ScrollingBackground.h"
#include"EnemyBossCreator.h"
#include"Snail.h"
#include"Camera.h"
#include"MovingPlatform.h"
#include"WaterPlatform.h"
#include"LadderPlatform.h"
#include"DeadSprite.h"
#include"MoreEnemies/CantBeHurtEnemy.h"
#include"MoreEnemies/ClosedAttackEnemy.h"
#include"MoreEnemies/FarAttackEnemy.h"
#include"CheckPointObject.h"
#include"GainPlayerLife.h"

float floatFPS = FPS;
float deltaTime = 1.0f / floatFPS;         //the amount of time between two frames --> is used in Platformer :: update()

namespace HDT_engine
{
	namespace Game
	{
		//Game class members...
		game::game()
		{

			m_renderer = Graphic::TextureManager::Instance()->get_renderer();
			is_close = false;

			m_gameWidth = 640;
			m_gameHeight = 360;

			scrollVelocity = -1;
		}

		game::~game()
		{
			SDL_Quit();
		}

		void game::Init() 
		{
			Graphic::Window::Instance();                   //we actually calling the Instance() function which Init every thing
														   //but we still assume it as an object

			//Player system
			m_PlayerLives = PLAYERLIVESMAX;

			Graphic::TextureManager::Instance()->load("src/assets/PlayerLives.png", "PLAYERLIVES",   //loading PlayerLives texture
													  Graphic::TextureManager::Instance()->get_renderer());

			///avoid black line background --> when scrolling backgrounds connect --> due to my own equation and display of the backgrounds
			///are type int --> there'll be some black line appear when two scrolling background do not connect
			///--> so I put this in the back instead of black default of SDL --> render in PlayState
			Graphic::TextureManager::Instance()->load("src/assets/YaranaicaBackground/AvoidBlackLineBackGround.png", "AVOIDBLACKLINEBACKGROUND",   //loading PlayerLives texture
													   Graphic::TextureManager::Instance()->get_renderer());

			//bosses system
			//m_BossLevel_1_Lives = BOSSLEVEL_1_LIVESMAX;
			//m_BossLevel_2_Lives = BOSSLEVEL_2_LIVESMAX;

			//level system
			Level_Complete = false;

			//ObjectCreator loading
			GameObjectFactory::Instance()->registerCreator("Player",new PlayerCreator());
			GameObjectFactory::Instance()->registerCreator("MenuButton",new MenuButtonCreator());
			GameObjectFactory::Instance()->registerCreator("AnimatedGraphic",new AnimatedGraphicCreator());
			GameObjectFactory::Instance()->registerCreator("Enemy", new EnemyCreator());
			GameObjectFactory::Instance()->registerCreator("Eskeletor", new EskeletorCreator());
			GameObjectFactory::Instance()->registerCreator("Turret", new TurretCreator());
			GameObjectFactory::Instance()->registerCreator("ShotGlider", new ShotGliderCreator());
			GameObjectFactory::Instance()->registerCreator("Glider", new GliderCreator());
			GameObjectFactory::Instance()->registerCreator("ScrollingBackground", new ScrollingBackgroundCreator());
			GameObjectFactory::Instance()->registerCreator("EnemyBoss", new EnemyBossCreator());
			GameObjectFactory::Instance()->registerCreator("Snail", new SnailCreator());
			GameObjectFactory::Instance()->registerCreator("MovingPlatform",new MovingPlatformCreator());
			GameObjectFactory::Instance()->registerCreator("WaterPlatform",new WaterPlatformCreator());
			GameObjectFactory::Instance()->registerCreator("LadderPlatform",new LadderPlatformCreator());
			GameObjectFactory::Instance()->registerCreator("DeadSprite",new DeadSpriteCreator());
			GameObjectFactory::Instance()->registerCreator("CheckPointObject",new CheckPointObjectCreator());
			GameObjectFactory::Instance()->registerCreator("GainPlayerLife",new GainPlayerLifeObjectCreator());

			//more Enemies
			GameObjectFactory::Instance()->registerCreator("CantBeHurtEnemy",new CantBeHurtEnemyCreator());
			GameObjectFactory::Instance()->registerCreator("ClosedAttackEnemy",new ClosedAttackEnemyCreator());
			GameObjectFactory::Instance()->registerCreator("FarAttackEnemy",new FarAttackEnemyCreator());

			//Sound loading
			/*
			SOUND::SoundManager::Instance()->Load("src/assets/sounds/Explosion.wav", SOUND::AudioType::Sound_SFX, "Explosion");
			SOUND::SoundManager::Instance()->Load("src/assets/sounds/Blip_Select3.wav", SOUND::AudioType::Sound_SFX, "Blip_Select3");
			SOUND::SoundManager::Instance()->Load("src/assets/sounds/PlayerShoot.wav", SOUND::AudioType::Sound_SFX,"PlayerShoot");
			SOUND::SoundManager::Instance()->Load("src/assets/sounds/EnemyBossSword.wav", SOUND::AudioType::Sound_SFX, "EnemyBossSword");
			*/

			SOUND::SoundManager::Instance()->Load("src/assets/sounds/BirdSound.wav", SOUND::AudioType::Sound_SFX, "BIRDSOUND"); 
			SOUND::SoundManager::Instance()->Load("src/assets/sounds/BackgroundMusic2.wav", SOUND::AudioType::Sound_Music, "BACKGROUNDMUSIC2");    
			SOUND::SoundManager::Instance()->Load("src/assets/sounds/CheckPointSound.wav", SOUND::AudioType::Sound_SFX, "CHECKPOINTSOUND");
			SOUND::SoundManager::Instance()->Load("src/assets/sounds/ClickButtonSound.wav", SOUND::AudioType::Sound_SFX, "CLICKBUTTONSOUND");
			SOUND::SoundManager::Instance()->Load("src/assets/sounds/ClosedEnemyAttack.wav", SOUND::AudioType::Sound_SFX, "CLOSEDENEMYATTACKSOUND");
			SOUND::SoundManager::Instance()->Load("src/assets/sounds/EnemyFuckedSound.wav", SOUND::AudioType::Sound_SFX, "ENEMYFUCKEDSOUND");
			SOUND::SoundManager::Instance()->Load("src/assets/sounds/FarEnemyAttackSound.wav", SOUND::AudioType::Sound_SFX, "FARENEMYATTACKSOUND");
			SOUND::SoundManager::Instance()->Load("src/assets/sounds/MainMenuBackgroundMusic.wav", SOUND::AudioType::Sound_Music, "MAINMENUBACKGROUNDMUSIC");  //
			SOUND::SoundManager::Instance()->Load("src/assets/sounds/PickUpGainPlayerLifeSound.wav", SOUND::AudioType::Sound_SFX, "PICKUPGAINPLAYERLIFESOUND");
			SOUND::SoundManager::Instance()->Load("src/assets/sounds/PlayerAttackSound.wav", SOUND::AudioType::Sound_SFX, "PLAYERATTACKSOUND");
			SOUND::SoundManager::Instance()->Load("src/assets/sounds/PlayerDyingSound1.wav", SOUND::AudioType::Sound_SFX, "PLAYERDYINGSOUND1");
			SOUND::SoundManager::Instance()->Load("src/assets/sounds/PlayerDyingSound2.wav", SOUND::AudioType::Sound_SFX, "PLAYERDYINGSOUND2");
			SOUND::SoundManager::Instance()->Load("src/assets/sounds/PlayerFootStepSound.wav", SOUND::AudioType::Sound_SFX, "PLAYERFOOTSTEPSOUND");
			SOUND::SoundManager::Instance()->Load("src/assets/sounds/PlayerJumpSound.wav", SOUND::AudioType::Sound_SFX, "PLAYERJUMPSOUND");
			SOUND::SoundManager::Instance()->Load("src/assets/sounds/Explosion.wav", SOUND::AudioType::Sound_SFX, "EXPLOSION");

			//bullets textureloading
		

			Graphic::TextureManager::Instance()->load("src/assets/Bullets/Bullet1.png", "BULLET1",
													  Graphic::TextureManager::Instance()->get_renderer());

			Graphic::TextureManager::Instance()->load("src/assets/Bullets/Bullet2.png", "BULLET2",
													  Graphic::TextureManager::Instance()->get_renderer());


			//LOADING SOME DEADYARANAICA texture

			
			Graphic::TextureManager::Instance()->load("src/assets/DeadYaranaica/DeadYaranaica_General.png", "DEADYARANAICA_GENERAL",
													  Graphic::TextureManager::Instance()->get_renderer());

			Graphic::TextureManager::Instance()->load("src/assets/DeadYaranaica/DeadYaranaica_Naruto.png", "DEADYARANAICA_NARUTO",
													  Graphic::TextureManager::Instance()->get_renderer());

			Graphic::TextureManager::Instance()->load("src/assets/DeadYaranaica/DeadYaranaica_PinkRanger.png", "DEADYARANAICA_PINKRANGER",
													  Graphic::TextureManager::Instance()->get_renderer());

			Graphic::TextureManager::Instance()->load("src/assets/DeadYaranaica/DeadYaranaica_Sasuke.png", "DEADYARANAICA_SASUKE",
													  Graphic::TextureManager::Instance()->get_renderer());

			Graphic::TextureManager::Instance()->load("src/assets/DeadYaranaica/DeadYaranaica_SpiderMan.png", "DEADYARANAICA_SPIDERMAN",
													  Graphic::TextureManager::Instance()->get_renderer());


			//FUCKING EFFECT TEXTURE LOADING
			Graphic::TextureManager::Instance()->load("src/assets/FuckingEffect/TestFuckingEffect.png", "TESTFUCKINGEFFECT",
													   Graphic::TextureManager::Instance()->get_renderer());

			Graphic::TextureManager::Instance()->load("src/assets/FuckingEffect/FuckingEffect.png", "FUCKINGEFFECT",
													   Graphic::TextureManager::Instance()->get_renderer());


			FSM::GameStateMachine::Instance()->changeState(new FSM::MenuState);        //after init everything --> get to menu state first
			
		}

		void game::render() 
		{
			FSM::GameStateMachine::Instance()->render();       //just copy to renderer
			
			Graphic::Window::Instance()->Render();             //present to renderer of the window
		}

		void game::update() //update math, vector and animation --->GAMESTATES---->LEVELS--->LAYERS---->OBJECTS
		{

			Game::Camera::Instance()->Update();   ///the whole game use camera


			FSM::GameStateMachine::Instance()->update();       //--> update to the CURRENT STATE --> update the objects of that state

			/*
			//after the boss level 1 was defeated(lives == 0) in that update
			
			if (m_BossLevel_1_Lives == 0)                     //the MAIN purpose of this is just to "anncounce" TO Player
														      //that the current Level is completed --> and it's time to..
															  //game::GoHigherLevel() in Player Update()
			{
				Level_Complete = true;                        //after this is true --> next update() loop --> go to Player Object
															  //Player object get the "signal" (in Player.cpp) -->Level_Complete!!!
				
				m_BossLevel_1_Lives = BOSSLEVEL_1_LIVESMAX;   //set again or else the game will keep LEVELCOMPLETE == true
															  //-->Player get the signal and try to push the new state again
															  //-->keep implemeting GO HIGHER LEVEL() :((
			}

			if (m_BossLevel_2_Lives == 0)                     //after this is true --> next update() loop --> go to Player Object
															  //Player object get the "signal" (in Player.cpp) -->Level_Complete!!!
			{
				Level_Complete = true;

				m_BossLevel_2_Lives = BOSSLEVEL_2_LIVESMAX;   //set again or else the game will keep LEVELCOMPLETE == true
															  //-->Player get the signal and try to push the new state again
															  //-->keep implemeting GO HIGHER LEVEL() :((
			}
			
			*/

			///RIGHT NOW LEVEL-COMPLETE is set When Player touch the final CheckPoint --> go CheckPointObject for more detail

			GoHigherLevel_AvoidVectorError();
		}

		void game::handleEvents()
		{
			INPUT::InputHandler::Instance()->update();              //SDL Poll event is called in here
																	//every input that is related to keyboard STATE(not event)..
																	//has to be called below the SDL Poll event(SDL pump event)

			if (INPUT::InputHandler::Instance()->get_close_info())  
				is_close = true;									
			
		}

		bool game::close()
		{
			return is_close;
		}

		game* game::instance = NULL;

		game* game::Instance()
		{
			if (instance == NULL)
			{
				instance = new game();
			}
			return instance;
		}

		int game::Get_GameWidth()
		{
			return m_gameWidth;
		}

		int game::Get_GameHeight()
		{
			return m_gameHeight;
		}

		int game::Get_ScrollVelocity()
		{
			return scrollVelocity;
		}

		//Level system
		bool game::Get_Level_Complete()
		{
			return Level_Complete;
		}

		void game::Set_Level_Complete(bool Input_)
		{
			Level_Complete = Input_;
		}

		void game::GoHigherLevel()                       //this is only implemented when the current level complete --> when the boss of that
														 //level BOSSLIVES == 0
		{
			b_GoHigherLevel = true;
		}

		void game::GoHigherLevel_AvoidVectorError()
		{
			if (b_GoHigherLevel)
			{
				int MAX_LEVELS_ = MAX_LEVELS;
				if (m_currentLevel == (MAX_LEVELS_ - 1))     //PLAYED ALL THE LEVELS (m_currentLevel is index 0 and 1)
				{
					FSM::GameStateMachine::Instance()->changeState(new FSM::GameOverState());
					Level_Complete = false;      //to avoid Get_LevelComplete in Player --> and go to this section again-->keep change new
												 //gameoverstate :(((
					m_currentLevel = 0;			 //--> so we can play again from the start
				}
				else
				{
					m_currentLevel++;            //look into the PlayState::Enter() to know more about this
												 //after currentLevel++ which means loading file index++ in PlayState
												 //have to change new PlayState to get this feature

					Level_Complete = false;      //ready for new level

					FSM::GameStateMachine::Instance()->changeState(new FSM::PlayState());
				}
			}
			
			///after set all things --> reset
			b_GoHigherLevel = false;
		}

		//Player system
		void game::Set_PlayerLives(int m_PlayerLives_)
		{
			this->m_PlayerLives = m_PlayerLives_;
		}

		int game::Get_PlayerLives()
		{
			return this->m_PlayerLives;
		}

		//BOSSES SYSTEM
		int game::Get_CurrentBossLevelLives()
		{
			switch (m_currentLevel)
			{
			case 0: return m_BossLevel_1_Lives; break;        //current level : 1
			case 1: return m_BossLevel_2_Lives; break;		  //current level : 2
				//right now only two cases
			}
		}

		void game::Set_CurrentBossLevelLives(int input_)
		{
			switch (m_currentLevel)
			{
			case 0: m_BossLevel_1_Lives = input_ ; break;   //level 1
			case 1: m_BossLevel_2_Lives = input_ ; break;   //level 2
				//right now only two cases
			}
		}
	}
}