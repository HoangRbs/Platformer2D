#pragma once
#ifndef GLIDERCREATOR_H
#define GLIDERCREATOR_H
#include"BaseObjectCreator.h"
#include"Glider.h"

namespace HDT_engine
{
	namespace Game
	{
		class GliderCreator: public BaseObjectCreator
		{
		public:
			GameObject* createGameObject()
			{
				return new Glider();
			}

			GliderCreator()
			{

			}
		private:
		};
	}
}
#endif