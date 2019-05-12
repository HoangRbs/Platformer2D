#pragma once
#ifndef TURRET_H
#define TURRET_H

#include"Enemy.h"
#include"Camera.h"

namespace HDT_engine
{
	namespace Game
	{
		class Turret: public Enemy
		{
		public:
			Turret() :Enemy()
			{

			}

			void draw()
			{
				Enemy::draw();
			}

			void update()
			{
				if (!is_dead)
				{
					if (!EnterScreen)
					{
						//if (scrollTimeCounter == scrollTime)  //no more scrolling --> Player's gonna get there
						//{
						//	Scroll(game::Instance()->Get_ScrollVelocity());
						//	scrollTimeCounter = 0;
						//}

						//scrollTimeCounter++;

						if (m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x() <= game::Instance()->Get_GameWidth()
							&& m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x() > 0
							&& m_position.get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y() > 0 &&
							m_position.get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y() <= game::Instance()->Get_GameHeight())
						{
							EnterScreen = true;
						}

					}
					else
					{
						if (!is_dying)
						{
							HandleFireBullet();

							//if (scrollTimeCounter == scrollTime)
							//{
							//	Scroll(game::Instance()->Get_ScrollVelocity());
							//	scrollTimeCounter = 0;
							//}

							//scrollTimeCounter++;
						}

						Enemy::update();           //standard update
					}

				}
			}

			void clean()
			{
				Enemy::clean();
			}

			void load(unique_ptr<LoadParams> const& inputParams)
			{
				Enemy::load(inputParams);

				//some more special load
				m_velocity.set_x(0);
				m_velocity.set_y(0);

				m_BulletReloadTime = 180;
				m_BulletReloadTimeCounter = 0;

				m_Health = 5;
			}

			~Turret()
			{

			}
		private:

			void HandleFireBullet()
			{
				if (m_BulletReloadTimeCounter == m_BulletReloadTime)
				{
					BulletHandler::Instance()->AddEnemyBullet(m_position.get_x(), m_position.get_y() + 10, 25, 25, 
															  "TURRETBULLET", 13, 14, 1, 800, 
															   Math::Vector2D(-2, 0), Math::Vector2D(0, 0));
					
					BulletHandler::Instance()->AddEnemyBullet(m_position.get_x(), m_position.get_y() + 10, 25, 25,
															  "TURRETBULLET", 13, 14, 1, 800,
															  Math::Vector2D(-2, -1), Math::Vector2D(0, 0));

					m_BulletReloadTimeCounter = 0;
				}

				m_BulletReloadTimeCounter++;
			}
		};
	}
}
#endif