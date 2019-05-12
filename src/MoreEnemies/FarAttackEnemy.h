#pragma once
#include"../Enemy.h"
#include"../BaseObjectCreator.h"

#ifndef FARATTACKENEMY_H
#define FARATTACKENEMY_H

namespace HDT_engine
{
	namespace Game
	{
		class FarAttackEnemy : public Enemy
		{
		public:
			FarAttackEnemy();
			~FarAttackEnemy();

			void draw();
			void update();
			void clean();
			void load(unique_ptr<LoadParams>const& inputParams);
			void attack();

		private:

			void handleMovement();
			void handleFireBullet();
			void handleAnimation();
			void checkPlayerAttack();

			bool hurt = false;
			const int hurtTime = 30;
			int hurtTimeCounter = 0;
			void Hurt();

		protected:
		};

		class FarAttackEnemyCreator : public BaseObjectCreator
		{
		public:
			FarAttackEnemyCreator()
			{

			}

			virtual ~FarAttackEnemyCreator()
			{

			}

			GameObject* createGameObject()
			{
				return new FarAttackEnemy();
			}
		private:
		};
	}
}
#endif