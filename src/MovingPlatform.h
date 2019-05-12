#pragma once
#ifndef MOVINGPLATFORM_H
#define MOVINGPLATFORM_H
#include"BaseObjectCreator.h"
#include"PlatformerObject.h"
namespace HDT_engine
{
	namespace Game
	{
		class MovingPlatform :public PlatformerObject
		{
		public:
			MovingPlatform();
			virtual ~MovingPlatform();

			virtual void draw();
			virtual void update();
			virtual void clean();
			virtual void load(unique_ptr<LoadParams>const& inputParams);

			virtual std::string Get_objectType();
		private:

			int Magnitude = 60;  ///--> maximum 13 blocks movement for now (1 middle block - 6 block each side - width size = 3 blocks)
			Math::Vector2D InitialPoint;
		};

		class MovingPlatformCreator: public BaseObjectCreator
		{
			public:
				MovingPlatformCreator() {}
				GameObject* createGameObject()
				{
					return new MovingPlatform();
				}
		};
	}
}


#endif