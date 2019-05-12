#pragma once
#ifndef ENEMYBOSSCREATOR_H
#define ENEMYBOSSCREATOR_H

#include"BaseObjectCreator.h"
#include"EnemyBoss.h"

namespace HDT_engine
{
	namespace Game
	{
		class EnemyBossCreator : public BaseObjectCreator
		{
		public:
			GameObject * createGameObject()
			{
				return new EnemyBoss();
			}

			EnemyBossCreator()
			{

			}

			~EnemyBossCreator()
			{

			}
		private:
		};
	}
}
#endif