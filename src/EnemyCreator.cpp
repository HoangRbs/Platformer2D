#include"EnemyCreator.h"

namespace HDT_engine
{
	namespace Game
	{
		GameObject* EnemyCreator::createGameObject()
		{
			return new Enemy();
		}
	}
}