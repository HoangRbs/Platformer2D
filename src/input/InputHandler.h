#pragma once

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include<SDL.h>
#include<vector>
#include<iostream>
#include"../math/Vector2D.h"

namespace HDT_engine
{
	namespace INPUT
	{
		enum mouse_buttons         //index code --> mouse button state
		{
			LEFT,MIDDLE,RIGHT
		};

		class InputHandler								 //singleton....
		{
		public:
			static InputHandler* Instance();
			void update();                               //everything goes here
			void clean();
			bool get_close_info();			//close window ->send to "game" class

			bool is_thiskey_pressed(SDL_Scancode key);   //use which key is pressed to control player(.cpp)
			bool is_thiskey_notpressed(SDL_Scancode key);

			///these are used in Player::HandleInput();
			bool is_RightKey_Released() { return RIGHT_KEY_RELEASED; }
			bool is_LeftKey_Released() { return LEFT_KEY_RELEASED; }

			bool is_thisMouseButton_pressed(int key);
			
			Math::Vector2D* get_mouse_pos();			 //get mouse pos to interact with NPC

		private:
			InputHandler();
			~InputHandler();

			static InputHandler* s_instance;
			bool is_close;
			SDL_Event m_event;
			vector<bool> m_mouseState;					//mouse container states
			const Uint8* m_keyboardstate;				//key board container states(*pointer)
			Math::Vector2D m_mousePosition;

			void HandleMouseMove();                            //movement of the mouse
			void HandleMouseButtonDown();
			void HandleMouseButtonUp();

			///is used in Player handle input
			bool LEFT_KEY_RELEASED = false;
			bool RIGHT_KEY_RELEASED = false;

		};
	}
}
#endif 