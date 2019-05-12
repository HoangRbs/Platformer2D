#include"WaterPlatform.h"

namespace HDT_engine
{
	namespace Game
	{
		void WaterPlatform::draw()
		{
			CanBeInsidePlatform::draw();
		}

		void WaterPlatform::update()
		{
			CanBeInsidePlatform::update();
		}

		void WaterPlatform::clean()
		{
			CanBeInsidePlatform::clean();
		}

		void WaterPlatform::load(unique_ptr<LoadParams>const &inputParams)
		{
			CanBeInsidePlatform::load(inputParams);

			DEFAUT_MAXVELOCITYLIMITER = 0.03f;
			
			m_MaxVelocityLimiter = 0;           ///these platform do not need these right now
		}
	}
}