#pragma once
#ifndef CHECKPOINTOBJECT_H
#define CHECKPOINTOBJECT_H
#include"PlatformerObject.h"
#include"BaseObjectCreator.h"

namespace HDT_engine
{
	namespace Game
	{
		class CheckPointObject : public PlatformerObject
		{
		public:
			CheckPointObject()
			{

			}

			virtual ~CheckPointObject()
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

			///for LASTCHECKPOINT textureID only
			bool PlayerFuckHimBeforeLevelComplete = false;      
			const int PlayerFuckTime = 500;
			int PlayerFuckTimeCounter = 0;

			///look into PlayerCollide  --> to handle playing sound effect better
			int PlayerCollideTimeCounter = 0;
			bool PlayerCollideOneTime = false;
		};

		class CheckPointObjectCreator : public BaseObjectCreator
		{
		public:
			CheckPointObjectCreator()
			{

			}

			~CheckPointObjectCreator()
			{

			}

			GameObject* createGameObject()
			{
				return new CheckPointObject();
			}
		private:
		};
	}
}
#endif
