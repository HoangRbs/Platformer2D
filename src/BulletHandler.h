#pragma once
#ifndef BULLETHANDLER_H
#define BULLETHANDLER_H

#include<vector>
#include"Bullet.h"
#include"Math/Vector2D.h"

namespace HDT_engine
{
	namespace Game				   //singleton
	{
		class BulletHandler        //instead of using gameObjectFactory for bullet game object --> we'll use BulletHandler
		{
		public:

			~BulletHandler();

			void UpdateBullets();
			void DrawBullets();

			void AddPlayerBullet(int pos_x, int pos_y, int screenWidth_, int screenHeight_, std::string textureID_,
								 int FrameWidth_, int FrameHeight_, int numFrames_, int animSpeed_,
								 Math::Vector2D BulletVel_, Math::Vector2D BulletAcc_);

			void AddEnemyBullet(int pos_x, int pos_y, int screenWidth_, int screenHeight_, std::string textureID_,
								int FrameWidth_, int FrameHeight_, int numFrames_, int animSpeed_, 
								Math::Vector2D BulletVel_, Math::Vector2D BulletAcc_);

			void BulletsClear();

			std::vector<PlayerBullet*>* Get_PlayerBullets();
			std::vector<EnemyBullet*>* Get_EnemyBullets();

			static BulletHandler* Instance();

		private:
			BulletHandler();
			static BulletHandler* instance;
			std::vector<PlayerBullet*> m_PlayerBullets;
			std::vector<EnemyBullet*> m_EnemyBullets;
		};
	}
}
#endif