
#pragma once
#ifndef STATEPARSE_H
#define STATEPARSE_H

#include<iostream>
#include<vector>

#include"../../GameObject.h"
#include"../../GameObjectFactory.h"

#include"../../ThirdParty/tinyxml.h"
#include"../../graphic/TextureManager.h"

namespace HDT_engine
{
	namespace FSM
	{
		class StateParser
		{
		public:
			//parse the state first ?  --> this will run once in Enter() in STATES
			bool ParseState(const char* stateFilePath, std::string StateID, 
													   std::vector<Game::GameObject*> *p_Objects,
													   std::vector<std::string> *p_TextureID);

		private:
			//parse the state's objects ? --> will run in parseState()
			void parseObjects(TiXmlElement* Objects_Root, std::vector<Game::GameObject*> *p_Objects);   //will be used in ParseState()
			//parse the state's Textures ? --> will run in parseState()
			void parseTextures(TiXmlElement* Textures_Root, std::vector<std::string> *p_TextureID);	   //will be used in ParseState()
		};
	}
}
#endif

