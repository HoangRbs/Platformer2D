#pragma once

#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include"GameStateGeneral.h"
#include"PausedState.h"
#include"GameOverState.h"

#include"../GameObject.h"          //all gameplay will be in this
#include"../Enemy.h"
#include"../Player.h"
#include"../AnimatedGraphic.h"
#include"../LoadParams.h"
#include"../input/InputHandler.h"

#include"../PlayerCreator.h"
#include"../EnemyCreator.h"
#include"../AnimatedGraphicCreator.h"
#include"../level/Level.h"
#include"../level/LevelParser.h"
#include"../CollisionManager.h"

#include"../sound/SoundManager.h"

#include<iostream>
#include<vector>

namespace HDT_engine
{
	namespace FSM
	{

		class PlayState : public GameStateGeneral
		{
		private:
			
			enum LEVEL_FILEPATH_INDEX
			{
				LEVEL_1 = 0,
				LEVEL_2 = 1
			};

			vector<string> LevelFilePath;

		public:
			virtual void update();
			virtual void render();

			virtual bool Enter();            //after calling enter in the stateMachine --> we should load every things needed
			virtual bool Exit();             //delete every thing

			virtual std::string get_StateID();
			
			void Set_PlayState_SafeZone(bool input);       //to do in Pause state whenever it is pop
														   //so when go back to PlayState ,we can access the SafeZone in PlayState

		private:

			const std::string Play_StateID = "PLAYSTATE";

			virtual void SetCallBacks();   //there is nothing here(cuz this is PlayState)

			bool CheckForCollision(Game::PlatformerObject* object_1,Game::PlatformerObject* object_2);

			std::vector<Game::GameObject*> m_gameobjects;          //SAFE MEMORY USAGE

			//LEVEL
			LEVEL::Level* level;

			//ANIMATE_CAT testing purpose
			int animateCat_currentColumn = 0;       //current column frame section on the animate_cat texture
			int animateCat_numFrames = 6;		    //total Frames of animate_cat.png

			//PLAYSTATE_SAFEZONE
			bool PlayState_SafeZone = true;       //use when change/push a new state
												  //avoid fucking out our program (memory shit)

			//SAFE MEMORY USAGE
			int PLAYSTATE_GAMEOBJECTS_SIZE = 1;    //we'll use this rather than the bool variable right above

			//Collision Manager
			Game::CollisionManager m_CollisionManager;
		};
	}
}
#endif
