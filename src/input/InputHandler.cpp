#include"InputHandler.h"

namespace HDT_engine
{
	namespace INPUT
	{
		InputHandler::InputHandler()
		{
			is_close = false;						     //pass to game.close()
			
			m_keyboardstate = SDL_GetKeyboardState(NULL);

			for (int i = 0; i < 3; i++)
			{
				m_mouseState.push_back(false);
			}
		}

		InputHandler::~InputHandler()
		{

		}

		InputHandler* InputHandler::s_instance = NULL;  //static define



		InputHandler* InputHandler::Instance()
		{
			if (s_instance == NULL)
			{
				s_instance = new InputHandler();

			}
			return s_instance;
		}

		void InputHandler::update()  //Poll events  -->used in handleEvent in game class
		{
			///after they released for 1 short amount of time --> so it is only true for a short amount of time
			RIGHT_KEY_RELEASED = false;
			LEFT_KEY_RELEASED = false;
			///wait until the next Frame

			while (SDL_PollEvent(&m_event) != 0)
			{
				switch (m_event.type)
				{
				case SDL_QUIT:
					is_close = true;
					break;

				case SDL_MOUSEMOTION:
					HandleMouseMove();
					break;

				case SDL_MOUSEBUTTONDOWN:
					HandleMouseButtonDown();
					break;

				case SDL_MOUSEBUTTONUP:
					HandleMouseButtonUp();
					break;
				
				case SDL_KEYUP:
					switch (m_event.key.keysym.sym)
					{
					case SDLK_RIGHT:
						RIGHT_KEY_RELEASED = true;
						break;
					case SDLK_LEFT:
						LEFT_KEY_RELEASED = true;
						break;
					}
					break;
			
				}
			}
		}

		void InputHandler::clean()   //clean devices we had initialized
		{

		}

		bool InputHandler::get_close_info()
		{
			return is_close;
		}

		bool InputHandler::is_thiskey_pressed(SDL_Scancode key)
		{
			if (m_keyboardstate[key] == 1)
				return true;
			return false;
		}
		
		bool InputHandler::is_thiskey_notpressed(SDL_Scancode key)
		{
			if (m_keyboardstate[key] == 0)
				return true;
			return false;
		}

		bool InputHandler::is_thisMouseButton_pressed(int key)
		{
			return m_mouseState[key];
		}

		Math::Vector2D* InputHandler::get_mouse_pos()
		{
			return &m_mousePosition;
		}

		void InputHandler::HandleMouseMove()
		{
			m_mousePosition.set_x(m_event.motion.x);
			m_mousePosition.set_y(m_event.motion.y);
		}

		void InputHandler::HandleMouseButtonDown()
		{
			if(m_event.button.button == SDL_BUTTON_LEFT)
				m_mouseState[LEFT] = true;
			
			if(m_event.button.button == SDL_BUTTON_RIGHT)
				m_mouseState[RIGHT] = true;
			
			if (m_event.button.button == SDL_BUTTON_MIDDLE)
				m_mouseState[MIDDLE] = true;
		}

		void InputHandler::HandleMouseButtonUp()
		{
			if (m_event.button.button == SDL_BUTTON_LEFT)
				m_mouseState[LEFT] = false;
			
			if (m_event.button.button == SDL_BUTTON_RIGHT)
				m_mouseState[RIGHT] = false;
			
			if (m_event.button.button == SDL_BUTTON_MIDDLE)
				m_mouseState[MIDDLE] = false;
		}
	}
}