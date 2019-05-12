#pragma once
#ifndef ANIMATEDGRAPHIC_H
#define ANIMATEDGRAPHIC_H

#include"PlatformerObject.h"

namespace HDT_engine
{
	namespace Game
	{
		class AnimatedGraphic : public PlatformerObject       //just another kind of SDLgameObject plus some other features
		{
		public:
			void load(unique_ptr<LoadParams> inputParams);    //animated graphic has full feature of a SDLgameobject
																						//moreover, it has 2 more features
			void draw();
			void update();

		private:
			int m_animSpeed;
			int m_numFrames;

			int PlayBirdSoundTimeCounter = 0;
			const int PlayBirdSoundTime = 1000;
		};
	}
}
#endif
