#pragma once

//FINITE STATE MACHINE (FSM)

#ifndef GAMESTATE_H
#define GAMESTATE_H
#include<string>
#include<vector>

namespace HDT_engine
{
	namespace FSM								  //finite state machine --> just basic --> not really finite state machine
	{

		class GameState                           //base class
		{

		public:
			virtual void update() = 0;
			virtual void render() = 0;

			virtual bool Enter() = 0;
			virtual bool Exit() = 0;

			virtual std::string get_StateID() = 0;  //ID is used to ensure that states do not get repeated
		};
	}
}
#endif
