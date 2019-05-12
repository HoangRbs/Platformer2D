#pragma once
#ifndef MENUBUTTONCREATOR_H
#define MENUBUTTONCREATOR_H

#include"BaseObjectCreator.h"
#include"MenuButton.h"

namespace HDT_engine
{
	namespace Game
	{
		class MenuButtonCreator : public BaseObjectCreator
		{
		public:
			GameObject * createGameObject();

			MenuButtonCreator();
		};
	}
}
#endif
