#include"LevelParser.h"
#include"../Camera.h"
#include"AnimatedTiles.h"
#include"TileMapInfo.h"
#include"../CheckPointObject.h"
#include"../ScrollingBackground.h"
#include"../GainPlayerLife.h"

namespace HDT_engine
{
	namespace LEVEL
	{
		Level* LevelParser::ParseLevel(const char* LevelFilePath)
		{
			TiXmlDocument LevelDocument;
			this->tempLevel = new Level;    //return this if successfully parsed

			if (!LevelDocument.LoadFile(LevelFilePath))
			{
				std::cout << "cannot load/find"<<LevelFilePath<< std::endl;
				return NULL;
			}

			TiXmlElement* MapElement = LevelDocument.RootElement();

			if (MapElement == NULL)
			{
				std::cout << " cannot find Root Element when parsing Level" << std::endl;
				return NULL;
			}

			MapElement->Attribute("width",&num_TileWidthMap);    //Map size
			MapElement->Attribute("height",&num_TileHeightMap);  //Map size
			MapElement->Attribute("tilewidth",&TileWidth);       //tile size
			MapElement->Attribute("tileheight",&TileHeight);     //tile size

			tempLevel->Set_numTileMapWidth(num_TileWidthMap); 
			tempLevel->Set_numTileMapHeight(num_TileHeightMap); 
			
			int MapHeight = num_TileHeightMap * TileHeight;     ///these are used for checking if player fall out of the map
			int MapWidth = num_TileWidthMap * TileWidth;

			TileMapInfo::Instance()->set_TileMapPos_y(0);
			TileMapInfo::Instance()->set_TileMapHeight(MapHeight);
			//parse TileSets into tempLevel's tileSets

			for (TiXmlElement* e = MapElement->FirstChildElement(); e != NULL; e = e ->NextSiblingElement())
			{
				if (e->Value() == std::string("tileset"))
				{
					ParseTileSet(e,tempLevel->Get_TileSets());  
				}
			}

			for (TiXmlElement* e = MapElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
			{
				if (e->Value() == std::string("layer"))                 //TileLayer or CollisionLayer in each for loop
				{
					ParseTileLayer(tempLevel->Get_TileSets() , e , tempLevel->Get_Layers(), tempLevel->Get_CollisionLayers());
				}

				if (e->Value() == std::string("objectgroup"))			//ObjectLayer
				{
					ParseObjectLayer(e, tempLevel->Get_Layers(), tempLevel->Get_CollisionLayers());
				}

			}


			//saving ALREADY KNOWN animatedTiles
			//for more accurate --> look at the TileSet info in LEVEL.tmx
			//REMEMBER TO PUT THIS OUTSIDE OF THE FOR LOOP OR ELSE IT WILL add again and again
			
			/*
			AnimatedTiles::Instance()->createAnimatedTile(32);   //create() always operates first
			AnimatedTiles::Instance()->addAnimatedTile(32, 33);  //add more IDs
			AnimatedTiles::Instance()->set_AnimatingTimeMax(32, 20);

			AnimatedTiles::Instance()->createAnimatedTile(29);   //create() always operates first
			AnimatedTiles::Instance()->addAnimatedTile(29, 30);
			AnimatedTiles::Instance()->set_AnimatingTimeMax(29, 20);
			*/

			//done parsing all the TileSets[...] and Layers

			///FOR SCROLLING BACKGROUND OBJECTS WHICH ARE DEPENDENT ON CAMERA INFO AND PLAYER INFO
			///Camera and Player is done in Objectparser
			for (int i = 0; i < tempLevel->Get_Layers()->size(); i++)
			{
				if (dynamic_cast<ObjectLayer*>(tempLevel->Get_Layers()->at(i)))
				{
					ObjectLayer* tempObjectLayer = dynamic_cast<ObjectLayer*>(tempLevel->Get_Layers()->at(i));
					for (int j = 0; j < tempObjectLayer->Get_m_gameObjects()->size(); j++)
					{
						if (dynamic_cast<Game::ScrollingBackground*>(tempObjectLayer->Get_m_gameObjects()->at(j)))
						{
							dynamic_cast<Game::ScrollingBackground*>(tempObjectLayer->Get_m_gameObjects()->at(j))->LeverParserLoad();
						}
					}

				}
			}

			return tempLevel;
		}

		void LevelParser::ParseTileSet(TiXmlElement* e, std::vector<TileSet>* m_TileSets)
		{
			TileSet tempTileSet;

			
			e->Attribute("firstgid",&tempTileSet.firstGridID);
			e->Attribute("tilewidth",&tempTileSet.tilewidth);
			e->Attribute("tileheight",&tempTileSet.tileheight);
			
			//e->Attribute("margin",&tempTileSet.margin);
			//e->Attribute("spacing",&tempTileSet.spacing);
			//e->FirstChildElement()->Attribute("width",&tempTileSet.image_width);
			//e->FirstChildElement()->Attribute("height",&tempTileSet.image_height);

			tempTileSet.name = e->Attribute("name");

			TiXmlElement* image_Element = NULL;
		
			for (TiXmlElement* e_ = e->FirstChildElement(); e_ != NULL; e_ = e_->NextSiblingElement())
			{
				if (e_->Value() == std::string("image"))   //image element
				{
					image_Element = e_;                    //one TileSet has only on image only so no need to worry
				}

				if (e_->Value() == std::string("properties"))
				{
					for (TiXmlElement* e_2 = e_->FirstChildElement(); e_2 != NULL; e_2 = e_2->NextSiblingElement())
					{

						if (e_2->Attribute("name") == std::string("AnimateInfoFilePath"))  
						{
							//now parsing Animated info //REMEMBER TO DELETE THE ABOVE CODE IN LEVEL PARSER
							ParseTileSetAnimateInfo(e_2,tempTileSet.firstGridID);
						}
					}
				}
			}

			image_Element->Attribute("width", &tempTileSet.image_width);
			image_Element->Attribute("height", &tempTileSet.image_height);
			tempTileSet.num_columns = tempTileSet.image_width / tempTileSet.tilewidth;   //num_columns --> really important

			std::string imageFilePath1 = "src/assets/";
			std::string imageFilePath2 = image_Element->Attribute("source");

			//now it's time to load image(texture) into texture manager
			Graphic::TextureManager::Instance()->load(imageFilePath1.append(imageFilePath2),
													  tempTileSet.name,
													  Graphic::TextureManager::Instance()->get_renderer());


			m_TileSets->push_back(tempTileSet);

		}

		void LevelParser::ParseTileSetAnimateInfo(TiXmlElement* e, int TileSet_FirstGridID)
		{
			TiXmlDocument AnimateInfoDoc;
		
			if ( AnimateInfoDoc.LoadFile(e->Attribute("value")) != NULL )
			{
				TiXmlElement* AnimateTilesElement = AnimateInfoDoc.RootElement();
				if (AnimateTilesElement == NULL)
				{
					cout << "cannot find the root element" << endl;
				}
				else
				{
					for (TiXmlElement* AnimateTileElement = AnimateTilesElement->FirstChildElement();
						 AnimateTileElement != NULL; AnimateTileElement = AnimateTileElement->NextSiblingElement())
					{
						int currentID;

						AnimateTileElement->Attribute("currentID",&currentID);      //save currentID

						//we have to do one more step
						currentID += TileSet_FirstGridID; //now this is our real ID

						//now create a animatedTile with this ID
						AnimatedTiles::Instance()->createAnimatedTile(currentID);

						//we need to take the animation speed (Time)
						int animationTime;
						AnimateTileElement->Attribute("animationTime",&animationTime);
						AnimatedTiles::Instance()->set_AnimatingTimeMax(currentID,animationTime);

						//now another for loop to scan all others ID to form an animatedTile
						for (TiXmlElement* NextID_Element = AnimateTileElement->FirstChildElement(); NextID_Element != NULL;
							NextID_Element = NextID_Element->NextSiblingElement())
						{
							int nextTileID;
							NextID_Element->Attribute("nextTileID",&nextTileID);

							//we have to do one more thing
							nextTileID += TileSet_FirstGridID;

							//then add 
							AnimatedTiles::Instance()->addAnimatedTile(currentID,nextTileID);

							//right now we did what we had to do 
						}

					}
				}


				//TESING OUR FINAL RESULT
				//AnimatedTiles::Instance()->printOut();

			}
			else
			{
				cout << " cannot load file AnimateInfoDoc " << AnimateInfoDoc.ErrorDesc() << endl;
			}
		}


		void LevelParser::ParseTileLayer(std::vector<TileSet>* m_TileSets,
										 TiXmlElement* e,
										 std::vector<Layer*>* m_TileLayers,
										 std::vector<TileLayer*>* m_CollisionLayers)
		{
			int numColumns = num_TileWidthMap; 
			int numRows = num_TileHeightMap;

			TileLayer* tempTileLayer = new TileLayer(TileWidth,TileHeight,numColumns,numRows,*m_TileSets);
			TileLayer* tempCollisionLayer = new TileLayer(TileWidth, TileHeight, numColumns, numRows, *m_TileSets);

			TiXmlElement* DataElement = NULL;
			TiXmlElement* LayerProperties = NULL;

			for (TiXmlElement* E = e->FirstChildElement(); E != NULL; E = E->NextSiblingElement())
			{
				if (E->Value() == std::string("data"))
				{
					DataElement = E;										//was gonna break this loop but just left it like that for...
																			//..more future operation

				}

				if (E->Value() == std::string("properties"))
				{
					LayerProperties = E;
				}
			}

			if (DataElement == NULL)
			{
				std::cout << "cannot find data element" << std::endl;
				return;
			}

			//next thing I need to do:
			//parse the Data --> Decode --> Uncompress --> pass all info into the MapData

			std::vector<std::vector<unsigned int>> MapDataIDs;       //ready to SetTileMapIDs() into the tempTileLayer/or tempCollisionLayer 
															//--> then pushback later
			std::vector<unsigned int> RowDataIDs(num_TileWidthMap);
			
			for (int i = 1; i <= num_TileHeightMap; i++)
			{
				MapDataIDs.push_back(RowDataIDs);           //push all the empty memory first so that it won't cause memory issue
			}

			//decode Base64 here
			std::string decodedIDs;

			for (TiXmlNode* e = DataElement->FirstChild(); e != NULL; e = e->NextSibling())
			{
				TiXmlText* tempTextNode = e->ToText();
				std::string tempData = tempTextNode->Value();
				decodedIDs = base64_decode(tempData);
			}

			//uncompress with zlib here
			vector<unsigned int> uncompressedIDs(num_TileHeightMap * num_TileWidthMap);				   //destination array
			uLongf uncompressIDs_size = num_TileWidthMap * num_TileHeightMap * sizeof(unsigned int);    //destination size
																							   //decodedIDs ---> source array(string)
																							   //decodedIDs.size()  --> source size

			uncompress((Bytef*)&uncompressedIDs[0],&uncompressIDs_size,
					   (const Bytef*)decodedIDs.c_str(),uLong(decodedIDs.size()));

			//we see we pass the address or a vector! --> it means we passing the address of the first element of a vector!!!--->
			//--->that's how it works --> unlike array --> we can pass the array which default passed by reference . but if pass by
			//reference of a vector --> pass by reference of it's first element

			//TESTING PURPOSE
			/*
			for (int i = 0; i < num_TileHeightMap; i++)
			{
				for (int j = 0; j < num_TileWidthMap; j++)
				{
					cout << uncompressedIDs[i * num_TileWidthMap + j] << " ";
				}

				cout << endl;
			}
			*/

			//since zlib only use string of C / not C++ --> convert to c_str() first then casting it to Bytef

			//now we'll gonna pass the uncompressedIDs to the MapDataIDs

			for (int i = 0; i < num_TileHeightMap; i++)
			{
				for (int j = 0; j < num_TileWidthMap; j++)
				{
					MapDataIDs[i][j] = uncompressedIDs[i * num_TileWidthMap + j];
				}
			}

			if (LayerProperties != NULL)
			{
				for (TiXmlElement* LayerProperty = LayerProperties->FirstChildElement();
					 LayerProperty != NULL;
					 LayerProperty = LayerProperty->NextSiblingElement())
				{
					if (LayerProperty->Attribute("name") == std::string("Collidable"))      //collision layer!!
					{
						tempCollisionLayer->SetTileMapIDs(MapDataIDs);
						///now we need to do one more thing --> is...OPTIMIZING FOR PLAYING

						for (int i = 0; i < num_TileHeightMap; i++)
						{
							for (int j = 0; j < num_TileWidthMap; j++)
							{
								int currentID = MapDataIDs[i][j];

								if (currentID == 0)
								{
									continue;
								}

								TileSet* tempTileSet = &tempCollisionLayer->GetTileSetByID(currentID);

								tempCollisionLayer->Get_ID_ItsTileSet()[currentID] = tempTileSet;
							}
						}

						m_CollisionLayers->push_back(tempCollisionLayer);
						m_TileLayers->push_back(tempCollisionLayer);
					}
				}
			}
			else
			{
				tempTileLayer->SetTileMapIDs(MapDataIDs);
				
				///now we need to do one more thing --> is...OPTIMIZING FOR PLAYING
				for (int i = 0; i < num_TileHeightMap; i++)
				{
					for (int j = 0; j < num_TileWidthMap; j++)
					{
						int currentID = MapDataIDs[i][j];

						if (currentID == 0)
						{
							continue;
						}

						TileSet* tempTileSet = &tempTileLayer->GetTileSetByID(currentID);

						tempTileLayer->Get_ID_ItsTileSet()[currentID] = tempTileSet;      ///GOAL of this code
					}
				}

				m_TileLayers->push_back(tempTileLayer);             //done parsing TileLayer
			}
		}

		void LevelParser::ParseObjectLayer(TiXmlElement* e, std::vector<Layer*>* m_Layers, std::vector<TileLayer*>* m_CollisionLayers)
		{
			cout << e->Attribute("name") << endl;

			ObjectLayer* tempObjectLayer = new ObjectLayer();    //create an ObjectLayer to be pushed back later
			TiXmlElement* objectElement = NULL;

			//...now all we need is to create Objects (of a particular TYPE ofcourse)
			//...and then take info from tmx file and pass into it
			//...and finally pushed back into the ObjectLayer we had created earlier

			for (TiXmlElement* e_ = e->FirstChildElement(); e_ != NULL; e_ = e_->NextSiblingElement())
			{
				std::string objectType;										   //these below are default info provided by the TileMapEditor
				int pos_x;
				int pos_y;
				int destRect_width;
				int destRect_height;

				std::string FilePath;										    //these below are custom info created by User(me) 
				std::string textureID;
				std::string FilePathDying;									//used to save EXPLODING texture 
				std::string DyingTextureID;

				int DyingFrameWidth = 0;
				int DyingFrameHeight = 0;
				int DyingNumFrames = 1;                                      //default for all image

				int textureWidth;											    //quite useless for now
				int textureHeight;												//quite useless for now
				
				int FrameWidth;
				int FrameHeight;
				int numFrames = 1;
				int animSpeed = 800;
				double scrollSpeed = 0;

				int CallBackID = 0;

				if (e_->Value() == std::string("object"))
				{

					objectElement = e_;												//parse 1 object right inside here --> cuz in the future 
																					//there will be many objects..
																					//..in this FOR loop
				
					objectType = objectElement->Attribute("type");					
					objectElement->Attribute("x",&pos_x);							//position the object is displayed on the screen
					objectElement->Attribute("y",&pos_y);							//position the object is displayed on the screen
					objectElement->Attribute("width",&destRect_width);				//how the object is displayed(destRect)
					objectElement->Attribute("height",&destRect_height);			//how the object is displayed(destRect)

																					//we no need ro register the create anymore
																					//cuz we already do it in playState onEnter()
																					//and we also try to create object in TileMapEditor...
																					//...and it's type is the same as in our framework
																					//so just need to create object and we done

					TiXmlElement* propertiesElement = NULL;
					for (TiXmlElement* e_1 = objectElement->FirstChildElement(); e_1 != NULL; e_1 = e_1->NextSiblingElement())
					{
						if (e_1->Value() == std::string("properties"))
						{

							propertiesElement = e_1;
																			//now parse properties right inside here..
																			//incase there are many <properties> in this FOR loop
							TiXmlElement* propertyElement = NULL;
							for (TiXmlElement* e_2 = propertiesElement->FirstChildElement(); e_2 != NULL; e_2 = e_2->NextSiblingElement())
							{

								if (e_2->Value() == std::string("property"))
								{
									propertyElement = e_2;
									
									if (propertyElement->Attribute("name") == std::string("FilePath"))  //parse texture into TextureManager
									{
										FilePath = propertyElement->Attribute("value");
									}

									if (propertyElement->Attribute("name") == std::string("CallBackID"))  
									{
										propertyElement->Attribute("value",&CallBackID);
									}

									if (propertyElement->Attribute("name") == std::string("textureID"))
									{
										textureID = propertyElement->Attribute("value");
									}

									if (propertyElement->Attribute("name") == std::string("FilePathDying")) 
									{
										FilePathDying = propertyElement->Attribute("value");
			
									}

									if (propertyElement->Attribute("name") == std::string("DyingTextureID")) 
									{
								
										DyingTextureID = propertyElement->Attribute("value");

									}

									if (propertyElement->Attribute("name") == std::string("textureWidth")) 
									{
										propertyElement->Attribute("value",&textureWidth);                 //quite useless at the time
									}

									if (propertyElement->Attribute("name") == std::string("textureHeight")) 
									{
										propertyElement->Attribute("value",&textureHeight);				   //quite useless at the time
									}

									if (propertyElement->Attribute("name") == std::string("FrameWidth")) 
									{
										propertyElement->Attribute("value", &FrameWidth);				   
									}

									if (propertyElement->Attribute("name") == std::string("FrameHeight")) 
									{
										propertyElement->Attribute("value", &FrameHeight);				   
									}

									if (propertyElement->Attribute("name") == std::string("numFrames")) 
									{
										propertyElement->Attribute("value", &numFrames);						   
									}

									if (propertyElement->Attribute("name") == std::string("animSpeed")) 
									{
										propertyElement->Attribute("value", &animSpeed);
									}

									if (propertyElement->Attribute("name") == std::string("ScrollSpeed"))
									{
										propertyElement->Attribute("value", &scrollSpeed);
									}

									if (propertyElement->Attribute("name") == std::string("DyingFrameWidth"))
									{
										propertyElement->Attribute("value", &DyingFrameWidth);
									}

									if (propertyElement->Attribute("name") == std::string("DyingFrameHeight"))
									{
										propertyElement->Attribute("value", &DyingFrameHeight);
									}

									if (propertyElement->Attribute("name") == std::string("DyingNumFrames"))
									{
						
										propertyElement->Attribute("value", &DyingNumFrames);
									}
								}

							}
						}

					}

					Graphic::TextureManager::Instance()->load(FilePath,textureID,Graphic::TextureManager::Instance()->get_renderer()); 
					Graphic::TextureManager::Instance()->load(FilePathDying,          //dying texture
															  DyingTextureID,
															  Graphic::TextureManager::Instance()->get_renderer());

					//DONE ADDING TEXTURES FOR EACH OBJECT

					Game::GameObject* tempObject = Game::GameObjectFactory::Instance()->createObject(objectType);
					
					unique_ptr<Game::LoadParams> inputParams(new Game::LoadParams(pos_x, pos_y, destRect_width, destRect_height,
																			      textureID,FrameWidth, FrameHeight, numFrames, animSpeed,scrollSpeed,
																				  DyingTextureID,DyingFrameWidth,DyingFrameHeight,DyingNumFrames,CallBackID));
					tempObject->load(inputParams);           

					if (tempObject->Get_objectType() == "Player")             //is it a type of gameobject that is pointing to Player
					{

						tempLevel->Set_LevelPlayer(dynamic_cast<Game::Player*>(tempObject));        
						tempObjectLayer->Set_Player(dynamic_cast<Game::Player*>(tempObject));       
						
						Game::Camera::Instance()->setTargetInfo(&tempObject->Get_Position(),&tempObject->Get_velocity());
						Game::Camera::Instance()->Set_ThePlayer(tempObject);
					}

					//after done creating 1 object at a time
					//add (push back) to the created ObjectLayer

					//setting collision layers for objects ---> remember to ignore ScrollingBackground Object when cheking
					//just doing some shit in each object's update then its fine
					//just don't do in shooterObject update()

					tempObject->set_CollisionLayers(m_CollisionLayers);

					//

					tempObjectLayer->Get_m_gameObjects()->push_back(tempObject);
				
					//saving Moving Platform address into the current object layer
					if (tempObject->Get_objectType() == "MovingPlatform")
					{
						tempObjectLayer->Get_m_MovingPlatforms()->push_back(tempObject);
					}

					if (tempObject->Get_objectType() == "CanBeInsidePlatform")
					{
						tempObjectLayer->Get_m_CanBeInsidePlatforms()->push_back(tempObject);
					}
					//now wait another loop(in parse level()) to scan a new object
				}

			}

			///after parsing the tempObjectLayer  ---> we'll ahave to do one more step 
			///each object (except moving platform) have to have MovingPlatforms vector to check collision later

			for (int i = 0; i < tempObjectLayer->Get_m_gameObjects()->size(); i++)
			{
				tempObjectLayer->Get_m_gameObjects()->at(i)->set_p_MovingPlatforms(tempObjectLayer->Get_m_MovingPlatforms());
				tempObjectLayer->Get_m_gameObjects()->at(i)->set_p_CanBeInsidePlatforms(tempObjectLayer->Get_m_CanBeInsidePlatforms());
			}

			///passing the Player into Enemies / CheckPoint Object -- and Camera(for scrolling bacground init)
			Game::GameObject* p_Player = NULL;

			for (int i = 0; i < tempObjectLayer->Get_m_gameObjects()->size(); i++)
			{
				if (tempObjectLayer->Get_m_gameObjects()->at(i)->Get_objectType() == "Player")
				{
					p_Player = tempObjectLayer->Get_m_gameObjects()->at(i);
					Game::Camera::Instance()->Set_ThePlayer(p_Player);
					break;
				}
			}

			///for check point object / GainPlayerLife and enemy
			for (int i = 0; i < tempObjectLayer->Get_m_gameObjects()->size(); i++)
			{
				if (dynamic_cast<Game::Enemy*>(tempObjectLayer->Get_m_gameObjects()->at(i)))
				{
					Game::Enemy* tempEnemy = dynamic_cast<Game::Enemy*>(tempObjectLayer->Get_m_gameObjects()->at(i));
					tempEnemy->set_Player(p_Player);
				}
				else if (dynamic_cast<Game::CheckPointObject*>(tempObjectLayer->Get_m_gameObjects()->at(i)))
				{
					Game::CheckPointObject* tempCheckPointObject = dynamic_cast<Game::CheckPointObject*>(tempObjectLayer->Get_m_gameObjects()->at(i));
					tempCheckPointObject->set_Player(p_Player);
				}
				else if (dynamic_cast<Game::GainPlayerLife*>(tempObjectLayer->Get_m_gameObjects()->at(i)))
				{
					Game::GainPlayerLife* tempCheckPointObject = dynamic_cast<Game::GainPlayerLife*>(tempObjectLayer->Get_m_gameObjects()->at(i));
					tempCheckPointObject->set_Player(p_Player);
				}
			}

			m_Layers->push_back(tempObjectLayer);
		}
	}
}