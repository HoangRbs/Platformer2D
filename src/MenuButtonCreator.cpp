#include"MenuButtonCreator.h"

namespace HDT_engine
{
	namespace Game
	{
		GameObject* MenuButtonCreator::createGameObject()
		{
			return new MenuButton;
		}

		MenuButtonCreator::MenuButtonCreator()
		{

		}
	}
}