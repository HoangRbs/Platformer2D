#pragma once
						//is used in "game.h"

//this will use singleton pattern

#include<iostream>   //to avoid this -> use precompiled header file
#include<string>
#include<SDL.h>
#include<SDL_Image.h>
#include<map>
#undef main  //in order for SDL to work -> not crupted with SDLmain

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

namespace HDT_engine
{
	namespace Graphic
	{

		class TextureManager        //singleton.......
		{
		private:
			std::map<std::string, SDL_Texture*> m_textureMap;	  						    //texture  //->remember to use UNIQUE pointer in the...
																							//...future
			SDL_Renderer* m_renderer;
			static TextureManager* var_instance;											//return to Instance()
		public:
			bool load(std::string filepath,std::string ID,SDL_Renderer* m_renderer); 
			
			void draw(std::string ID,float x,float y,int screenWidth,int screenHeight);	//for all basic texture
			void drawFlip(std::string ID, float x, float y, int screenWidth, int screenHeight, SDL_RendererFlip fliptype); //for flipping the object
			
			void drawFrame(std::string textureID, float x, float y, int FrameWidth, int FrameHeight,                //for animated texture
						   int screenWidth, int screenHeight, int currentColumn, int currentRow,
						   int angle_, int alpha_);

			void drawFrameFlip(std::string textureID, float x, float y, int FrameWidth, int FrameHeight,
							   int screenWidth, int screenHeight, int currentColumn, int currentRow,
							   int angle_, int alpha_,SDL_RendererFlip Flip);
			
			void draw_1_Tile(std::string ID,int tileWidth,int tileHeight,float pos_x, float pos_y,int current_Column,int current_Row);

			void draw_ScrollingBackground(std::string textureID_, SDL_Rect& srcRect_, SDL_Rect& destRect_);

			void clearFromTextureMap(std::string ID);

			static TextureManager* Instance();

			std::map<std::string, SDL_Texture*>* Get_textureMap() { return &m_textureMap; }
		public:
			SDL_Renderer* get_renderer();
			void take_renderer(SDL_Renderer* m_renderer);  //get renderer from Window class
		private:  
			TextureManager();
			~TextureManager();
		};
	}
}

#endif