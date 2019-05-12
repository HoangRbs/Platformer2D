#include"LadderPlatform.h"

namespace HDT_engine
{
	namespace Game
	{
		void LadderPlatform::draw()
		{
			CanBeInsidePlatform::draw();
		}

		void LadderPlatform::update()
		{
			CanBeInsidePlatform::update();
		}

		void LadderPlatform::clean()
		{
			CanBeInsidePlatform::clean();
		}

		void LadderPlatform::load(unique_ptr<LoadParams>const &inputParams)
		{
			CanBeInsidePlatform::load(inputParams);

			DEFAUT_MAXVELOCITYLIMITER = 0.06f;  ///for other objects to get

			m_MaxVelocityLimiter = 0;           ///these platform do not need these right now
		}
	}
}