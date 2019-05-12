#pragma once

#ifndef MENUSTATE_H
#define MENUSTATE_H

#include"GameStateGeneral.h"
#include"../GameObject.h"
#include"../MenuButton.h"
#include"../graphic/TextureManager.h"

#include"../GameObjectFactory.h"
#include"../MenuButtonCreator.h"
#include"../BaseObjectCreator.h"

#include"GameStateMachine.h"                          //State pattern --> maybe a small path of it 
#include"../sound/SoundManager.h"

#include"../level/Level.h"
#include"../level/LevelParser.h"

#include<iostream>
#include<vector>

namespace HDT_engine
{
	namespace FSM
	{
		class MenuState : public GameStateGeneral
		{
		public:

			virtual void update();       //the menu state is just like how the Game operating --> it update all needed objects...
										 //..(PLAY BUTTON, EXIT BUTTON ,...)
										 //..just like the game updating ENEMIES and PLAYER.
			virtual void render();       //..just like how the game render objects

			virtual bool Enter();        //this create the whole things
			virtual bool Exit();         //this destroy the whole things

			virtual std::string get_StateID();  //ID is used to ensure that states do not get repeated
		private:

			std::vector<Game::GameObject*> m_gameobjects;

			const std::string menu_stateID = "MENUSTATE";
	   
			virtual void SetCallBacks();

			static void MenuToPlay();                                             //FOR CALLBACK FUNCTION --> add FEATURE to MenuButton
			static void MenuToExit();

			static bool MENU_TO_PLAY ;


			//why CallBacks have to be STATIC !!!!! --->
			//when an Object of the current StateObject is operating CallBack()...
			//that Object (for example) trying to delete that current StateObject and push a new State...
			//...so everthing of the old State has to be gone! --> even MenuToPlay..
			//..fornately --> MenuToPlay() is out of scope of that old State(STATIC)...
			//..so memory system won't be messed up..
			//..this is why callBack is invented

			///LEVEL --> right now we'll gonna use level parser to design MenuState
			LEVEL::Level* MenuLevel = NULL;
		};
	}
}

#endif