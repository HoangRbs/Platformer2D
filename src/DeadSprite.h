#pragma once
#ifndef DEADSPRITE_H
#define DEADSPRITE_H

#include"Enemy.h"
#include"BaseObjectCreator.h"

namespace HDT_engine
{
	namespace Game
	{
		class DeadSprite : public Enemy
		{
		public:
			DeadSprite():Enemy()
			{

			}

			virtual ~DeadSprite()
			{

			}

			virtual void draw();
			virtual void update();
			virtual void clean();
			virtual void load(unique_ptr<LoadParams>const& inputParams);
		private:
		};

		class DeadSpriteCreator:public BaseObjectCreator
		{
		public:
			DeadSpriteCreator()
			{

			}

			GameObject* createGameObject()
			{
				return new DeadSprite();
			}
		private:
		};
	}
}

#endif