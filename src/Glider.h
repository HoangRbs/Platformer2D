#pragma once
#ifndef GLIDER_H
#define GLIDER_H

#include"Enemy.h"
#include"Camera.h"

namespace HDT_engine
{
	namespace Game
	{
		class Glider: public Enemy
		{
		public:
			Glider() :Enemy()
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
						//if (scrollTimeCounter == scrollTime)
						//{
						//	Scroll(game::Instance()->Get_ScrollVelocity());
						//	scrollTimeCounter = 0;
						//}

						//scrollTimeCounter++;

						if (m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x()<= game::Instance()->Get_GameWidth()
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
				m_velocity.set_x(0);
				m_velocity.set_y(0);

				m_BulletReloadTime = 150;
				m_BulletReloadTimeCounter = 0;

				m_Health = 4;
			}

			~Glider()
			{

			}

		private:

			void HandleFireBullet()
			{
				if (m_BulletReloadTimeCounter == m_BulletReloadTime)
				{
					BulletHandler::Instance()->AddEnemyBullet(m_position.get_x(), m_position.get_y() + 10, 25, 25, 
															  "GLIDERBULLET", 15, 12, 1, 800, 
															   Math::Vector2D(-2, 0), Math::Vector2D(0, 0));

					m_BulletReloadTimeCounter = 0;
				}

				m_BulletReloadTimeCounter++;
			}
		};
	}
}
#endif