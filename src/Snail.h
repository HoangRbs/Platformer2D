#pragma once
#ifndef SNAIL_H
#define SNAIL_H

#include"Enemy.h"
#include"BaseObjectCreator.h"

namespace HDT_engine
{
	namespace Game
	{
		class Snail: public Enemy
		{
		public:
			Snail() {}
			~Snail() {}

			virtual void draw();
			virtual void update();
			virtual void clean();
			virtual void load(unique_ptr<LoadParams>const& inputParams);

		private:
			
			void handleMovement();
			virtual void attack();
		};

		class SnailCreator : public BaseObjectCreator
		{
		public:
			SnailCreator()
			{

			}

			GameObject* createGameObject()
			{
				return new Snail();
			}
		private:
		};
	}
}

#endif