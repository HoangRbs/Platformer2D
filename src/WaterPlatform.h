#pragma once
#ifndef WATERPLATFORM_H
#define WATERPLATFORM_H

#include"CanBeInsidePlatform.h"

namespace HDT_engine
{
	namespace Game
	{
		class WaterPlatform :public CanBeInsidePlatform
		{
		public:
			virtual ~WaterPlatform()
			{

			}

			WaterPlatform():CanBeInsidePlatform()
			{

			}

			virtual void draw();
			virtual void update();
			virtual void clean();
			virtual void load(unique_ptr<LoadParams>const &inputParams);

		private:

		};

		class WaterPlatformCreator : public BaseObjectCreator
		{
		public:
			WaterPlatformCreator()
			{

			}

			GameObject* createGameObject()
			{
				return new WaterPlatform();
			}
		private:
		};
	}
}
#endif