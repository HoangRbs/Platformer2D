#pragma once

#ifndef DEADYARANAICA_H
#define DEADYARANAICA_H

#include"../PlatformerObject.h"

namespace HDT_engine
{
	namespace Game
	{
		class DeadYaranaica : public PlatformerObject
		{
		public:
			DeadYaranaica() : PlatformerObject()
			{

			}

			virtual ~DeadYaranaica()
			{

			}

			virtual void draw()
			{
				PlatformerObject::draw();
			}

			virtual void update()
			{

				//ENTESCREEN OF DeadYaranaica IS SET IN its HANDLER
				///only if EnterScreen = true --> we can access into Platformer::update() section
				
				m_alpha -= 1;

				if (EnterScreen)
				{
					if (m_alpha <= 0)
					{
						is_dead = true;
					}
				}

				PlatformerObject::update();
			}

			virtual void clean()
			{

				PlatformerObject::clean();
			}

			virtual void load(unique_ptr<LoadParams> const& inputParams)
			{
				PlatformerObject::load(inputParams);

				m_velocity.set_x(0);
				m_velocity.set_y(-1);

				m_alpha = 255;
			}

			virtual std::string Get_objectType()
			{
				return ("DeadYaranaica");
			}

			void set_EnterScreen(bool input)
			{
				EnterScreen = input;
			}

		private:
		};
	}
}
#endif
