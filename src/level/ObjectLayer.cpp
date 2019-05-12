#include"ObjectLayer.h"
#include"../BulletHandler.h"         //testing
#include"../game.h"
#include"../MovingPlatform.h"
#include"TileMapInfo.h"

namespace HDT_engine
{
	namespace LEVEL
	{
		void ObjectLayer::Update()
		{
			///for optimization
			int TileMapInfo_y_plus_height = TileMapInfo::Instance()->get_TileMapPos_y() + TileMapInfo::Instance()->get_TileMapHeight();

			for (int i = 0; i < m_gameObjects.size(); i++)
			{
				
				m_gameObjects[i]->update();

				if (m_gameObjects[i]->Get_objectType() == "Player" || m_gameObjects[i]->Get_objectType() == "Enemy")
				{
					if (m_gameObjects[i]->Get_Position().get_y() - 500 > TileMapInfo_y_plus_height)
					{
						m_gameObjects[i]->collision();
					}
				}

			}

			if (m_Player != NULL)			//we have to do this cuz we have a new Object Layer that only has 1 ScrollingBackground
											//object --> no Player --> no enemies -->so Player will be NULL
			{
				//m_CollisionManager.CheckEnemies_PlayerBulletsCollision(m_gameObjects);        //though if Player == NULL --> there will be no 
				m_CollisionManager.CheckPlayer_EnemiesCollision(m_Player, m_gameObjects);	  //Player Bullet --> make sense
			}
		}

		void ObjectLayer::Render()
		{
			for (int i = 0; i < m_gameObjects.size(); i++)
			{
				m_gameObjects[i]->draw();
			}
		}

		void ObjectLayer::Clean()
		{
			for (int i = 0; i < m_gameObjects.size(); i++)
			{
				m_gameObjects.at(i)->clean();
				delete m_gameObjects.at(i);
			}

			m_gameObjects.clear();
		}

		std::vector<Game::GameObject*>* ObjectLayer::Get_m_gameObjects()
		{
			return &m_gameObjects;
		}

		std::vector<Game::GameObject*>* ObjectLayer::Get_m_MovingPlatforms()
		{
			return &m_MovingPlatforms;
		}

		std::vector<Game::GameObject*>* ObjectLayer::Get_m_CanBeInsidePlatforms()
		{
			return &m_CanBeInsidePlatforms;
		}


		void ObjectLayer::Set_Player(Game::Player* inputPlayer_)
		{
			this->m_Player = inputPlayer_;
		}
	}
}