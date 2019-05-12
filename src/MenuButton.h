#pragma once

#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include"PlatformerObject.h"
#include"LoadParams.h"
#include"input/InputHandler.h"                         //track the mouse position
#include"sound/SoundManager.h"

namespace HDT_engine
{
	namespace Game
	{
		class MenuButton: public PlatformerObject         //since menu button has texture (textureID), position(vector2D) -> inherit this
		{
			typedef void(* void_function_pointer)();
		
		private:
			enum buttonStates               //special Frame change
			{
				MOUSE_OUT = 0,              //0th num_Column
				MOUSE_OVER = 1,				//1th num_Column
				MOUSE_CLICKED = 2			//2th num_Column
			};

		public:
			MenuButton();
			void draw();
			void update();
			void clean();
			void load(unique_ptr<LoadParams> inputParams);
			
			void SetCallBack(void_function_pointer m_callBack_);
			int getCallBackID();                                   //not really what to do with this right now

			///handle mouse cliking better
			bool is_LeftMouseReleasedPrev;         ///true at the first time

		};
	}
}
#endif
