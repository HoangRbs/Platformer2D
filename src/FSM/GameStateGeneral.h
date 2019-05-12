#pragma once

#ifndef GAMESTATEGENERAL_H
#define GAMESTATEGENERAL_H

#include"GameState.h"
#include"StateParser/StateParse.h"
#include<vector>

namespace HDT_engine
{
	namespace FSM
	{
		class GameStateGeneral: public GameState
		{
		public:
			virtual void update() = 0;
			virtual void render() = 0;

			virtual bool Enter() = 0;
			virtual bool Exit() = 0;

			virtual std::string get_StateID() = 0;

		protected:

			typedef void(*void_function_pointer)();

			virtual void SetCallBacks() = 0;											   //..set all the gameobjects
																						   //..(type [MenuButton type] only) 
																						   //..combine with the callback(s)
                                                                                     	   //..declare here cuz all STATES need this function
																						   //..will be in the Enter() function
			
			std::vector<void_function_pointer> m_callBacks;     //store callBacks* 
			std::vector<std::string> m_Textures_ID;				//every states should have its own textures_ID list
			StateParser m_StateParser;      //now we are just parsing textures
		};
	}
}
#endif
