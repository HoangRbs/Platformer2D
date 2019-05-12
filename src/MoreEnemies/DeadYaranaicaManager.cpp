#include "DeadYaranaicaManager.h"
#include"iostream"
#include"../Camera.h"
#include"../game.h"
#include"../LoadParams.h"

namespace HDT_engine
{
	namespace Game
	{
		DeadYaranaicaManager* DeadYaranaicaManager::instance = NULL;

		DeadYaranaicaManager* DeadYaranaicaManager::Instance()
		{
			if (instance == NULL)
			{
				instance = new DeadYaranaicaManager();
			}

			return instance;
		}

		void DeadYaranaicaManager::YaranaicasUpdate()
		{
			float OptimizeLagCamPos_x = Camera::Instance()->Get_OptimizeLagCamPos_x();
			float OptimizeLagCamPos_y = Camera::Instance()->Get_OptimizeLagCamPos_y();
			int GameWidth = game::Instance()->Get_GameWidth();
			int GameHeight = game::Instance()->Get_GameHeight();

			for (int i = 0; i < m_DeadYaranaicas.size(); /*no i++ here*/)
			{
				if (m_DeadYaranaicas.at(i)->isDead()
					|| m_DeadYaranaicas.at(i)->Get_Position().get_x() - OptimizeLagCamPos_x < 0
					|| m_DeadYaranaicas.at(i)->Get_Position().get_x() - OptimizeLagCamPos_x > GameWidth
					|| m_DeadYaranaicas.at(i)->Get_Position().get_y() - OptimizeLagCamPos_y < 0
					|| m_DeadYaranaicas.at(i)->Get_Position().get_y() - OptimizeLagCamPos_y > GameHeight)
				{
					delete m_DeadYaranaicas.at(i);
					m_DeadYaranaicas.erase(m_DeadYaranaicas.begin() + i);
				}
				else            //update normally
				{
					m_DeadYaranaicas.at(i)->set_EnterScreen(true);
					m_DeadYaranaicas.at(i)->update();
					i++;			//this is important
				}
			}
		}

		void DeadYaranaicaManager::YaranaicasDraw()
		{
			for (int i = 0; i < m_DeadYaranaicas.size(); i++)
			{
				m_DeadYaranaicas.at(i)->draw();
			}
		}

		void DeadYaranaicaManager::YaranaicaAdd(float pos_x, float pos_y, int screenWidth_, int screenHeight_, std::string textureID_, 
												int FrameWidth_, int FrameHeight_, int numFrames_, int animSpeed_)
		{
			DeadYaranaica* temp = new DeadYaranaica();

			unique_ptr<LoadParams> inputParams(new LoadParams(pos_x,pos_y,screenWidth_,screenHeight_,textureID_,FrameWidth_,FrameHeight_,
															  numFrames_,animSpeed_,0,"0",0,0,0));

			temp->load(inputParams);

			m_DeadYaranaicas.push_back(temp);
		}

		void DeadYaranaicaManager::YaranaicasClear()
		{
			///no need to delete pointer since we aready did that in Update

			m_DeadYaranaicas.clear();
		}
	}
}