#pragma once
#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include"GameStateGeneral.h"
#include"GameStateMachine.h"
#include"MenuState.h"

#include"../GameObject.h"
#include"../MenuButton.h"
#include"../graphic/TextureManager.h"

#include"../level/Level.h"
#include"../level/LevelParser.h"

#include<vector>
#include<string>

namespace HDT_engine
{
	namespace FSM
	{
		class GameOverState : public GameStateGeneral
		{
		private:

			virtual void SetCallBacks();
			std::vector<Game::GameObject*> m_gameobjects;

			const std::string GameOverStateID = "GAMEOVERSTATE";

			static void GameOverToMain();                 //game over to mainmenu
			static void GameOverToRestart();              //game over --> restart immediatly
			static bool GAMEOVER_TO_MAIN;
			static bool GAMEOVER_TO_RESTART;

			LEVEL::Level* GameOverLevel = NULL;

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
