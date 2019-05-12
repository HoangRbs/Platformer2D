#pragma once
#ifndef LEVEL_H
#define LEVEL_H

#include"TileSet.h"
#include"Layer.h"
#include"TileLayer.h"
#include"../Player.h"
#include"../CollisionManager.h"

#include<vector>

namespace HDT_engine
{
	namespace LEVEL
	{
		class Level						//designing level
		{
		public:
			Level();
			void Render();
			void Update();
			void Clean();

			std::vector<Layer*>* Get_Layers();		//points to its Layers[...]
			std::vector<TileSet>* Get_TileSets();   //points to its tilesets[...]
			std::vector<TileLayer*>* Get_CollisionLayers();

			Game::Player* Get_LevelPlayer();
			void Set_LevelPlayer(Game::Player* m_Player_);
		private:
			std::vector<TileSet> m_tilesets;        
			std::vector<Layer*> m_layers;           //both TileLayer and ObjectLayer type in here
			std::vector<TileLayer*> m_CollisionLayers;  //this is only for Collision Layer (Tile Layer type)

			Game::Player* m_Player;                 //to saperate from other gameobjects --> set in parseObjectLayers
			Game::CollisionManager m_CollisionManager;            //COLLISION MANAGER

			//these below are used in Level update() check collision section
			//the reason for this is to avoid the PLAYER fly out of the map and check collision turns into SHIT
			int m_numTileMapWidth;
			int m_numTileMapHeight;

		public:
			void Set_numTileMapWidth(int input_numTileMapWidth_) { m_numTileMapWidth = input_numTileMapWidth_; }     //this is used in level parser 
			void Set_numTileMapHeight(int input_numTileMapHeight_) { m_numTileMapHeight = input_numTileMapHeight_; } //this is used in level parser
			
		};
	}
}

#endif 

