#pragma once
#ifndef ENEMYBOSS_H
#define ENEMYBOSS_H

#include"Enemy.h"

namespace HDT_engine
{
	namespace Game
	{
		class EnemyBoss : public Enemy
		{
		public:
			EnemyBoss():Enemy()         //init every thing in gameobject()
			{

			}
			~EnemyBoss()
			{

			}

			void draw()
			{
				Enemy::draw();
			}

			void update();

			void clean()
			{
				Enemy::clean();
			}

			void load(unique_ptr<LoadParams>const& inputParams)
			{
				Enemy::load(inputParams);
				m_velocity.set_x(0);
				m_velocity.set_y(0);

				m_BulletReloadTime = 180;
				m_BulletReloadTimeCounter = 0;
			}

			void collision();           //using it's own collision

		private:

			void HandleFireBullet()
			{

				if (m_BulletReloadTimeCounter == m_BulletReloadTime)
				{

					BulletHandler::Instance()->AddEnemyBullet(m_position.get_x(), m_position.get_y() + 10,
															  m_screenWidth / 2, m_screenHeight / 2,
															  "ENEMYBOSS1BULLET", 29, 42, 1, 800,
															  Math::Vector2D(-3,-1), Math::Vector2D(0, 0));

					BulletHandler::Instance()->AddEnemyBullet(m_position.get_x(), m_position.get_y() + 10,
															  m_screenWidth/2,m_screenHeight/2, 
															  "ENEMYBOSS1BULLET", 29, 42, 1, 800, 
															  Math::Vector2D(-4, 0), Math::Vector2D(0, 0));

					BulletHandler::Instance()->AddEnemyBullet(m_position.get_x(), m_position.get_y() + 10,
															  m_screenWidth / 2, m_screenHeight / 2,
															  "ENEMYBOSS1BULLET", 29, 42, 1, 800,
															  Math::Vector2D(-3, 1), Math::Vector2D(0, 0));

					BulletHandler::Instance()->AddEnemyBullet(m_position.get_x(), m_position.get_y() + 10,
														      m_screenWidth / 3, m_screenHeight / 3,
															  "ENEMYBOSS1_2BULLET", 60, 43, 3, 50,
															  Math::Vector2D(-5, 0), Math::Vector2D(0, 0));

					m_BulletReloadTimeCounter = 0;
				}

				m_BulletReloadTimeCounter++;

			}

		};
	}
}
#endif