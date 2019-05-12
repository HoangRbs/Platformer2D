#pragma once
#ifndef SHOTGLIDERCREATOR_H
#define SHOTGLIDERCREATOR_H

#include"BaseObjectCreator.h"
#include"ShotGlider.h"

namespace HDT_engine
{
	namespace Game
	{
		class ShotGliderCreator: public BaseObjectCreator
		{
		public:
			GameObject * createGameObject()
			{
				return new ShotGlider();
			}

			ShotGliderCreator()
			{

			}
		private:
		};
	}
}
#endif