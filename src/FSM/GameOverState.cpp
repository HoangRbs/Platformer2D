#include"GameOverState.h"
#include"PlayState.h"
#include"../Camera.h"
#include"../level/ObjectLayer.h"

namespace HDT_engine
{
	namespace FSM
	{
		
		bool GameOverState::GAMEOVER_TO_MAIN = false;
		bool GameOverState::GAMEOVER_TO_RESTART = false;

		void GameOverState::update()
		{
			/*
			for (int i = 0; i < m_gameobjects.size(); i++)
			{
				if(m_gameobjects.at(i) != NULL)
					m_gameobjects.at(i)->update();
			}
			*/

			if (GAMEOVER_TO_MAIN)
			{
				FSM::GameStateMachine::Instance()->changeState(new FSM::MenuState);
			}
			else if (GAMEOVER_TO_RESTART)
			{
				FSM::GameStateMachine::Instance()->changeState(new FSM::PlayState());
			}
			else
			{
				if (GameOverLevel != NULL)
				{
					GameOverLevel->Update();
				}
			}

		}

		void GameOverState::render()
		{
			/*
			for (int i = 0; i < m_gameobjects.size(); i++)
			{
				m_gameobjects.at(i)->draw();
			}
			*/

			if (GameOverLevel != NULL)
			{
				GameOverLevel->Render();
			}
		}

		bool GameOverState::Enter()
		{
			SOUND::SoundManager::Instance()->PlayMusic("MAINMENUBACKGROUNDMUSIC", -1);

			Game::GameObjectFactory::Instance()->registerCreator("MenuButton", new Game::MenuButtonCreator);
			
			/*
			GameStateGeneral::m_StateParser.ParseState("src/FSM/StateParser/PARSESTATE.xml",
														GameOverStateID,
														&m_gameobjects,
														&m_Textures_ID);
			*/

			LEVEL::LevelParser tempGameOverLevelParser;
			GameOverLevel = tempGameOverLevelParser.ParseLevel("src/assets/GameOverState.tmx");

			m_callBacks.push_back(NULL);					 //at index 0 (callBackID = 0) --> NULL
			m_callBacks.push_back(GameOverToMain);			 //index 1(callBackID = 1)-->MainMenu
			m_callBacks.push_back(GameOverToRestart);		 //index 2(callBackID = 2)-->Restart

			SetCallBacks();          //connecting all the *callback feature for buttons

			//CAMERA
			Game::Camera::Instance()->setTargetInfo(NULL, NULL);

			cout << "entering gameover state" << endl;
			return true;
		}

		bool GameOverState::Exit()
		{
			for (int i = 0; i < m_gameobjects.size(); i++)
			{
				//m_gameObjects.at(i)->clean();
				delete m_gameobjects.at(i);
			}
			m_gameobjects.clear();

			Graphic::TextureManager::Instance()->clearFromTextureMap("GAMEOVER");
			Graphic::TextureManager::Instance()->clearFromTextureMap("RESTART");
			Graphic::TextureManager::Instance()->clearFromTextureMap("MAINMENU");   

			GAMEOVER_TO_MAIN = false;
			GAMEOVER_TO_RESTART = false;

			///LEVEL
			if (GameOverLevel != NULL)
			{
				GameOverLevel->Clean();
			}

			cout << "exitting game over state" << endl;
			return true;
		}

		std::string GameOverState::get_StateID()
		{
			return GameOverStateID;
		}


		void GameOverState::SetCallBacks()
		{
			/*
			for (int i = 0; i < m_gameobjects.size(); i++)
			{
				if (dynamic_cast<Game::MenuButton*>(m_gameobjects[i]))   //if it is pointing MenuButton type?
				{
					Game::MenuButton* temp = dynamic_cast<Game::MenuButton*>(m_gameobjects[i]);

					temp->SetCallBack(m_callBacks[temp->getCallBackID()]);
				}
			}
			*/

			for (int i = 0; i < GameOverLevel->Get_Layers()->size(); i++)
			{
				if (dynamic_cast<LEVEL::ObjectLayer*>(GameOverLevel->Get_Layers()->at(i)))
				{
					LEVEL::ObjectLayer* tempObjectLayer = dynamic_cast<LEVEL::ObjectLayer*>(GameOverLevel->Get_Layers()->at(i));

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

		void GameOverState::GameOverToMain()
		{

			//FSM::GameStateMachine::Instance()->popState();   //pop the current game overstate state
			GAMEOVER_TO_MAIN = true;
			//FSM::GameStateMachine::Instance()->changeState(new FSM::MenuState);       //change the MenuState and the saving Playstate
		}

		void GameOverState::GameOverToRestart()
		{
			GAMEOVER_TO_RESTART = true;
			//FSM::GameStateMachine::Instance()->changeState(new FSM::PlayState());
		}
	}
}