#pragma once
#ifndef PAUSEDSTATE_H
#define PAUSEDSTATE_H

#include"GameStateGeneral.h"
#include"GameStateMachine.h"
#include"MenuState.h"

#include"../GameObject.h"
#include"../MenuButton.h"
#include"../LoadParams.h"
#include"../graphic/TextureManager.h"

#include"../level/Level.h"
#include"../level/LevelParser.h"

#include<vector>

namespace HDT_engine
{
	namespace FSM
	{
		class PausedState: public GameStateGeneral
		{
		private:
			std::vector<Game::GameObject*> m_gameObjects;

			const string PausedStateID = "PAUSEDSTATE";

			virtual void SetCallBacks();

			static void Paused_ToMain();           //to main menu   -->add feature for button
			static void Paused_ToResume();         //resume the game

			static bool PAUSED_TO_MAIN;
			static bool PAUSED_TO_RESUME;

			///LEVEL --> right now we'll gonna use level parser to design MenuState
			LEVEL::Level* PausedLevel = NULL;



		public:
			virtual void update();
			virtual void render();

			virtual bool Enter();
			virtual bool Exit();

			virtual std::string get_StateID();
		};
	}
}
#endif
