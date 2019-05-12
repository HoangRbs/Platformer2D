#include"PlayerCreator.h"

namespace HDT_engine
{
	namespace Game
	{
		GameObject* PlayerCreator::createGameObject()
		{
			return new Player();
		}

		PlayerCreator::PlayerCreator()
		{

		}
	}
}