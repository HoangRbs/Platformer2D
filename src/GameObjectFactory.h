#pragma once

#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include<map>
#include<string>
#include"BaseObjectCreator.h"

namespace HDT_engine
{
	namespace Game
	{

		class GameObjectFactory                //SINGLETON -->right now it is not used yet  --> 
		{
		public:
			bool registerCreator(std::string typeID,BaseObjectCreator* passed_creator);

			GameObject* createObject(std::string typeID);

			static GameObjectFactory* Instance();

		private:
			map<std::string,BaseObjectCreator*> m_gameObjectCreators;
			static GameObjectFactory* instance;
			GameObjectFactory();
		};
	}
};
#endif
