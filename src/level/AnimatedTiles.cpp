#include"AnimatedTiles.h"
#include"../game.h"

namespace HDT_engine
{
	namespace LEVEL
	{
		bool AnimatedTiles::isAnimatedTile(unsigned int currentID)
		{
			if (m_AnimatedTileIDs[currentID].size() > 0)  //the vector size() > 0 --> means the Tile is animated type
			{
				return true;
			}

			return false;
		}

		unsigned int AnimatedTiles::getAnimatedTile(unsigned int currentID) //keep changing the current TileID
		{
			
			unsigned int saveStandardID = currentID;              //save standard first or else things will be scrull up

			if (isAnimatedTile(saveStandardID))                   //this is an animated Tile      
			{
			
				unsigned int currentID_animatedTileSize = m_AnimatedTileIDs[saveStandardID].size();
				currentID = m_AnimatedTileIDs[saveStandardID].at(m_currentFrame[saveStandardID]);

				
				if (m_animatingTime[saveStandardID].at(AnimatingTimeCounter) == m_animatingTime[saveStandardID].at(AnimatingTimeMax))
				{
					
					m_currentFrame[saveStandardID] = (m_currentFrame[saveStandardID] + 1) % currentID_animatedTileSize;
					//change frame

					m_animatingTime[saveStandardID].at(AnimatingTimeCounter) = 0;       //reset
				}

				if (DoneOneFrameToPlusCounter[saveStandardID])         //look at my paper for more info
				{
					m_animatingTime[saveStandardID].at(AnimatingTimeCounter)++;

					DoneOneFrameToPlusCounter[saveStandardID] = false;  //or the same currentID in one frame will go in here and plus counter again
																		//which is not what we want

					//Done one frame to plus counter for ALL IDs to TRUE when all IDs is scanned -> means that one FRAME update or render is finished
					//and ready to plus Counter for ALL IDs for the next FRAME
					//this is done in main.cpp
				}
			}
			
			return currentID;        
		}

		void AnimatedTiles::addAnimatedTile(unsigned int currentID,unsigned int animatedID)
		{	
			if (m_AnimatedTileIDs[currentID].size() == 0)
			{
				std::cout << " did not create animated Tile previously with initial ID : "<<currentID<< std::endl;
			}
			else
				m_AnimatedTileIDs[currentID].push_back(animatedID);            //DONE :D
		}

		void AnimatedTiles::createAnimatedTile(unsigned int currentID)
		{
			m_AnimatedTileIDs[currentID].push_back(currentID);   //DONE :D
			m_currentFrame[currentID] = 0;        //always start at frame 0
			DoneOneFrameToPlusCounter[currentID] = false;      //we do not want to plus counter at that Tile(currentID) yet
		}


		void AnimatedTiles::set_AnimatingTimeMax(unsigned int currentID,unsigned int TimeMax)
		{
			if (m_AnimatedTileIDs[currentID].size() == 0)
			{
				std::cout << " did not create animated Tile previously with initial ID : " << currentID << std::endl;
			}
			else
			{
				m_animatingTime[currentID].push_back(0);    //always push back two times first
				m_animatingTime[currentID].push_back(0);

				m_animatingTime[currentID].at(AnimatingTimeCounter) = 0;            //always start at 0
				m_animatingTime[currentID].at(AnimatingTimeMax) = TimeMax;
			}
		}

		//TESING
		void AnimatedTiles::printOut()
		{
			
			for(auto i = m_AnimatedTileIDs.begin() ; i != m_AnimatedTileIDs.end() ; i++)
			{
				cout << i->first<< " :";

				for (int j = 0; j < (i->second).size(); j++)
				{
					cout << (i->second).at(j) << " ";
				}

				cout << endl;

			}
		}

		void AnimatedTiles::set_DoneOneFrameToPlusCounterForAll()   //SET TO TRUE FOR ALL --> READY FOR THE NEXT FRAME
		{
			//if we clear the memory --> this won't be done as well --> no need to worry about memory shit

			for (auto i = DoneOneFrameToPlusCounter.begin(); i != DoneOneFrameToPlusCounter.end(); i++)
			{
				i->second = true;   //DONE :D
			}
		}

		void AnimatedTiles::Clean()
		{
			m_AnimatedTileIDs.clear();
			m_currentFrame.clear();
			m_animatingTime.clear();
			DoneOneFrameToPlusCounter.clear();
		}

		AnimatedTiles* AnimatedTiles::instance = NULL;

		AnimatedTiles* AnimatedTiles::Instance()
		{
			if (instance == NULL)
			{
				instance = new AnimatedTiles();
			}
			
			return instance;
		}
	}
}