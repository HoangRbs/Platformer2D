#pragma once
#ifndef DEADYARANAICAMANAGER_H
#define DEADYARANAICAMANAGER_H

#include"vector"
#include"DeadYaranaica.h"

namespace HDT_engine
{
	namespace Game
	{
		class DeadYaranaicaManager             ///singleton --> this class make things funny er
		{
		public:
			~DeadYaranaicaManager()
			{

			}

			static DeadYaranaicaManager* Instance();

			void YaranaicasUpdate();
			void YaranaicasDraw();
			void YaranaicaAdd(float pos_x, float pos_y, int screenWidth_, int screenHeight_, std::string textureID_,
							  int FrameWidth_, int FrameHeight_, int numFrames_, int animSpeed_);
			void YaranaicasClear();

		private:

			DeadYaranaicaManager()
			{

			}

			static DeadYaranaicaManager* instance;
			
			std::vector<DeadYaranaica*> m_DeadYaranaicas;
		};
	}
}
#endif
