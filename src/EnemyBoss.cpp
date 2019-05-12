#include"EnemyBoss.h"
#include"Game.h"
#include"Camera.h"

namespace HDT_engine
{
	namespace Game
	{
		void EnemyBoss::update()
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

					if (m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x() <= game::Instance()->Get_GameWidth() + 320
						&& m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x() > 0 - 320
						&& m_position.get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y() > 0 - 320 &&
						m_position.get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y() <= game::Instance()->Get_GameHeight() + 320)
					{
						EnterScreen = true;
						m_velocity.set_x(0);
						m_velocity.set_y(-1);
					}

				}
				else               //IN THE SCREEN CMNR
				{
					if (!is_dying)
					{
			
						if (m_textureID == std::string("ENEMYBOSS"))  //is the EnemyBoss texture-->look at assets Enemy/EnemyBoss and
																	  //more info at Level.tmx in TileMapEditor
						{

							if (m_currentColumn == 7)   //is the 7th Frame when the EnemyBoss use the WEAPON
							{

								BulletHandler::Instance()->AddEnemyBullet(m_position.get_x(), m_position.get_y() + 10,
																		  m_screenWidth,m_screenHeight,
																		  "ENEMYBOSSBULLET",15,26, 1, 800,
																		  Math::Vector2D(-2, 0), Math::Vector2D(-1, 0));
								
								BulletHandler::Instance()->AddEnemyBullet(m_position.get_x(), m_position.get_y() + 10,
																		  m_screenWidth, m_screenHeight/2,
																		  "WEIRDBULLET1", 32, 32, 2, 200,
																		  Math::Vector2D(-2, 0), Math::Vector2D(0, 0));

								//SOUND::SoundManager::Instance()->PlaySoundEffect("EnemyBossSword",0);

							}
						}
						else
						{
							HandleFireBullet();           //OTHER BOSSES
						}
						
						//Scroll(game::Instance()->Get_ScrollVelocity());  --> it won't scroll "forward anymore"
						//now we have to make out own movement in this
				        if (m_position.get_y() <= 0)
					    {
							m_velocity.set_y(1);
					    }
					    else if ((m_position.get_y() + m_screenHeight) >= game::Instance()->Get_GameHeight())
					    {
							m_velocity.set_y(-1);
					    }

							
					
					}

					Enemy::update();           //standard update
				}

			}
		}

		void EnemyBoss::collision()
		{
			
			game::Instance()->Set_CurrentBossLevelLives(game::Instance()->Get_CurrentBossLevelLives() - 1);

			if (game::Instance()->Get_CurrentBossLevelLives() == 0)  
			{
				//change texture id first
				//m_textureID = "ENEMYDYING";        //you know what asset to look for

												   //set dying to true --> prevent checking collision again too
				//is_dying = true;

				//texture changed --> Frames changes
				//m_currentColumn = 0;
				//m_currentRow = 0;

				//m_numFrames = 8;
				//m_FrameHeight = 172;
				//m_FrameWidth = 242;

				//int temp = BOSSLEVEL_1_LIVESMAX;
				//game::Instance()->Set_BossLevel_1_Lives(temp);  --> no need this --> we do this in game update()

				//Enemy::collision();

				//set dying to true --> prevent checking collision again too
				is_dying = true;

				//texture changed --> Frames changes
				m_currentColumn = 0;
				m_currentRow = 0;
			}
		}
	}
}