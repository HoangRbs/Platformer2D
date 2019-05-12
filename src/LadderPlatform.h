#pragma once
#ifndef LADDERPLATFORM_H
#define LADDERPLATFORM_H

#include"CanBeInsidePlatform.h"

namespace HDT_engine
{
	namespace Game
	{
		class LadderPlatform : public CanBeInsidePlatform
		{
		public:
			virtual~ LadderPlatform()
			{

			}

			LadderPlatform(): CanBeInsidePlatform()
			{

			}

			virtual void draw();
			virtual void update();
			virtual void clean();
			virtual void load(unique_ptr<LoadParams>const &inputParams);

		private:

		protected:

		};

		class LadderPlatformCreator : public BaseObjectCreator
		{
		public:
			LadderPlatformCreator()
			{

			}

			GameObject* createGameObject()
			{
				return new LadderPlatform();
			}
		private:
		};
	}
}
#endif