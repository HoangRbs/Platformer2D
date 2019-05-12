#pragma once
#ifndef TILESET_H
#define TILESET_H

#include<string>

namespace HDT_engine
{
	namespace LEVEL
	{
		struct TileSet
		{
			int firstGridID;         
			int tilewidth;
			int tileheight;
			int num_columns;     //number of columns   --> to calculate ---> create my own formular
			
			int spacing;       //later ( = 0 for now)
			int margin;		   //later ( = 0 for now)

			int image_width;   //width of the img source(tileset img)
			int image_height;  //height of the img source(tileset img)

			std::string name;  //used as ID in textureManager
		};
	}
}
#endif
