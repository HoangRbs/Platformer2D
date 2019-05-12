
#include"StateParse.h"

namespace HDT_engine
{
	namespace FSM
	{
		bool StateParser::ParseState(const char* stateFilePath, std::string StateID, 
																std::vector<Game::GameObject*> *m_Objects,
																std::vector<std::string> *m_TexturesID)
		{


			TiXmlDocument xmlDoc;      //create an blank xml Doc

			if (!xmlDoc.LoadFile(stateFilePath))
			{
				cerr<< xmlDoc.ErrorDesc() <<endl;
				return false;
			}


			//get the root element
			TiXmlElement* Root = xmlDoc.RootElement();        //The <STATES> element
			if (Root == NULL)
			{
				cout << "cannot find root element" << endl;
				return false;
			}

			TiXmlElement* StateRoot = NULL;
			for (TiXmlElement* temp_StateRoot = Root->FirstChildElement();
				 temp_StateRoot != NULL; 
				 temp_StateRoot = temp_StateRoot->NextSiblingElement())
			{
				if (temp_StateRoot->Value() == string(StateID))           //if the current Value == passed in StateID(the one that need to find to parse)
				{
					StateRoot = temp_StateRoot;							  //now we found the current needed StateRoot to Parse
					break;
				}
			}

			if (StateRoot == NULL)
			{
				cout << " the STATE value in XML file and in the current class are different" << endl;
				return false;
			}

			TiXmlElement* Textures_Root = NULL;
			for (TiXmlElement* temp_Texture_Root = StateRoot->FirstChildElement();
				 temp_Texture_Root != NULL;
				 temp_Texture_Root = temp_Texture_Root->NextSiblingElement())
			{
				if (temp_Texture_Root->Value() == string("TEXTURES"))
				{
					Textures_Root = temp_Texture_Root;
					break;
				}
			}


			parseTextures(Textures_Root,m_TexturesID);                             //now it's time to parse textures

			TiXmlElement* GameObjects_Root = NULL;
			for (TiXmlElement* temp_GameObjects_Root = StateRoot->FirstChildElement();
				 temp_GameObjects_Root != NULL;
				 temp_GameObjects_Root = temp_GameObjects_Root->NextSiblingElement())
			{
				if (temp_GameObjects_Root->Value() == string("GAMEOBJECTS"))
				{
					GameObjects_Root = temp_GameObjects_Root;
					break;
				}
			}

			parseObjects(GameObjects_Root,m_Objects);							//now it's time to parse objects

			return true;
		}

		void StateParser::parseObjects(TiXmlElement* Objects_Root, std::vector<Game::GameObject*> *m_Objects)
		{
			//will use gameObjectFactory --> a bit comlicated
			for (TiXmlElement* gameobject_elem = Objects_Root->FirstChildElement();
				gameobject_elem != NULL;
				gameobject_elem = gameobject_elem->NextSiblingElement())
			{


				int pos_x, pos_y, height, width, m_callBackID, m_FrameWidth, m_FrameHeight;
				int numFrames = 1;                 //by default it is only one numFrame
				int DyingNumFrames = 1;
				int animSpeed = 800;               //
				int scrollSpeed = 0;
				int DyingFrameWidth = 0;
				int DyingFrameHeight = 0;

				string textureID;
				string DyingTextureID;
				string gameObject_type;

				gameobject_elem->Attribute("pos_x",&pos_x);
				gameobject_elem->Attribute("pos_y",&pos_y);
				gameobject_elem->Attribute("height",&height);
				gameobject_elem->Attribute("width",&width);
				gameobject_elem->Attribute("m_callBackID", &m_callBackID);
				gameobject_elem->Attribute("FrameWidth", &m_FrameWidth);
				gameobject_elem->Attribute("FrameHeight", & m_FrameHeight);
				gameobject_elem->Attribute("ScrollSpeed",&scrollSpeed);
				
				if (gameobject_elem->Attribute("numFrames") != NULL)		//for animate object only
				{
					gameobject_elem->Attribute("numFrames", &numFrames);
				}

				if (gameobject_elem->Attribute("animSpeed") != NULL)		//for animate object only
				{
					gameobject_elem->Attribute("animSpeed", &animSpeed);
				}

				textureID = gameobject_elem->Attribute("textureID");
				gameObject_type = gameobject_elem->Attribute("type");       //use as ID for creator in map

				Game::GameObject* current_object = Game::GameObjectFactory::Instance()->createObject(gameObject_type);
				
				unique_ptr<Game::LoadParams> inputParams(new Game::LoadParams(pos_x, pos_y, width, height, textureID,
														 m_FrameWidth, m_FrameHeight, numFrames, animSpeed,scrollSpeed,
														 DyingTextureID,DyingFrameWidth,DyingFrameHeight,DyingNumFrames,
														 m_callBackID));

				current_object->load(inputParams);        //it's unique_ptr so we'll have a little different Load

				//after parsing --> we have to push the created object into the Objects vector (of the current state)
				m_Objects->push_back(current_object);
			}
		}

		void StateParser::parseTextures(TiXmlElement* Textures_Root, std::vector<std::string> *m_TexturesID)
		{
			for (TiXmlElement* texture_elem = Textures_Root->FirstChildElement();
				 texture_elem != NULL;
				 texture_elem = texture_elem->NextSiblingElement())
			{
				string filepath = texture_elem->Attribute("filepath");
				string texture_id = texture_elem->Attribute("ID");

				m_TexturesID->push_back(texture_id);

				if (!Graphic::TextureManager::Instance()->load(filepath, 
															   texture_id,
															   Graphic::TextureManager::Instance()->get_renderer()))
				{
					cout << "cannot parse texture in "<< endl;
					exit(-1);
				}
			}
		}
	}
	
}
