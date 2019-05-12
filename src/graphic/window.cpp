#include"window.h"
#include"../game.h"

namespace HDT_engine  //EV engine
{
	namespace Graphic
	{
		Window* Window::instance = NULL;                   //singleton

		Window::Window(const char* title, int width, int height)
		{
			this->title = title;
			this->width = width;
			this->height = height;
			if (!Init())                //Window Init is here
			{
				SDL_Quit();
			}
		}

		Window::~Window()
		{
			SDL_DestroyWindow(m_window);
			m_window = NULL;
		}

		bool Window::Init()
		{
			if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
			{
				cout << " FAIL TO INIT SDL " << endl;
				return false;
			}
			m_window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN);
			if (m_window == NULL)
			{
				cout << " SDL FAIL TO INIT WINDOW " << endl;
			}
			else
			{
				if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
				{
					cout << " INIT PNG FAIL " << IMG_GetError() << endl;
					return false;
				}
				m_renderer = SDL_CreateRenderer(m_window,-1,SDL_RENDERER_ACCELERATED);

				///NEW FUCKING THINGS
				SDL_RenderSetLogicalSize(m_renderer, HDT_engine::Game::game::Instance()->Get_GameWidth(), 
													 HDT_engine::Game::game::Instance()->Get_GameHeight());


				//SDL_RenderSetIntegerScale(m_renderer,SDL_TRUE);
				///
				
				TextureManager::Instance()->take_renderer(m_renderer);         //pass window's renderer into this -> I was gonna
																	//make window singleton but it needs value set from outside so....
				return true;
			}
			return false;
		}


		void Window::Render()
		{
			SDL_RenderPresent(m_renderer);
			SDL_RenderClear(m_renderer);
		}
	

		SDL_Renderer* Window::get_renderer()
		{
			return m_renderer;
		}

		Window* Window::Instance()
		{
			if (instance == NULL)
			{
				/*
				instance = new Window("EV engine written in SDL/C++ by HoangRbs", 
									  HDT_engine::Game::game::Instance()->Get_GameWidth() * 2,
									  HDT_engine::Game::game::Instance()->Get_GameHeight() * 2);
				*/

				instance = new Window("The Man",
									  1280,
									  720);
			}

			return instance;
		}
	}
}