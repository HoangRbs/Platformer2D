#pragma once
#ifndef GAMESTATEMACHINE_H
#define GAMESTATEMACHINE_H

#include"GameState.h"
#include<vector>
#include<iostream>

namespace HDT_engine
{
	namespace FSM             //this is just a simple concept --> STATE pattern --> the FSM_2(real concept) will be implemented in game
	{						  //to control/ react NPC...
		class GameStateMachine
		{
		public:
			void pushState(GameState* input_state);
			void changeState(GameState* input_state);
			void popState();

			void update();
			void render();

			GameState* Get_WantedState(std::string StateID);           //used in PAUSE STATE::Paused_ToResume() --> look for it

			static GameStateMachine* Instance();

		private:
			GameStateMachine();
			~GameStateMachine();

			std::vector<GameState*> m_gameStates;  //save the created states
			static GameStateMachine* instance;

			//bool AnnounceToExit;
			//bool AnnounceToPlay;
		};
	}
}
#endif
