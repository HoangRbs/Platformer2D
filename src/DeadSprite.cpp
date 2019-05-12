#include"DeadSprite.h"

namespace HDT_engine
{
	namespace Game
	{
		void DeadSprite::draw()
		{
			Enemy::draw();
		}

		void DeadSprite::update()
		{
			if (!is_dead)
			{
				if (!EnterScreen)
				{
					
					if (m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x() <= game::Instance()->Get_GameWidth() + 320
						&& m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x() > 0 - 320
						&& m_position.get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y() > 0 - 320 &&
						m_position.get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y() <= game::Instance()->Get_GameHeight() + 320)
					{
						EnterScreen = true;
					}

				}
				else           //ENTER SCREEN CMNR
				{
					Enemy::update();           //standard update
				}

			}
		}

		void DeadSprite::clean()
		{
			Enemy::clean();
		}

		void DeadSprite::load(unique_ptr<LoadParams>const& inputParams)
		{
			Enemy::load(inputParams);
		}
	}
}