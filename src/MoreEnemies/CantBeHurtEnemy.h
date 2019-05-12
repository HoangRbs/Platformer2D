#pragma once
#include"../Enemy.h"
#include"../BaseObjectCreator.h"

#ifndef CANTBEHURTENEMY_H
#define CANTBEHURTENEMY_H
namespace HDT_engine
{
	namespace Game
	{
		class CantBeHurtEnemy : public Enemy
		{
		public:
			CantBeHurtEnemy();
			virtual ~CantBeHurtEnemy();

			void draw();
			void update();
			void clean();
			void load(unique_ptr<LoadParams>const& inputParams);
			void attack();            ///no nothing in here

		private:
			void handleMovement();

		protected:
		};

		class CantBeHurtEnemyCreator : public BaseObjectCreator
		{
		public:
			CantBeHurtEnemyCreator()
			{

			}

			virtual ~CantBeHurtEnemyCreator()
			{

			}

			GameObject* createGameObject()
			{
				return new CantBeHurtEnemy();
			}

		private:
		};
	}
}
#endif