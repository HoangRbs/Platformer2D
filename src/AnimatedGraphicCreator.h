#pragma once
#ifndef ANIMATEDGRAPHICCREATOR_H
#define ANIMATEDGRAPHICCREATOR_H

#include"BaseObjectCreator.h"
#include"AnimatedGraphic.h"

namespace HDT_engine
{
	namespace Game
	{
		class AnimatedGraphicCreator: public BaseObjectCreator
		{
		public:
			GameObject* createGameObject();
		private:
		};
	}
}
#endif
