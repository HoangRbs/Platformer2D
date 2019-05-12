#pragma once
#ifndef ESKELETORCREATOR_H
#define ESKELETORCREATOR_H

#include"BaseObjectCreator.h"
#include"Eskeletor.h"

namespace HDT_engine
{
	namespace Game
	{
		class EskeletorCreator: public BaseObjectCreator
		{
		public:
			GameObject * createGameObject()
			{
				return new Eskeletor();
			}

			EskeletorCreator()
			{

			}
		private:
		};
	}
}
#endif