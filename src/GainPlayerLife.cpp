#include "GainPlayerLife.h"
#include"Camera.h"
#include"game.h"
#include"Collision.h"
#include"Player.h"
#include"sound/SoundManager.h"

namespace HDT_engine
{
	namespace Game
	{
		void GainPlayerLife::draw()
		{
			if(!is_dead)
				PlatformerObject::draw();
		}

		void GainPlayerLife::update()
		{
			if (!is_dead)
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
						m_position.get_y() + m_screenHeight - Camera::Instance()->Get_OptimizeLagCamPos_y() < 0 ||
						m_position.get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y() > game::Instance()->Get_GameHeight())

					{
						EnterScreen = false;
					}

					CheckPlayerCollide();

					//update like normal
					PlatformerObject::update();
				}
			}
		}

		void GainPlayerLife::clean()
		{
			PlatformerObject::clean();
		}

		void GainPlayerLife::load(unique_ptr<LoadParams>const &inputParams)
		{
			PlatformerObject::load(inputParams);
		}

		void GainPlayerLife::CheckPlayerCollide()
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
				if (game::Instance()->Get_PlayerLives() < 6)
				{
					is_dead = true;
					game::Instance()->Set_PlayerLives(game::Instance()->Get_PlayerLives() + 1);
					SOUND::SoundManager::Instance()->PlaySoundEffect("PICKUPGAINPLAYERLIFESOUND",0);
				}

			}

			delete Rect_1;
			delete Rect_2;
		}
	}
}