#pragma once
#ifndef TILEMAPINFO_H
#define TILEMAPINFO_H
#include<iostream>

namespace HDT_engine
{
	namespace LEVEL
	{
		class TileMapInfo                ///singleton ---> is used to check if the objects are falling out of the map
										 ///---> this class is used in ObjectLayer
										 ///--->WE'RE GONNA ONLY NEED TO PASS THE MAP INTO IN PARSE LEVEL
										 ///since the Map stand still the whole game and we only move the camera
		{
		public:
			static TileMapInfo* Instance()
			{
				if (instance == NULL)
				{
					instance = new TileMapInfo();
				}

				return instance;
			}

			float& get_TileMapPos_y()
			{
				return TileMapPos_y;
			}

			int& get_TileMapHeight()
			{
				return TileMapHeight;
			}

			void set_TileMapPos_y(float input_y)
			{
				TileMapPos_y = input_y;
			}

			void set_TileMapHeight(int inputHeight)
			{
				TileMapHeight = inputHeight;
			}


			///we're gonna have clean function in the future

		private:
			TileMapInfo()
			{

			}

			float TileMapPos_y = 0;          ///position of the map in the game -->  == 0 for now
			int TileMapHeight;

			static TileMapInfo* instance;
		};
	}
}
#endif