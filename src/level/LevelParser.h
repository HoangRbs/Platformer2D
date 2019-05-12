#pragma once
#ifndef LEVELPARSER_H
#define LEVELPARSER_H

#include"Level.h"
#include"Layer.h"
#include"TileLayer.h"
#include"ObjectLayer.h"
#include"zlib.h"
#include"../ThirdParty/tinyxml.h"
#include"../ThirdParty/BASE64/base64.h"
#include"../graphic/TextureManager.h"

#include"../GameObjectFactory.h"                     //to create object RANDOM_SHIT whose type is...
#include"../EnemyCreator.h"
#include"../GameObject.h"
#include"../Enemy.h"								 //...enemy
#include"../LoadParams.h"

#include<iostream>

namespace HDT_engine
{
	namespace LEVEL
	{
		class LevelParser         //this kind of class will be used in PlayState      
		{
			//this class will parse TileSets[...] and Layers[....] into...
			//created Level object

		public:
			Level* ParseLevel(const char* LevelFilePath);
		private:
			Level * tempLevel;

			int num_TileWidthMap;     //so_Tile chieu rong cua Map
			int num_TileHeightMap;    //so_Tile chieu cao cua Map
			int TileWidth;			  //Tile Size    ----> parse into TileLayer
			int TileHeight;			  //Tile Size    ----> parse into TileLayer

			void ParseTileSet(TiXmlElement* e, std::vector<TileSet>* m_TileSets); //push each tileset into created Level's m_TileSets[...]

			void ParseTileSetAnimateInfo(TiXmlElement* e,int TileSet_FirstGridID);           //in used in ParseTileSet

			void ParseTileLayer(std::vector<TileSet>* m_TileSets,
								TiXmlElement* e, 
								std::vector<Layer*>* m_TileLayers,
								std::vector<TileLayer*>* m_CollisionLayers);    //push each TileLayer into created Level's m_TileLayers[...]

			void ParseObjectLayer(TiXmlElement* e, std::vector<Layer*>* m_Layers ,std::vector<TileLayer*>* m_CollisionLayers);

		};
	}
}
#endif // !LEVELPARSER_H
