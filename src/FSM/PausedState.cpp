#include"PausedState.h"
#include"PlayState.h"
#include"GameStateMachine.h"
#include"../game.h"
#include"../Camera.h"
#include"../level/ObjectLayer.h"

namespace HDT_engine
{
	namespace FSM
	{
		bool PausedState::PAUSED_TO_MAIN = false;
		bool PausedState::PAUSED_TO_RESUME = false;

		void PausedState::update()
		{
			//since there is nothing special update
			//we do not need SafeZone here

			/*
			for (int i = 0; i < m_gameObjects.size(); i++)
			{
				m_gameObjects.at(i)->update();
			}
			*/

			if (PAUSED_TO_MAIN)
			{
				FSM::GameStateMachine::Instance()->popState();   //pop the current paused state

				FSM::GameStateMachine::Instance()->changeState(new FSM::MenuState);  //change the PlayState with MenuState
			}
			else if (PAUSED_TO_RESUME)
			{
				FSM::GameStateMachine::Instance()->popState();  //pop the current paused State and go to PlayState
			}
			else
			{
				if (PausedLevel != NULL)
				{
					PausedLevel->Update();
				}
			}
		}

		void PausedState::render()
		{
			/*
			for (int i = 0; i < m_gameObjects.size(); i++)
			{
				m_gameObjects.at(i)->draw();
			}
			*/

			if (PausedLevel != NULL)
			{
				PausedLevel->Render();
			}
		}

		bool PausedState::Enter()
		{

			SOUND::SoundManager::Instance()->PlayMusic("MAINMENUBACKGROUNDMUSIC", -1);

			Game::GameObjectFactory::Instance()->registerCreator("MenuButton", new Game::MenuButtonCreator);

			/*
			GameStateGeneral::m_StateParser.ParseState("src/FSM/StateParser/PARSESTATE.xml",
														PausedStateID,
														&m_gameObjects,
														&m_Textures_ID);

			*/

			///LEVEL
			LEVEL::LevelParser tempPausedLevelParser;
			PausedLevel = tempPausedLevelParser.ParseLevel("src/assets/PausedState.tmx");

			m_callBacks.push_back(NULL);                     //at index 0 (callBackID = 0) --> NULL
			m_callBacks.push_back(Paused_ToMain);			 //index 1(callBackID = 1)-->MainMeNu
			m_callBacks.push_back(Paused_ToResume);			 //index 2(callBackID = 2)-->Resume

			SetCallBacks();               //connecting all the callback* feature

			//CAMERA..................
			Game::Camera::Instance()->saveTargetPosPausedState(Game::Camera::Instance()->getTargetPos());  
			Game::Camera::Instance()->saveTargetVelPausedState(Game::Camera::Instance()->getTargetVel());
			//saving the current TargetPos first

			Game::Camera::Instance()->setTargetInfo(NULL,NULL);
			//set Target to NULL so Camera->getCamPosition == 0 when drawing button 
			//--> or else it will be "LECH" to one side

			cout << "Entering paused state " << endl;

			return true;
		}

		bool PausedState::Exit()
		{
			/*
			for (int i = 0; i < m_gameObjects.size(); i++)
			{
				//m_gameObjects.at(i)->clean();
				delete m_gameObjects.at(i);
			}
			m_gameObjects.clear();
			*/

			Graphic::TextureManager::Instance()->clearFromTextureMap("RESUMETOMAINMENU");
			Graphic::TextureManager::Instance()->clearFromTextureMap("RESUMETOGAME");

			//CAMERA...................  //going in to the Playstate again
			Game::Camera::Instance()->setTargetInfo(Game::Camera::Instance()->getSavedTargetPosPausedState(),
												Game::Camera::Instance()->getSavedTargetVelPausedState());
			//---> No NUll any more

			if (PausedLevel != NULL)      ///LEVEL
			{
				PausedLevel->Clean();
			}

			PAUSED_TO_MAIN = false;
			PAUSED_TO_RESUME = false;

			cout << "Exitting paused state " << endl;

			SOUND::SoundManager::Instance()->PlayMusic("BACKGROUNDMUSIC2",-1);

			return true;
		}

		string PausedState::get_StateID()
		{
			return PausedStateID;
		}

		void PausedState::Paused_ToMain()
		{
			Game::Camera::Instance()->setTargetInfo(NULL,NULL);

			int temp_2 = 0;  //so when we start a new PlayState --> it will load LEVEL_1.tmx(play again)
			Game::game::Instance()->SetCurrentLevel(temp_2);
			
			PAUSED_TO_MAIN = true;
			
			/*
			FSM::GameStateMachine::Instance()->popState();   //pop the current paused state
			
			FSM::GameStateMachine::Instance()->changeState(new FSM::MenuState);  //change the PlayState with MenuState
			*/
		}

		void PausedState::Paused_ToResume()        //resume to PlayState
		{

			PAUSED_TO_RESUME = true;

			/*
			FSM::GameStateMachine::Instance()->popState();
			*/
		}

		void PausedState::SetCallBacks()
		{
			/*
			for (int i = 0; i < m_gameObjects.size(); i++)
			{
				if (dynamic_cast<Game::MenuButton*>(m_gameObjects[i]))     //if can be "dynamic cast" to (MenuButton*) first (or else you'll burn)
																		   //it's deep meaning is that GameObject* is pointing to a Menubutton type
				{
					Game::MenuButton* temp = dynamic_cast<Game::MenuButton*>(m_gameObjects[i]);

					temp->SetCallBack(m_callBacks[temp->getCallBackID()]);  //SetCallBack of a state is a little different from SetCallBack of a..
																			//..MenuButton object

					//ONLY MenuButton has GetCallBackID function --> so that why we dynamic cast it
				}
			}
			*/

			for (int i = 0; i < PausedLevel->Get_Layers()->size(); i++)
			{
				if (dynamic_cast<LEVEL::ObjectLayer*>(PausedLevel->Get_Layers()->at(i)))
				{
					LEVEL::ObjectLayer* tempObjectLayer = dynamic_cast<LEVEL::ObjectLayer*>(PausedLevel->Get_Layers()->at(i));

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
	}
}