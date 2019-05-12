#pragma once
#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include"Player.h"
#include"level/TileLayer.h"

namespace HDT_engine
{
	namespace Game
	{
		class CollisionManager
		{
		public:
			void CheckPlayer_EnemyBulletCollision(Player* inputPlayer);      //is used in Level update()
			
			
			void CheckPlayer_EnemiesCollision(Player* inputPlayer, std::vector<GameObject*>& m_gameObjects_);   //is used in ObjectLayer update()
																												//void CheckEnemies_PlayerBulletsCollision(std::vector<GameObject*>& m_gameObjects_);               //ObjectLayer update()
			//void CheckPlayer_TileLayerCollision(Player* inputPlayer, std::vector<LEVEL::TileLayer*>& CollisionLayers,
			//									int numTileMapWidth,int numTileMapHeight);  //used in LEVEL update()

			//BULDING AN ADVENTURE GAME
			//NO MORE BULLET COLLISION

			//MOVING PLATFORM COLLISION
			///this is a fucking fail code
			void CheckOtherObjects_MovingPlatformsCollision(std::vector<GameObject*>* gameObjects, std::vector<GameObject*>* MovingPlatforms);

		private:
		};
	}
}
#endif