#pragma once

#ifndef ENEMY_H
#define ENEMY_H

#include"PlatformerObject.h"
#include"LoadParams.h"
#include"input/InputHandler.h"
#include"BulletHandler.h"

namespace HDT_engine
{
	namespace Game
	{

		class Enemy: public PlatformerObject		//inherit sdl game object
		{
		public:

			Enemy();
			virtual ~Enemy();

			virtual void draw();
			virtual void update();
			virtual void clean();
			virtual void load(unique_ptr<LoadParams>const& inputParams);

			std::string Get_objectType();        //do not override this function --> use for collision detection

			virtual void collision();            //not override anymore --> this is it

			virtual void Detect_Player();
			
			virtual void set_Player(GameObject* Player_)            //Object level parser
			{
				ThePlayer = Player_;
			}
		protected:
			virtual void attack() {};
			virtual void DoDyingAnimation();

			int scrollTime;
			int scrollTimeCounter;
			int m_Health;

			GameObject* ThePlayer = NULL;      ///is used to detect
			int DetectPlayerRange = 250;
			bool RightDetect = false;
			bool LeftDetect = false;

			bool goingLeft = false;
			bool goingRight = false;
		};
	}
}

#endif