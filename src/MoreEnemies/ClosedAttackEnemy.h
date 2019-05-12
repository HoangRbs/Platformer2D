#pragma once
#include"../Enemy.h"
#include"../BaseObjectCreator.h"

#ifndef CLOSEDATTACKENEMY_H
#define CLOSEDATTACKENEMY_h
namespace HDT_engine
{
	namespace Game
	{
		class ClosedAttackEnemy : public Enemy
		{
		public:
			ClosedAttackEnemy();
			~ClosedAttackEnemy();

			void draw();
			void update();
			void clean();
			void load(unique_ptr<LoadParams>const& inputParams);

		private:
			void attack();
			void handleMovement();
			void handleAnimation();
			void checkPlayerAttack();

			const int changeDirectionTime = 280;
			int changeDirectionTimeCounter = 0;

			const int attackingTime = 100;
			int attackingTimeCounter = 0;

			bool hurt = false;
			const int hurtTime = 30;
			int hurtTimeCounter = 0;
			void Hurt();

		protected:
		};

		class ClosedAttackEnemyCreator : public BaseObjectCreator
		{
		public:
			ClosedAttackEnemyCreator()
			{

			}

			virtual ~ClosedAttackEnemyCreator()
			{

			}

			GameObject* createGameObject()
			{
				return new ClosedAttackEnemy();
			}
		private:
		};
	}
}

#endif