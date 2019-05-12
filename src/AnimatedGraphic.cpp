#include"AnimatedGraphic.h"
#include"Camera.h"
#include"game.h"
#include"sound/SoundManager.h"

namespace HDT_engine
{
	namespace Game
	{
		void AnimatedGraphic::load(unique_ptr<LoadParams> inputParams)
		{
			PlatformerObject::load(inputParams);       //get all the basic info 

			m_currentColumn = 0;
			m_currentRow = 0;
		}

		void AnimatedGraphic::draw()
		{
			PlatformerObject::draw();
		}

		void AnimatedGraphic::update()
		{
			if (m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x() <= game::Instance()->Get_GameWidth() + 320
				&& m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x() > 0 - 320
				&& m_position.get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y() > 0 - 320 &&
				m_position.get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y() <= game::Instance()->Get_GameHeight() + 320)
			{
				EnterScreen = true;
			}
			else
			{
				EnterScreen = false;
			}

			if (EnterScreen)
			{
				if (m_textureID == "FALLINGLEAVES")
				{
					if (PlayBirdSoundTimeCounter == PlayBirdSoundTime)
					{
						SOUND::SoundManager::Instance()->PlaySoundEffect("BIRDSOUND",0);
						PlayBirdSoundTimeCounter = 0;
					}
					PlayBirdSoundTimeCounter++;
				}
			}
																			 
			PlatformerObject::update();
		}
	}
}