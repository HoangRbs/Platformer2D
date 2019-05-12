#pragma once
#ifndef LAYER_H
#define LAYER_H

#include"TileSet.h"

namespace HDT_engine
{
	namespace LEVEL
	{
		class Layer			//abstract only
		{
		public:
			virtual void Render() = 0;
			virtual void Update() = 0;
			virtual void Clean() = 0;
		private:
		};
	}
}
#endif
