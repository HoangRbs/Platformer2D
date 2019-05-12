
#include"PlayState.h"
#include"../Player.h"
#include"../game.h"
#include"../BulletHandler.h"
#include"../Bullet.h"
#include"../Camera.h"
#include"../level/AnimatedTiles.h"
#include"../MoreEnemies/DeadYaranaicaManager.h"
#include"../ShowFuckingEffect.h"

namespace HDT_engine
{
	namespace FSM
	{
		//THIS IS HOW YOU GONNA PLAY IT SAFE --> IF DON'T DO THIS --> MESS UP WITH MEMORY --> YOU'LL BURN
		//WHEN CHANGING A NEW STATE --> ALL THE m_gameObjects WILL NO LONGER EXIST --> AND ITS SIZE() == 0 --> WE'LL gonna use this to Play it safe
		//and I had an idea -->to be safer --> why not set the SIZE() == 0 manually (in the callBack function )---> SAFER
		//--> look at SAFE MEMORY USAGE in PlayState.h   --> we're gonna pretend SIZE since we can't control directly --> just like bool SAFEZONE
		//--->but this is more specific WHY the program STOPPED

		void PlayState::update()
		{

			if (Game::game::Instance()->Get_PlayerLives() == 0)
			{
				FSM::GameStateMachine::Instance()->changeState(new FSM::GameOverState());
				int temp = PLAYERLIVESMAX;
				Game::game::Instance()->Set_PlayerLives(temp);
				PLAYSTATE_GAMEOBJECTS_SIZE = 0;
			}

			if (INPUT::InputHandler::Instance()->is_thiskey_pressed(SDL_SCANCODE_ESCAPE))
			{
				FSM::GameStateMachine::Instance()->pushState(new PausedState);
			}

			if (PLAYSTATE_GAMEOBJECTS_SIZE == 0)                 //this is just for testing
			{ 
				cout << "no more PlayState" << endl;
			}

			if (PLAYSTATE_GAMEOBJECTS_SIZE != 0)                
			{
				Game::DeadYaranaicaManager::Instance()->YaranaicasUpdate();

				//since we're treating bullets in the gamestate like gameobjects --> we're gonna update here
				
				
				Game::BulletHandler::Instance()->UpdateBullets();      //this gonna update all the ADDED bullets(might be ADDED SOMEWHERE ELSE)
																	   //this also can manage when to delete those bullets
																	   //so no need to worry
				
				level->Update();  //we updated bullets above --> so we're gonna check collision inside this function
				                  //this not gonna get our program run slow
				
				Game::UpdateFuckingEffect();
			}

		}

		void PlayState::render()
		{
			if (PLAYSTATE_GAMEOBJECTS_SIZE != 0)
			{
				///avoid black line background --> always render first
				Graphic::TextureManager::Instance()->drawFrame("AVOIDBLACKLINEBACKGROUND",0,0,640,360,
																Game::game::Instance()->Get_GameWidth(),
																Game::game::Instance()->Get_GameHeight(),
																0,0,0,255);

				level->Render();

				Game::BulletHandler::Instance()->DrawBullets();

				Game::DeadYaranaicaManager::Instance()->YaranaicasDraw();

				for (int i = 0; i < Game::game::Instance()->Get_PlayerLives(); i++) //drawing PlayerLives texture
				{
					Graphic::TextureManager::Instance()->drawFrame("PLAYERLIVES", i * 32, 0, 32, 32, 32, 32, 0, 0, 0, 190);
				}

				Game::DrawFuckingEffect();
			}
		}

		bool PlayState::Enter()
		{
			//set Player LIVES max again when enter a new PlayState
			int temp = PLAYERLIVESMAX;
			Game::game::Instance()->Set_PlayerLives(temp);

			//SAVING LEVEL FILE (LEVEL DESIGN) PATH
			LevelFilePath.push_back(std::string("src/assets/LEVEL.tmx"));          //WE'RE TESTING WITH NO TMX FILE
			//LevelFilePath.push_back(std::string("src/assets/LEVEL2.tmx")); --> right now ew only use one level

			//creating level
			LEVEL::LevelParser m_LevelParser;
			//every time we change current level in game-->use it ad index to load file
			
			level = m_LevelParser.ParseLevel(LevelFilePath[Game::game::Instance()->GetCurrentLevel()].c_str());
			//TESTING :))))))))
				//level = m_LevelParser.ParseLevel(LevelFilePath[1].c_str());
				//level = m_LevelParser.ParseLevel(LevelFilePath[0].c_str());

			//prepare m_callBacks
			m_callBacks.push_back(NULL);                  //callBackID = 0th

			cout << "Entering PlayState" << endl;

			SOUND::SoundManager::Instance()->PlayMusic("BACKGROUNDMUSIC2", -1);

			return true;
		}

		bool PlayState::Exit()
		{
			cout << "exitting play state" << endl;

			for (int i = 0; i < m_gameobjects.size(); i++)
			{
				//m_gameobjects.at(i)->clean();
				delete m_gameobjects.at(i);
			}

			m_gameobjects.clear();

			level->Clean();

			Graphic::TextureManager::Instance()->clearFromTextureMap("PLAYER");
			Graphic::TextureManager::Instance()->clearFromTextureMap("ENEMY");
			Graphic::TextureManager::Instance()->clearFromTextureMap("PLAYERDYING");
			Graphic::TextureManager::Instance()->clearFromTextureMap("ANIMATE_CAT");
			Graphic::TextureManager::Instance()->clearFromTextureMap("ENEMYDYING");
			Graphic::TextureManager::Instance()->clearFromTextureMap("GLIDER");
			Graphic::TextureManager::Instance()->clearFromTextureMap("SHOTGLIDER");
			Graphic::TextureManager::Instance()->clearFromTextureMap("ESKELETOR");
			Graphic::TextureManager::Instance()->clearFromTextureMap("TURRET");

			Game::BulletHandler::Instance()->BulletsClear();

			Game::DeadYaranaicaManager::Instance()->YaranaicasClear();

			//ANIMATED TILES
			LEVEL::AnimatedTiles::Instance()->Clean();


			SOUND::SoundManager::Instance()->HaltMusic();

			return true;
		}

		std::string PlayState::get_StateID()
		{
			return Play_StateID;
		}
		
		
		bool PlayState::CheckForCollision(Game::PlatformerObject* object_1, Game::PlatformerObject* object_2)
		{
			int LeftA = object_1->Get_position().get_x();  
			int RightA = object_1->Get_position().get_x() + object_1->Get_ScreenWidth();
			int TopA = object_1->Get_position().get_y(); 
			int BottomA = object_1->Get_position().get_y() + object_1->Get_ScreenHeight();

			int LeftB = object_2->Get_position().get_x();
			int RightB = object_2->Get_position().get_x() + object_2->Get_ScreenWidth();
			int TopB = object_2->Get_position().get_y(); 
			int BottomB = object_2->Get_position().get_y() + object_2->Get_ScreenHeight();

			if (BottomA <= TopB) return false;
			if (TopA >= BottomB) return false;
			if (RightA <= LeftB) return false;
			if (LeftA >= RightB) return false;

			return true;
		}
		
		void PlayState::Set_PlayState_SafeZone(bool input)
		{
			PlayState_SafeZone = input;
		}

		void PlayState::SetCallBacks()
		{
		
		}
	}
}