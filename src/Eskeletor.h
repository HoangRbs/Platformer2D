#pragma once
#ifndef ESKELETOR_H
#define ESKELETOR_H

#include"Enemy.h"
#include"Camera.h"

namespace HDT_engine
{
	namespace Game
	{
		class Eskeletor: public Enemy
		{
		public:
			Eskeletor():Enemy()
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
						
						if (m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x() <= game::Instance()->Get_GameWidth()
							&& m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x() > 0
							&& m_position.get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y() > 0 &&
							m_position.get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y() <= game::Instance()->Get_GameHeight())
							//we have to add another && condition cuz we set EnterScreen = false in Enemy Update()
							//but when get into this loop again if we don't do it right
							//the EnterSreen will be set to TRUE again and all your work will be useless
							//even increase CPU usage
						{
							EnterScreen = true;

							//now start moving up and down the sreen
							m_velocity.set_x(0);
							m_velocity.set_y(1);
						}
					}
					else
					{
						if (!is_dying)
						{
							HandleFireBullet();

							//if (scrollTimeCounter == scrollTime)
							//{
							//	Scroll(game::Instance()->Get_ScrollVelocity());   //this scroll only change position not velocity
							//	scrollTimeCounter = 0;
							//}

							//scrollTimeCounter++;

							if (m_position.get_y() >= Game::game::Instance()->Get_GameHeight())
							{
								m_velocity.set_y(-1);
							}
							else if(m_position.get_y() <= 0)
							{
								m_velocity.set_y(1);
							}
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
				//in here ,we are loading(pasre from outside) the very basic infomation

				//now the addition info will not be loaded-->we will create out own value
				m_velocity.set_x(0);
				m_velocity.set_y(0);

				m_BulletReloadTime = 200;
				m_BulletReloadTimeCounter = 0;

				m_Health = 3;
			}
			
			~Eskeletor()
			{

			}
		private:

			void HandleFireBullet()
			{
				if (m_BulletReloadTimeCounter == m_BulletReloadTime)
				{
					BulletHandler::Instance()->AddEnemyBullet(m_position.get_x(), m_position.get_y() + 10, 25, 25, 
															  "ESKELETORBULLET", 19, 19, 1, 800,
															   Math::Vector2D(0, 1),Math::Vector2D(0,0));

					BulletHandler::Instance()->AddEnemyBullet(m_position.get_x(), m_position.get_y() + 10, 25, 25,
															  "ESKELETORBULLET", 19, 19, 1, 800,
															  Math::Vector2D(0, -1), Math::Vector2D(0, 0));

					m_BulletReloadTimeCounter = 0;
				}

				m_BulletReloadTimeCounter++;
			}
		};
	}
}
#endif