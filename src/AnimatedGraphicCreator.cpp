#include"AnimatedGraphicCreator.h"

namespace HDT_engine
{
	namespace Game
	{
		GameObject* AnimatedGraphicCreator::createGameObject()
		{
			return new AnimatedGraphic();
		}
	}
}