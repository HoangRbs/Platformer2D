#pragma once
#ifndef TILELAYER_H
#define TILELAYER_H

#include"Layer.h"
#include"../math/Vector2D.h"
#include"TileSet.h"
#include"../graphic/TextureManager.h"

#include<vector>

namespace HDT_engine
{
	namespace LEVEL
	{
		class TileLayer: public Layer									   //this type of layer is only made of Tile entirely
		{
		public:
			TileLayer(int tile_width, int tile_height,
					  int numColumns, int numRows,
					  const std::vector<TileSet>& tilesets_);				//init and pass from outside
			
			void Render();                                          //over ride
			void Update();										    //over ride
			void Clean();

			void SetTileMapIDs(const std::vector<std::vector<unsigned int>> &data_tileIDs);     //tileIDs are passed from outside !
																					   //---> is parsed from Level maybe -->
																					   //decompressed ---> decode --> tileIDs (map)

			Math::Vector2D Get_MapPosition()        //is used in Collision Manager
			{
				return m_Mapposition;
			}

			int Get_TileSize()						//is used in Collision Manager 
													///--> now it is used in CheckCollideTile() in Objects
			{
				return m_tileheight;
			}

			std::vector<std::vector<unsigned int>>* Get_tileMapIDs() { return &m_tileMapIDs; }  //is used in Collision Manager 
																					 ///--> now it is used in CheckCollideTile() in Objects
			int Get_MapWidthSize();													 ///is used in CheckCollideTile                    
			int Get_MapHeightSize();												 ///is used in CheckCollideTile

			///this is used in Parse TileLayer
			std::map<unsigned int, TileSet*>& Get_ID_ItsTileSet()
			{
				return ID_ItsTileSet;
			}

			///now this will be used in Parse TileLayer too
			TileSet& GetTileSetByID(unsigned int currentTileID);

		private:
			int m_numColumns;				//so cot cua 1 TileLayer   
			int m_numRows;					//so hang cua 1 TileLayer   
			int m_tilewidth;				//tile size
			int m_tileheight;				//tile size

			int scrollMapTime = 2;          //if we want the TileMap to run slower
			int scrollMapTimeCounter = 0;

			Math::Vector2D m_Mapposition;		//to scroll the map
			Math::Vector2D m_Mapvelocity;		//to scroll the map

			std::vector<TileSet> m_tilesets;					  //is passed from the outside from Level into TileLayer
			std::vector<std::vector<unsigned int>> m_tileMapIDs;  //we'll gonna render right in TileLayer --> it needs tileMapIDs and...
																  //..tilesets to draw()...
																  //..for short --> this class is where all the magic things happen
			
			std::map<unsigned int, TileSet*> ID_ItsTileSet;
			///this is used to Optimize the Get_TileSetByID (which is used in the game when Playing --> since this has many calculation)
			///--->so move to load in Parsing TileLayer
			///this MAP will be used to get TileSet when accessing current ID when playing --> fast as fuck 0(1)
		};
	}
}
#endif