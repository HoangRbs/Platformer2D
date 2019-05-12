#pragma once
#ifndef WINDOW_H
#define WINDOW_H


#include<SDL.h>
#include<iostream>
#include<SDL_Image.h>
#include"TextureManager.h"  //pass renderer into this texture singleton -> use it every where

using namespace std;

namespace HDT_engine
{
	namespace Graphic
	{

		class Window
		{
		private:
			const char* title;
			int width;
			int height;
			SDL_Window* m_window;
			SDL_Event m_event;
			SDL_Renderer* m_renderer;
			
			static Window* instance;
		public:
			~Window();
			inline int get_width() { return width; }
			inline int get_height() { return height; }
			void Render();
			SDL_Renderer* get_renderer();
			
			static Window* Instance();
		private:
			bool Init();
			Window(const char* title, int width, int height);  //constructor to create window

		};
	}
}

#endif