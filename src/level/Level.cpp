#include"Level.h"
#include"../game.h"
#include"../CollisionManager.h"

namespace HDT_engine
{
	namespace LEVEL
	{
		Level::Level()
		{

		}

		void Level::Update()
		{
			
			for (int i = 0; i < m_layers.size(); i++)
			{
				m_layers[i]->Update();         //both objects layers ,tiled layers, collision layers
			}

			if(m_Player != NULL)       ///the MenuLevel does not have PlayerPointer
				m_CollisionManager.CheckPlayer_EnemyBulletCollision(m_Player);
	
		}

		void Level::Render()
		{
	
			for (int i = 0; i < m_layers.size(); i++)
			{
				m_layers[i]->Render();        //both object layer and TileLayer is in here
			}								  //which has scrollingBackground Layers(Tilelayer type) --> cover the CollisionLayer if
											  //collision layer is rendered first  
											  //-->so always put collision layer renderer second --> it makes sense in real life though

		}

		std::vector<TileSet>* Level::Get_TileSets()
		{
			return &m_tilesets;
		}

		std::vector<Layer*>* Level::Get_Layers()
		{
			return &m_layers;
		}

		std::vector<TileLayer*>* Level::Get_CollisionLayers()
		{
			return &m_CollisionLayers;
		}

		Game::Player* Level::Get_LevelPlayer()
		{
			return this->m_Player;
		}

		void Level::Set_LevelPlayer(Game::Player* m_Player_)
		{
			this->m_Player = m_Player_;
		}

		void Level::Clean()
		{
			m_tilesets.clear();
			for (int i = 0; i < m_layers.size(); i++)
			{
				m_layers.at(i)->Clean();      //clean the small parts first
				delete m_layers.at(i);        //then free the memory
			}
			m_layers.clear();

			/*  -->we do not need to do this anymore --> the above function already delete our collision layer
			for (int i = 0; i < m_CollisionLayers.size(); i++)
			{
				m_CollisionLayers.at(i)->Clean();
				delete m_CollisionLayers.at(i);
			}
			*/

			m_CollisionLayers.clear();
		}
	}
}