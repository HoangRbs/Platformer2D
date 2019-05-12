#include"CanbeInsidePlatform.h"
#include"Camera.h"
#include"game.h"

namespace HDT_engine
{
	///THE SPECIAL THING IS THAT-->THESE OBJECT WON'T HAVE TEXTURE-->WE'LL JUST GONNA MODIFIFY WHERE THE OBJECT IS IN THE
	///TILE MAP EDITOR --> IT'S POSITION AND SIZE WILL COVER THE WATER TILES OR LADDER TILES

	namespace Game
	{
		void CanBeInsidePlatform::draw()
		{
			//PlatformerObject::draw(); ---> do not need this
		}

		void CanBeInsidePlatform::update()
		{
			if (!EnterScreen)
			{

				if (m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x() <= game::Instance()->Get_GameWidth()
					&& m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x() > 0
					&& m_position.get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y() > 0 &&
					m_position.get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y() <= game::Instance()->Get_GameHeight())
				{
					EnterScreen = true;
				}

			}
			else           //ENTER SCREEN CMNR
			{
				if (m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x() < 0 - m_screenWidth ||
					m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x() > game::Instance()->Get_GameWidth() ||
					m_position.get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y() < 0 - m_screenHeight ||
					m_position.get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y() > game::Instance()->Get_GameHeight())

				{
					EnterScreen = false;        //outside of the screen --> look at the specific enemy type 
												//to see how EnterScreen is used in its update() function
												//the purpose of EnterScreen is just to reduce the CPU when 
												//checking collision detection
				}
			}

			PlatformerObject::update();
		}

		void CanBeInsidePlatform::clean()
		{
			PlatformerObject::clean();
		}

		void CanBeInsidePlatform::load(unique_ptr<LoadParams>const &inputParams)
		{
			PlatformerObject::load(inputParams);

			///since the object standstill
			m_MaxVelocityLimiter = 0;
			m_acceleration.set_x(0);
			m_acceleration.set_y(0);
			m_velocity.set_x(0);
			m_velocity.set_y(0);

			///the DEFAULT one will be gotten the Player --> look into Platformer Object for more detail
		}

		float& CanBeInsidePlatform::Get_DefaultMaxVelocityLimiter()
		{
			return DEFAUT_MAXVELOCITYLIMITER;
		}
	}
}