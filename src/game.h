//BULDING A PLATFORM GAME 
//FUCKING ADVENTURE THE GAME

#pragma once

#ifndef GAME_H
#define GAME_H


#include<SDL.h>
#include<iostream>
#include<vector>

#include"graphic/TextureManager.h"      //to use TextureManager in Game
#include"LoadParams.h"
#include"Player.h"
#include"Enemy.h"
#include"input/InputHandler.h"

#include "FSM/GameStateMachine.h"
#include "FSM/GameState.h"
#include "FSM/MenuState.h"
#include "FSM/PlayState.h"

using namespace std;
#define PLAYERLIVESMAX 6;
//#define BOSSLEVEL_1_LIVESMAX 70;
//#define BOSSLEVEL_2_LIVESMAX 90;
//#define MAX_LEVELS 2;     //right now only 2 levels max
#define MAX_LEVELS 1;
#define FPS 120;

extern float floatFPS;
extern float deltaTime;

namespace HDT_engine
{
	namespace Game
	{

		class game   
		{
		private:
			
			vector<GameObject*> m_gameObjects;                     //use unique pointer in the future
			SDL_Renderer* m_renderer;
			FSM::GameStateMachine* m_gameStateMachine;

			game();													//get original renderer from window class
			~game();												//destroy renderer inside here

			static game* instance;                                  //has to be defined or else will get error

			int m_gameWidth;
			int m_gameHeight;
			int scrollVelocity;

			SDL_Window* m_window;

		public:

			void Init();
			void render();											//copy to main renderer
			void update();											//dealing with texture and math, physic and stuff 
																	//-> different from update() in Window class
			
			void handleEvents();  
			bool close();

			bool is_close;
			static game* Instance();

			int Get_GameWidth();
			int Get_GameHeight();
			int Get_ScrollVelocity();

			//Level system
			bool Get_Level_Complete();       ///is used in Player --> and the Player annouce the the game
			void Set_Level_Complete(bool Input_);   ///is used in CheckPointObject --> set --> Player get the signal --> annouce the game
			void GoHigherLevel(); 
			bool b_GoHigherLevel = false;
			void GoHigherLevel_AvoidVectorError();    ///is put in Update()
			int GetCurrentLevel() { return m_currentLevel; }         //used as index to parse new level in PlayState Enter()
			void SetCurrentLevel(int input_) { m_currentLevel = input_; }  //is used in Player.cpp update() when it completes a level

			//Player system
			void Set_PlayerLives(int m_PlayerLives_);
			int Get_PlayerLives();

			//bosses system
			int Get_CurrentBossLevelLives();
			void Set_CurrentBossLevelLives(int input_);

			//stop scrolling background --> is used when the Map in TileLayer stops
			//the GAME gets the "signal"
			//and announce the ObjectsLayer to stop scrolling background if that is its type
			bool Get_ScrollingBackgroundStopped() { return ScrollingBackgroundStopped; }
			void Set_ScrollingbackgroundStopped(bool input_) { ScrollingBackgroundStopped = input_; }

		private:
			//level system
			bool Level_Complete;
			int m_currentLevel = 0;      

			//player system
			int m_PlayerLives;

			//bosses system
			int m_BossLevel_1_Lives; // = 50
			int m_BossLevel_2_Lives; // = 70

			//stop scrolling background --> is used when the Map in TileLayer stops
			//this gonna be RESET when changing a new PLAYSTATE
			bool ScrollingBackgroundStopped = false;
		};

	}
}

#endif