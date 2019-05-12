#pragma once
#ifndef BASEOBJECTCREATOR_H
#define BASEOBJECTCREATOR_H

#include"GameObject.h"

namespace HDT_engine
{
	namespace Game
	{
		class BaseObjectCreator
		{
		public:
			virtual GameObject* createGameObject() = 0;
			//virtual ~BaseObjectCreator() = 0;              //virtual destructor --> gonna find out later

			BaseObjectCreator();
		};
	}
}
#endif
