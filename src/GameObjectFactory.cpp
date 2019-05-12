
#include "GameObjectFactory.h"
namespace HDT_engine
{
	namespace Game
	{
		bool GameObjectFactory::registerCreator(std::string typeID, BaseObjectCreator* passed_creator)
		{
			auto it = m_gameObjectCreators.find(typeID);

			if (it != m_gameObjectCreators.end())     //exist (already registered the passed creator)
			{
				delete passed_creator;
				return false;
			}

			//if not register
			m_gameObjectCreators[typeID] = passed_creator;
			return true;
		}

		GameObject* GameObjectFactory::createObject(std::string typeID)
		{
			auto it = m_gameObjectCreators.find(typeID);

			if (it == m_gameObjectCreators.end())       //not found the needed ID (which is actually the Object type)
			{
				cout << "cannot find any creator ID like that" << endl;
				return NULL;
			}

			//if found
			return it->second->createGameObject();
		}

		GameObjectFactory* GameObjectFactory::Instance()
		{
			if (instance == NULL)
			{
				instance = new GameObjectFactory();
			}

			return instance;
		}


		GameObjectFactory* GameObjectFactory::instance = NULL;

		GameObjectFactory::GameObjectFactory()
		{

		}
	}
}