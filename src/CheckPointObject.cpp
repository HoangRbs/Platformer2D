#include"CheckPointObject.h"
#include"Camera.h"
#include"game.h"
#include"Collision.h"
#include"Player.h"
#include"sound/SoundManager.h"

namespace HDT_engine
{
	namespace Game
	{
		void CheckPointObject::draw()
		{
			PlatformerObject::draw();
		}

		void CheckPointObject::update()
		{
			if (!EnterScreen)
			{

				if (m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x() <= game::Instance()->Get_GameWidth()
					&& m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x() > 0 
					&& m_position.get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y() > 0 &&
					m_position.get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y() <= game::Instance()->Get_GameHeight())
				{
					EnterScreen = true;
				}

			}
			else           //ENTER SCREEN CMNR
			{
				if (m_position.get_x() + m_screenWidth - Camera::Instance()->Get_OptimizeLagCamPos_x() < 0 ||
					m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x() > game::Instance()->Get_GameWidth() ||
					m_position.get_y() + m_screenHeight - Camera::Instance()->Get_OptimizeLagCamPos_y() < 0  ||
					m_position.get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y() > game::Instance()->Get_GameHeight())

				{
					EnterScreen = false;
				}

				if (m_textureID == "LASTCHECKPOINT")
				{
					if (PlayerFuckHimBeforeLevelComplete)
					{
						if (PlayerFuckTimeCounter == PlayerFuckTime)
						{
							PlayerFuckTimeCounter = 0;
							game::Instance()->Set_Level_Complete(true);
						}
						PlayerFuckTimeCounter++;

						dynamic_cast<Player*>(ThePlayer)->makePlayerInvisible();
						dynamic_cast<Player*> (ThePlayer)->set_Position(m_position);
					}
				}

				CheckPlayerCollide();

				//update like normal
				PlatformerObject::update();

				
			}
		}

		void CheckPointObject::clean()
		{
			PlatformerObject::clean();
		}

		void CheckPointObject::load(unique_ptr<LoadParams>const &inputParams)
		{
			PlatformerObject::load(inputParams);
		}

		void CheckPointObject::CheckPlayerCollide()
		{
		
			SDL_Rect* Rect_1 = new SDL_Rect();
			SDL_Rect* Rect_2 = new SDL_Rect();

			Rect_1->x = ThePlayer->Get_Position().get_x();
			Rect_1->y = ThePlayer->Get_Position().get_y();
			Rect_1->w = ThePlayer->Get_ScreenWidth();
			Rect_1->h = ThePlayer->Get_ScreenHeight();

			Rect_2->x = m_position.get_x();
			Rect_2->y = m_position.get_y();
			Rect_2->w = m_screenWidth;
			Rect_2->h = m_screenHeight;

			if (Rects_Collided(Rect_1, Rect_2))
			{
				if (PlayerCollideTimeCounter == 0)         ///at the first time Player Collide
				{
					PlayerCollideOneTime = true;
				}
				else
				{
					PlayerCollideOneTime = false;
				}

				if (m_textureID == "LASTCHECKPOINT")
				{
					PlayerFuckHimBeforeLevelComplete = true;

					m_currentRow = 1;
					m_numFrames = 4;

					///hide the Player --> to make Player invisible
					dynamic_cast<Player*>(ThePlayer)->makePlayerInvisible();

					///save Player at that position
					Math::Vector2D newPos = m_position;
					newPos.set_y(newPos.get_y() - 50);  ///avoid stick into the ground
					dynamic_cast<Player*> (ThePlayer)->set_CheckPointPos(newPos);
				}
				else
				{
					Math::Vector2D newPos = m_position;
					newPos.set_y(newPos.get_y() - 50);  ///avoid stick into the ground
					dynamic_cast<Player*> (ThePlayer)->set_CheckPointPos(newPos);
				}

				PlayerCollideTimeCounter++;

				//handle sound
				if (PlayerCollideOneTime)
				{
					SOUND::SoundManager::Instance()->PlaySoundEffect("CHECKPOINTSOUND", 0);
				}
			}
			else            ///not collide anymore!
			{
				PlayerCollideTimeCounter = 0;
			}


			delete Rect_1;
			delete Rect_2;
		}
	}
}