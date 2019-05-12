#include"MenuState.h"
#include"../game.h"
#include"../Camera.h"
#include"../level/ObjectLayer.h"

namespace HDT_engine
{
	namespace FSM
	{
		bool MenuState::MENU_TO_PLAY = false;

		void MenuState::update()
		{
			/*
			//update all the objects in this state
			for (int i = 0; i < m_gameobjects.size(); i++)
			{
				//IF GAMEOBJECT.AT(I) !=NULL --> we are going to do this due to our usage of changing the state and messing with memory
				if(m_gameobjects.at(i) != NULL)
					m_gameobjects.at(i)->update();
			}
			*/

			if (MENU_TO_PLAY == true)
			{
				GameStateMachine::Instance()->changeState(new PlayState());
			}
			else
			{
				if (MenuLevel != NULL)
					MenuLevel->Update();
			}

		}

		void MenuState::render()
		{
			/*
			//render sll the objects in this state
			for (int i = 0; i < m_gameobjects.size(); i++)
			{
				if(m_gameobjects.at(i) != NULL)
					m_gameobjects.at(i)->draw();
			}
			*/
			if(MenuLevel != NULL)
				MenuLevel->Render();
		}

		bool MenuState::Enter()
		{
			/*
			GameStateGeneral::m_StateParser.ParseState("src/FSM/StateParser/PARSESTATE.xml", menu_stateID, 
																							 &m_gameobjects,  //parse gameObjects
																							 &m_Textures_ID); //parse TextureID
			*/

			SOUND::SoundManager::Instance()->PlayMusic("MAINMENUBACKGROUNDMUSIC",-1);

			MENU_TO_PLAY = false;

			///LEVEL
			LEVEL::LevelParser tempMenuLevelParser;
			MenuLevel = tempMenuLevelParser.ParseLevel("src/assets/MenuState.tmx");


			m_callBacks.push_back(NULL);                 //at index 0 (callBackID = 0) --> NULL
			m_callBacks.push_back(MenuToPlay);			 //index 1(callBackID = 1)-->Play
			m_callBacks.push_back(MenuToExit);			 //index 2(callBackID = 2)-->Exit
			SetCallBacks();								 //before entering --> have to set the all the callback* to the "feature"


			//CAMERA
			Game::Camera::Instance()->setTargetInfo(NULL,NULL);

			std::cout << "entering menu state " << std::endl;
			return true;						//successfully loaded all -->can enter this menu state
		}

		bool MenuState::Exit()
		{

			//before exitting --> if going to PlayState --> have to INIT something first
			Game::game::Instance()->Set_ScrollingbackgroundStopped(false);

			int temp = PLAYERLIVESMAX;
			Game::game::Instance()->Set_PlayerLives(temp);

			//temp = BOSSLEVEL_1_LIVESMAX;
			//Game::game::Instance()->Set_CurrentBossLevelLives(temp);
			
		
			//temp = BOSSLEVEL_2_LIVESMAX;
			//Game::game::Instance()->Set_CurrentBossLevelLives(temp);

			Game::game::Instance()->SetCurrentLevel(0);       //back to level 1 in PlayState
			
			/*
			for (int i = 0; i < m_gameobjects.size(); i++)
			{
				m_gameobjects.at(i)->clean();
			}

			m_gameobjects.clear();
			*/

			Graphic::TextureManager::Instance()->clearFromTextureMap("PLAYBUTTON");
			Graphic::TextureManager::Instance()->clearFromTextureMap("EXITBUTTON");

			///level
			if(MenuLevel != NULL)
				MenuLevel->Clean();

			MENU_TO_PLAY = false;

			std::cout << "exiting menu state " << std::endl;
			return true;
		}

		std::string MenuState::get_StateID()                        //avoid duplicating in changing state
		{
			return menu_stateID;
		}

		void MenuState::SetCallBacks()
		{
			/*
			for (int i = 0; i < m_gameobjects.size(); i++)
			{
				if (dynamic_cast<Game::MenuButton*>(m_gameobjects[i]))     //if can be "dynamic cast" to (MenuButton*)
				{
					Game::MenuButton* temp = dynamic_cast<Game::MenuButton*>(m_gameobjects[i]);

					temp->SetCallBack(m_callBacks[temp->getCallBackID()]);
				}
			}
			*/

			for (int i = 0; i < MenuLevel->Get_Layers()->size(); i++)
			{
				if (dynamic_cast<LEVEL::ObjectLayer*>(MenuLevel->Get_Layers()->at(i)))
				{
					LEVEL::ObjectLayer* tempObjectLayer = dynamic_cast<LEVEL::ObjectLayer*>(MenuLevel->Get_Layers()->at(i));

					for (int j = 0; j < tempObjectLayer->Get_m_gameObjects()->size(); j++)
					{
						if (dynamic_cast<Game::MenuButton*>(tempObjectLayer->Get_m_gameObjects()->at(j)))  /// is the current Object in Level is 
																										   ///MenuButton* type
						{
							Game::MenuButton* tempMenuButton = dynamic_cast<Game::MenuButton*>(tempObjectLayer->Get_m_gameObjects()->at(j));

							tempMenuButton->SetCallBack(m_callBacks[tempMenuButton->getCallBackID()]);
						}
					}
				}
			}

		}

		void MenuState::MenuToPlay()                               //static member function --> that's why they take game Instance() (static too)
		{														   //in the book --> we'll gonna make gamestatemachine -> Instance
			cout << "Play Button clicked" << endl;
			//GameStateMachine::Instance()->Set_AnnounceToPlay(true); //after we click this --> this is always true !!! --> be careful
																	//the state machine will keeps changing the playstate if the current state
																	//is different
			//Game::game::Instance()->is_close = true;

			//GameStateMachine::Instance()->changeState(new PlayState());

			MENU_TO_PLAY = true;
		}

		void MenuState::MenuToExit()							   //static member function
		{
			cout << "Exit Button Clicked" << endl;
			//GameStateMachine::Instance()->Set_AnnounceToExit(true);
			Game::game::Instance()->is_close = true;                      //exit the whole game --> if(game::close())
		}
	}

}

