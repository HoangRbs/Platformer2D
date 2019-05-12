#pragma once
#ifndef ANIMATEDTILES_H
#define ANIMATEDTILES_H

#include<iostream>
#include<map>
#include<vector>

namespace HDT_engine
{
	namespace LEVEL
	{
		class AnimatedTiles       //SINGLETON
		{
		public:
			enum ANIMATING_TIME   //is used as INDEXES in m_AnimatingTime Map's vector below
			{
				AnimatingTimeCounter = 0,
				AnimatingTimeMax = 1
			};

			static AnimatedTiles* Instance();

			bool isAnimatedTile(unsigned int currentID);        //is used in getAnimatedTile()

			unsigned int  getAnimatedTile(unsigned int currentID);       //is used in TileLayer::render()

			void addAnimatedTile(unsigned int currentID,unsigned int animatedID);       //is used in LevelParser --> doing it manually and remember 
																	   //in code for now
			
			void createAnimatedTile(unsigned int currentID);           //first we have to make a vector with a currentID is the first ID "frame"
															  //this is used in LevelParser 

			//NEXT feature : since each Tile "currentID" animation speed is different --> we'll make an array to store these
			//SIMPLE AS FUCK


			//ANIMATING TIME
			void set_AnimatingTimeMax(unsigned int currentID,unsigned int TimeMax);                  //is used in LevelParser()

			//COUNTER SYSTEM CHECKING
			void set_DoneOneFrameToPlusCounterForAll();

			//TESING IN LEVEL PARSER
			void printOut();

			//WE NEED TO MAKE A CLEAN FUNCTION FOR IT AS IT CHANGE TO A NEW PLAY STATE(LEVEL 2)
			void Clean();                     //this is done in PlayState Exit()

		private:
			AnimatedTiles()
			{

			}

			std::map<unsigned int, std::vector<unsigned int>> m_AnimatedTileIDs;
			std::map<unsigned int,unsigned int> m_currentFrame;
			std::map<unsigned int, std::vector<unsigned int>> m_animatingTime;

			static AnimatedTiles* instance;

			//COUNTER SYSTEM CHECKING
			//look into getAnimateTile for more detail
			std::map<int, bool> DoneOneFrameToPlusCounter;  //is init in createAnimatedTile
		};
	}
}

#endif