#include"BulletHandler.h"
#include"game.h"
#include"Camera.h"

namespace HDT_engine
{
	namespace Game
	{
		BulletHandler::BulletHandler()
		{

		}

		BulletHandler::~BulletHandler()
		{

		}

		void BulletHandler::UpdateBullets()
		{
			float OptimizeLagCamPos_x = Camera::Instance()->Get_OptimizeLagCamPos_x();
			float OptimizeLagCamPos_y = Camera::Instance()->Get_OptimizeLagCamPos_y();
			int GameWidth = game::Instance()->Get_GameWidth();
			int GameHeight = game::Instance()->Get_GameHeight();

			for (int i = 0; i < m_PlayerBullets.size(); /*no i++ here*/)
			{
			
				if (m_PlayerBullets.at(i)->isDead() 
					|| m_PlayerBullets.at(i)->Get_Position().get_x() - OptimizeLagCamPos_x < 0
					|| m_PlayerBullets.at(i)->Get_Position().get_x() - OptimizeLagCamPos_x > GameWidth
					|| m_PlayerBullets.at(i)->Get_Position().get_y() - OptimizeLagCamPos_y < 0
					|| m_PlayerBullets.at(i)->Get_Position().get_y() - OptimizeLagCamPos_y > GameHeight)
				{
					delete m_PlayerBullets.at(i);
					m_PlayerBullets.erase(m_PlayerBullets.begin() + i);
				}
				else            //update normally
				{
					m_PlayerBullets.at(i)->set_EnterScreen(true);
					m_PlayerBullets.at(i)->update();
					i++;			//this is important
				}
			}

			for (int i = 0; i < m_EnemyBullets.size(); /*no i++ here*/)
			{
				if (m_EnemyBullets.at(i)->isDead() 
					|| m_EnemyBullets.at(i)->Get_Position().get_x() - OptimizeLagCamPos_x < 0
					|| m_EnemyBullets.at(i)->Get_Position().get_x() - OptimizeLagCamPos_x > GameWidth
					|| m_EnemyBullets.at(i)->Get_Position().get_y() - OptimizeLagCamPos_y < 0
					|| m_EnemyBullets.at(i)->Get_Position().get_y() - OptimizeLagCamPos_y > GameHeight)
				{
					delete m_EnemyBullets.at(i);
					m_EnemyBullets.erase(m_EnemyBullets.begin() + i);
				}
				else            //update normally
				{
					m_EnemyBullets.at(i)->set_EnterScreen(true);
					m_EnemyBullets.at(i)->update();
					i++;         //this is important
				}
			}

		}

		void BulletHandler::DrawBullets()
		{
			for (int i = 0; i < m_PlayerBullets.size(); i++)
			{
				m_PlayerBullets.at(i)->draw();
			}

			for (int i = 0; i < m_EnemyBullets.size(); i++)
			{
				m_EnemyBullets.at(i)->draw();
			}
		}

		void BulletHandler::AddPlayerBullet(int pos_x, int pos_y,int screenWidth_,int screenHeight_,std::string textureID_,
											int FrameWidth_, int FrameHeight_, int numFrames_, int animSpeed_,
											Math::Vector2D BulletVel_, Math::Vector2D BulletAcc_)
		{

			PlayerBullet* temp = new PlayerBullet();       //we won't use gameObjectFactory here :D

			unique_ptr<LoadParams> inputParams(new LoadParams(pos_x,pos_y,screenWidth_,screenHeight_,textureID_,
															  FrameWidth_,FrameHeight_,numFrames_,animSpeed_,
															  0,"0",0,0,0,0,BulletVel_,BulletAcc_));

			temp->load(inputParams);

			m_PlayerBullets.push_back(temp);
		}

		void BulletHandler::AddEnemyBullet(int pos_x, int pos_y, int screenWidth_, int screenHeight_, std::string textureID_,
										   int FrameWidth_, int FrameHeight_, int numFrames_, int animSpeed_,
										   Math::Vector2D BulletVel_, Math::Vector2D BulletAcc_)
		{
			EnemyBullet* temp = new EnemyBullet();

			unique_ptr<LoadParams> inputParams(new LoadParams(pos_x, pos_y, screenWidth_, screenHeight_, textureID_,
															  FrameWidth_, FrameHeight_, numFrames_, animSpeed_,
															  0,"0",0,0,0,0,BulletVel_,BulletAcc_));
			temp->load(inputParams);

			m_EnemyBullets.push_back(temp);
		}

		void BulletHandler::BulletsClear()
		{
			m_PlayerBullets.clear();
			m_EnemyBullets.clear();
		}

		BulletHandler* BulletHandler::instance = NULL;

		BulletHandler* BulletHandler::Instance()
		{
			if (instance == NULL)
			{
				instance = new BulletHandler();
			}

			return instance;
		}

		std::vector<PlayerBullet*>* BulletHandler::Get_PlayerBullets()
		{
			return &m_PlayerBullets;
		}

		std::vector<EnemyBullet*>* BulletHandler::Get_EnemyBullets()
		{
			return &m_EnemyBullets;
		}
	}
}