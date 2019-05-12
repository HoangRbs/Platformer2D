#include"TileLayer.h"
#include"../game.h"
#include"../Camera.h"
#include"AnimatedTiles.h"

namespace HDT_engine
{
	namespace LEVEL
	{
		TileLayer::TileLayer(int tile_width, int tile_height,
			                 int numColumns, int numRows,
							 const std::vector<TileSet>& tilesets_)

		: m_tilewidth(tile_width), m_tileheight(tile_height),
		  m_numColumns(numColumns), m_numRows(numRows),
		  m_tilesets(tilesets_),
		  m_Mapposition(0,0), m_Mapvelocity(0,0)      
		{
			///m_Mapvelocity.set_x(-1);           //cuz we want the map to move backward as we move forward
			///m_Mapvelocity.set_x(Game::game::Instance()->Get_ScrollVelocity());
			
			m_Mapvelocity.set_x(0);            //fucking adventure the game
		}

		void TileLayer::SetTileMapIDs(const std::vector<std::vector<unsigned int>> &data_tileIDs)
		{
			m_tileMapIDs = data_tileIDs;
		}
		
		void TileLayer::Update()    //scrolling 
		{
			//LET THE CAMERA DO THE WORK
		}

		TileSet& TileLayer::GetTileSetByID(unsigned int currentTileID)
		{
			//The ORDER of tilesets in the m_tilesets is really really important!!!!
			//cuz we SCAN down to the file and PUSHBACK (create order in the m_tilesets)...
			//...and that makes the firstGridID of each tileset is ASCENDING.

			///THIS FOR LOOP IS BAD !!!! --> WE SHOULD DO THIS IN LOAD
			///THE GET TILESET BY ID SHOULD ONLY DONE O(1) TIME
			///IMAGINE DOING O(N) TIMES FOR 6000 TILES --> THAT'S FUCKING NIGHTMARE
			///WE'RE GONNA CREATE A IDs LIST FOR EACH TILE SETS
			///AND WHEN WE COME ACROSS AN ID --> JUST LOOK INTO THE MEMORY OF EACH TILESET THEN WE'LL FINE

			for (int i = 0; i < m_tilesets.size(); i++)
			{
				//case 1 : there are more than 2 tilesets left to compare
				//case 2 : if the currentTileID is in the OUTER MOST tileset--->return that tileset right away

				if ((i + 1) > m_tilesets.size() - 1)  //case 2 --> only one tileset left to compare(OUTER MOST TILESET)
				{									  //but the main ourpose of this is to prevent exceed the for loop..
													  //..since we use both [i] and [i + 1] in the IF() below case 1
					return m_tilesets[i];
				}
				else                                  //case 1
				{
					if (currentTileID >= m_tilesets[i].firstGridID && currentTileID < m_tilesets[i + 1].firstGridID)
					{
						return m_tilesets[i];
					}
				}
			}

			std::cout << "cannot find tileset for the currentTileID in this TileLayer" << std::endl; ///this usually can't happen
			std::cout << "returning empty tileset" << std::endl;
			TileSet temp;
			return temp;
		}

		void TileLayer::Render()     //this is where the magic happens
		{
			//things need to do now
			//after SetTileMapIDs()  --> now we have the IDs to draw!


			///all these shit is just to reduce performance-->since calling function again and again takes fucking memory
			float OptimizeLagCamPos_y = Game::Camera::Instance()->Get_OptimizeLagCamPos_y();
			float OptimizeLagCamPos_x = Game::Camera::Instance()->Get_OptimizeLagCamPos_x();

			int GameWidth = Game::game::Instance()->Get_GameWidth();
			int GameHeight = Game::game::Instance()->Get_GameHeight();

			float MapPosition_y = m_Mapposition.get_y();
			float MapPosition_x = m_Mapposition.get_x();
			///

			for (int i = 0; i < m_numRows; i++)
			{

				//OPTIMIZE --> ONLY DRAW WHERE YOU NEED TO DRAW :3   ---> OUT OF THE SCREEN --> NO DRAW

				if ((MapPosition_y + (i * m_tileheight + m_tileheight)) - OptimizeLagCamPos_y < 0)
				{
					continue;       //no draw the whole row
				}

				if ((MapPosition_y + (i * m_tileheight)) - OptimizeLagCamPos_y > GameHeight + 64)
				{
					continue;	    //no draw the whole row
				}

				for (int j = 0; j < m_numColumns; j++)
				{
					
					//OPTIMIZE --> ONLY DRAW WHERE YOU NEED TO DRAW :3 ---> OUT OF THE SCREEN --> NO DRAW
					if ((MapPosition_x + (j*m_tilewidth + m_tilewidth)) - OptimizeLagCamPos_x < 0)
					{
						continue;    //no draw at the column
					}

					if ((MapPosition_x + (j*m_tilewidth)) - OptimizeLagCamPos_x > GameWidth + 64)
					{
						continue;	 //no draw at the column
					}

					//now start to draw
					unsigned int currentID = m_tileMapIDs[i][j];

					if (currentID == 0)				//draw nothing
					{
						continue;
					}

					currentID = AnimatedTiles::Instance()->getAnimatedTile(currentID);    //than re_calculate the currentID if it is a animatedTile_Index
																						  //it is checked in this function too
																						  //if not --> it is still the same value

					//REMEMBER : the function above will only change currentID but cannot change m_tileMapIDs[i][j]
					//--> which is what we want
					
					/*    WE NO LONGER USE THIS --> IMAGINE ALWAYS CALCULATE THE FOR LOOP FOR MANY TILES (6000 TILES) --> nightmare
					TileSet tempTileSet = GetTileSetByID(currentID);     //if that ID is > 0--> there is always a tileset for it
																		 //because every ID is > 0 on the Map we created from the 
					*/													 //TileSet --> and it is always in the TileSet

					TileSet* tempTileSet = NULL;

					if (ID_ItsTileSet[currentID] != NULL)
					{
						tempTileSet = ID_ItsTileSet[currentID];   ///we'll use this
					}
					else       ///try disable this else to know what's happenning
					{
						tempTileSet = &GetTileSetByID(currentID);
						ID_ItsTileSet[currentID] = tempTileSet;       ///make/save new one so it won't have to go in here to calculate again
					}

					Graphic::TextureManager::Instance()->draw_1_Tile((*tempTileSet).name,
																	 m_tilewidth,
																	 m_tileheight,
																	 (j * m_tilewidth) + MapPosition_x - OptimizeLagCamPos_x,
																	 (i * m_tileheight) + MapPosition_y - OptimizeLagCamPos_y,
																	 (currentID - (*tempTileSet).firstGridID)%(*tempTileSet).num_columns,
																	 (currentID - (*tempTileSet).firstGridID)/(*tempTileSet).num_columns);

				}
			}
		}

		void TileLayer::Clean()
		{
			m_tilesets.clear();
			m_tileMapIDs.clear();
		}

		int TileLayer::Get_MapWidthSize()
		{
			return m_numColumns * m_tilewidth;
		}

		int TileLayer::Get_MapHeightSize()
		{
			return m_numRows * m_tileheight;
		}
	}
}