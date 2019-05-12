#pragma once
#ifndef PLAYERCREATOR_H
#define PLAYERCRAETOR_H

#include"BaseObjectCreator.h"
#include"Player.h"

namespace HDT_engine
{
	namespace Game
	{
		class PlayerCreator : public BaseObjectCreator
		{
		public:
			virtual GameObject* createGameObject();
			PlayerCreator();
		private:
		};
	}
}
#endif