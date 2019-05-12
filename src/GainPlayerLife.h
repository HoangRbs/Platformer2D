#pragma once

#ifndef GAINPLAYERLIFE_H
#define GAINPLAYERLIFE_H

#include "PlatformerObject.h"
#include "BaseObjectCreator.h"


namespace HDT_engine
{
	namespace Game
	{
		class GainPlayerLife : public PlatformerObject
		{
		public:
			GainPlayerLife()
			{

			}

			virtual ~GainPlayerLife()
			{

			}

			virtual void draw();
			virtual void update();						//standard animation and standard movement
			virtual void clean();						//over ride --> but not implement in this class
			virtual void load(unique_ptr<LoadParams>const &inputParams);   //over ride
			virtual void set_Player(GameObject* Player_)   ///lever parser
			{
				ThePlayer = Player_;
			}

		private:

			void CheckPlayerCollide();
			GameObject * ThePlayer = NULL;
		};


		class GainPlayerLifeObjectCreator : public BaseObjectCreator
		{
		public:
			GainPlayerLifeObjectCreator()
			{

			}

			virtual ~GainPlayerLifeObjectCreator()
			{

			}

			GameObject* createGameObject()
			{
				return new GainPlayerLife();
			}
		private:
		};
	}
}
#endif
