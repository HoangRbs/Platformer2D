#include"GameStateMachine.h"
#include"../game.h"

namespace HDT_engine
{
	namespace FSM
	{
		GameStateMachine* GameStateMachine::instance = NULL;     //static --> singleton

		GameStateMachine::GameStateMachine()
		{

		}

		GameStateMachine::~GameStateMachine()
		{

		}

		void GameStateMachine::pushState(GameState* input_state)
		{
			m_gameStates.push_back(input_state);
			m_gameStates.back()->Enter();            //getting into the state --> "Entering...."
		}

		void GameStateMachine::popState()  
		{
			if (!m_gameStates.empty())
			{
				if (m_gameStates.back()->Exit())     //before pop()  --> delete all the shit of the outer most state
				{
					delete m_gameStates.back();
					m_gameStates.pop_back();
				}
			}
		}

		void GameStateMachine::changeState(GameState* input_state)
		{
			Game::game::Instance()->Set_ScrollingbackgroundStopped(false);

			int temp = PLAYERLIVESMAX;
			Game::game::Instance()->Set_PlayerLives(temp);
			
			/*
			if (Game::game::Instance()->GetCurrentLevel() == 0)   //when changing a new state but the boss lives are still the same
																  //have to reset it
			{
				int temp = BOSSLEVEL_1_LIVESMAX;
				Game::game::Instance()->Set_CurrentBossLevelLives(temp);
			}
			else if (Game::game::Instance()->GetCurrentLevel() == 1)
			{
				int temp = BOSSLEVEL_2_LIVESMAX;
				Game::game::Instance()->Set_CurrentBossLevelLives(temp);
			}
			*/

			if (!m_gameStates.empty())
			{
				//if (m_gameStates.back()->get_StateID() == input_state->get_StateID())
				//{
					//two stages are the same --> do nothing -->but if we want to get new level in new PlayState
					//we have to change PlayState with PlayState
				//	return;
				//}
				if (m_gameStates.back()->Exit())        //exit will clear everything of that state
				{
					delete m_gameStates.back();
					m_gameStates.pop_back();
				}
			}

			m_gameStates.push_back(input_state);
			m_gameStates.back()->Enter();                 //enter the outer most stage  --> start init everthing in that state
		}

		void GameStateMachine::update()
		{
			m_gameStates.back()->update();    //update current(outer most) state
		}

		void GameStateMachine::render()
		{
			m_gameStates.back()->render();   //render current(outer most) state
		}

		GameStateMachine* GameStateMachine::Instance()
		{
			if (instance == NULL)
			{
				instance = new GameStateMachine;
				
				//instance->AnnounceToExit = false;  //init here !!!
				//instance->AnnounceToPlay = false;
			}
			return instance;
		}

		GameState* GameStateMachine::Get_WantedState(std::string StateID)
		{
			for (int i = 0; i < m_gameStates.size(); i++)
			{
				if (m_gameStates.at(i)->get_StateID() == StateID)
				{
					return m_gameStates.at(i);
				}
			}
			
			std::cout << "Cannot Get Wanted State" << std::endl;

			return NULL;
		}
	}
}