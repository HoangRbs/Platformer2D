#pragma once
#ifndef OBJECTLAYER_H
#define OBJECTLAYER_H

#include"../GameObject.h"
#include"Layer.h"
#include"../Player.h"
#include"../CollisionManager.h"
#include<vector>

namespace HDT_engine
{
	namespace LEVEL
	{
		class ObjectLayer : public Layer
		{
		public:
			void Update();
			void Render();
			void Clean();

			void Set_Player(Game::Player* inputPlayer_);                    //is used in objectLayer parser()
			Game::Player* Get_Player()
			{
				return m_Player;
			}

			std::vector<Game::GameObject*>* Get_m_gameObjects();			//is used in LevelParser
			std::vector<Game::GameObject*>* Get_m_MovingPlatforms();		//is used in LevelParser
			std::vector<Game::GameObject*>* Get_m_CanBeInsidePlatforms();	//is used in LevelParser

		private:
			std::vector<Game::GameObject*> m_gameObjects;   //both PLAYER and ENEMIES are in this vector
			std::vector<Game::GameObject*> m_MovingPlatforms;   //point to MovingPlatforms inside m_gameObjects for collision detection
			std::vector<Game::GameObject*> m_CanBeInsidePlatforms;   //point to CanBeInsidePlatforms inside m_gameObjects for collision detection

			Game::Player* m_Player;                         //for collision checking in ObjectLayer update()
															//is set in parseObjectLayer
			
			Game::CollisionManager m_CollisionManager;      //for collsion detection
		};
	}
}
#endif
