#pragma once
#ifndef ENEMYCREATOR_H
#define ENEMYCREATOR_H
#include"BaseObjectCreator.h"
#include"Enemy.h"

namespace HDT_engine
{
	namespace Game
	{
		class EnemyCreator : public BaseObjectCreator
		{
		public:
			GameObject * createGameObject();
		private:
		};
	}
}
#endif
