#include"TextureManager.h"


namespace HDT_engine
{
	namespace Graphic
	{
		TextureManager::TextureManager()
		{
			//nothing
			//TESTING --> DELETE LATER
			SDL_SetRenderDrawColor(m_renderer,255,0,0,255);
		}

		TextureManager::~TextureManager()        //use unique pointer to delete in the future
		{

		}

		bool TextureManager::load(std::string filepath, std::string ID,SDL_Renderer* m_renderer)
		{
			
			SDL_Surface* temp_surface = IMG_Load(filepath.c_str());
			if (temp_surface == NULL)
			{
				std::cout << " fail to get texture at : "<<filepath<<" because "<<IMG_GetError()<<std::endl;
				return false;
			}
			else
			{
				SDL_Texture* temp_texture = SDL_CreateTextureFromSurface(m_renderer,temp_surface);
				if (temp_texture == NULL)
				{
					std::cout << " convert to texture fail " <<IMG_GetError()<<std::endl;
					return false;
				}
				else
				{
					m_textureMap[ID] = temp_texture;
					SDL_FreeSurface(temp_surface);
					return true;
				}
			}

			return false;
		}

		//this becomes useless function now
		void TextureManager::draw(std::string ID, float x, float y, int screenWidth, int screenHeight) //draw the loaded texture using ID
		{
			SDL_Rect desRect;
			desRect.x = x;
			desRect.y = y;
			desRect.w = screenWidth;
			desRect.h = screenHeight;

			SDL_RenderCopy(m_renderer,m_textureMap[ID],NULL,&desRect);  //copy! -> have to present it in window update!
		}

		//this become useless function now
		void TextureManager::drawFlip(std::string ID, float x, float y, int screenWidth, int screenHeight,
			SDL_RendererFlip fliptype)
		{
			SDL_Rect desRect;
			desRect.x = x;
			desRect.y = y;
			desRect.w = screenWidth;
			desRect.h = screenHeight;

			SDL_RenderCopyEx(m_renderer, m_textureMap[ID], NULL, &desRect, NULL, NULL, fliptype);
		}


		void TextureManager::drawFrame(std::string textureID, float x, float y, int FrameWidth, int FrameHeight, 
									   int screenWidth, int screenHeight,int currentColumn,int currentRow,
									   int angle_,int alpha_)
		{
			
			SDL_Rect srcRect; SDL_Rect destRect;
			srcRect.x = currentColumn * FrameWidth; srcRect.y = currentRow * FrameHeight;
			srcRect.w = FrameWidth; srcRect.h = FrameHeight;

			destRect.x = x; destRect.y = y;
			destRect.w = screenWidth; destRect.h = screenHeight;

			//set alpha for the texture
			SDL_SetTextureAlphaMod(m_textureMap[textureID],alpha_);
			SDL_RenderCopyEx(m_renderer,m_textureMap[textureID],&srcRect,&destRect,angle_,NULL,SDL_FLIP_NONE);
			
		}


		//our HELICOPTER game does not need this yet
		void TextureManager::drawFrameFlip(std::string textureID, float x, float y, int FrameWidth, int FrameHeight, 
										   int screenWidth, int screenHeight,int currentColumn, int currentRow, 
										   int angle_, int alpha_,SDL_RendererFlip fliptype)
		{
			SDL_Rect srcRect; SDL_Rect destRect;
			srcRect.x = currentColumn * FrameWidth; srcRect.y = currentRow * FrameHeight;
			srcRect.w = FrameWidth; srcRect.h = FrameHeight;

			destRect.x = x; destRect.y = y;
			destRect.w = screenWidth; destRect.h = screenHeight;
			
			SDL_SetTextureAlphaMod(m_textureMap[textureID], alpha_);
			SDL_RenderCopyEx(m_renderer,m_textureMap[textureID],&srcRect,&destRect,angle_,NULL,fliptype);
		}
	
		void TextureManager::clearFromTextureMap(std::string ID)
		{
			if (m_textureMap[ID] == NULL)
			{
				std::cout << "there is no such textureID "<<ID<< std::endl;
			}
			m_textureMap.erase(ID);
		}

		TextureManager* TextureManager::var_instance = NULL;  //init
		
		TextureManager* TextureManager::Instance()
		{
			if (var_instance == NULL)
				var_instance = new TextureManager();
			return var_instance;
		}

		SDL_Renderer* TextureManager::get_renderer()
		{
			return m_renderer;
		}

		void TextureManager::take_renderer(SDL_Renderer* m_renderer)
		{
			this->m_renderer = m_renderer;
		}

		void TextureManager::draw_1_Tile(std::string ID,				//ID to find the right texture to draw
										 int tileWidth, int tileHeight, //tileSize
									     float pos_x,float pos_y,			//x and y where to draw on the screen
									     int currentColumn,             //current Row and current Column...
										 int currentRow)				//..is used to determine which block section of the..
																		//..texture(by ID) is cut
														
		{
			SDL_Rect srcRect;   //where to cut
			SDL_Rect destRect;  //where to put on screen

			srcRect.x = currentColumn * tileWidth;                 //multiplied by tilesize to get the actual position where to cut on texture
			srcRect.y = currentRow * tileHeight;				   //multiplied by tilesize to get the actual position where to cut on texture
			srcRect.w = tileWidth;
			srcRect.h = tileHeight;

			destRect.x = pos_x;
			destRect.y = pos_y;
			destRect.w = tileWidth;
			destRect.h = tileHeight;

			SDL_RenderCopyEx(m_renderer,m_textureMap[ID],&srcRect,&destRect,0,0,SDL_FLIP_NONE);
		}

		void TextureManager::draw_ScrollingBackground(std::string textureID_ ,SDL_Rect& srcRect_,SDL_Rect& destRect_)
		{
			SDL_RenderCopyEx(m_renderer,m_textureMap[textureID_],&srcRect_,&destRect_,0,NULL,SDL_FLIP_NONE);
		}
	}
}