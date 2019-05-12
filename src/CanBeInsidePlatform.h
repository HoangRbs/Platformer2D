#pragma once
#ifndef CANBEINSIDEPLATFORM_H
#define CANBEINSIDEPLATFORM_H

#include"PlatformerObject.h"
#include"BaseObjectCreator.h"

namespace HDT_engine
{
	namespace Game
	{
		class CanBeInsidePlatform: public PlatformerObject           ///WATER, LADDER , ROPE
		{
		public:
			virtual ~CanBeInsidePlatform()
			{

			}

			virtual void draw();
			virtual void update();						
			virtual void clean();						
			virtual void load(unique_ptr<LoadParams>const &inputParams);  
			
			virtual float& Get_DefaultMaxVelocityLimiter();

			virtual std::string Get_objectType()
			{
				return "CanBeInsidePlatform";
			}

		private:

		protected:
			CanBeInsidePlatform()
			{

			}
		};

	    ///this class' constructor is protected so we cannot make a creator class for this(what we want)
		///cannot use gameObject* sfsrf = new CanBeInsidePlatform()  !!!!
	}
}
#endif