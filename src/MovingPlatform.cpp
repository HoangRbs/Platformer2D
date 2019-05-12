#include"MovingPlatform.h"
#include"Camera.h"
#include"game.h"
#include"Math.h"

namespace HDT_engine
{
	namespace Game
	{
		MovingPlatform::MovingPlatform():PlatformerObject()
		{
		
		}

		MovingPlatform::~MovingPlatform()
		{

		}

		void MovingPlatform::update()
		{

			if (!EnterScreen)
			{

				if (m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x() <= game::Instance()->Get_GameWidth() + 500
					&& m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x() > 0  - 500
					&& m_position.get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y() > 0  - 500 &&
					m_position.get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y() <= game::Instance()->Get_GameHeight() + 500)
				{
					EnterScreen = true;
				}

			}
			else           //ENTER SCREEN CMNR
			{
				if (m_position.get_x() + m_screenWidth - Camera::Instance()->Get_OptimizeLagCamPos_x() < 0  - 500 ||
					m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x() > game::Instance()->Get_GameWidth() + 500 ||
					m_position.get_y() + m_screenHeight - Camera::Instance()->Get_OptimizeLagCamPos_y() < 0 - 500 ||
					m_position.get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y() > game::Instance()->Get_GameHeight() + 500)

				{
					EnterScreen = false;        
				}

				
				if (m_acceleration.get_x() > 0)
				{
					if (m_position.get_x() - InitialPoint.get_x() >= Magnitude)
					{
						m_acceleration.set_x(-2);
					}
				}

				if (m_acceleration.get_x() < 0)
				{
					if (m_position.get_x() - InitialPoint.get_x() <= -Magnitude)
					{
						m_acceleration.set_x(2);
					}
				}
				

				/*
				if (m_acceleration.get_y() > 0)
				{
					if (m_position.get_y() - InitialPoint.get_y() >= Magnitude)
					{
						m_acceleration.set_y(-2);
					}
				}

				if (m_acceleration.get_y() < 0)
				{
					if (m_position.get_y() - InitialPoint.get_y() <= -Magnitude)
					{
						m_acceleration.set_y(2);
					}
				}
				*/

				//update like normal
				PlatformerObject::update();

				//cout << m_position.get_x() - InitialPoint.get_x() << endl;
			}
		
		}

		void MovingPlatform::draw()
		{
			PlatformerObject::draw();
		}

		void MovingPlatform::clean()
		{
			PlatformerObject::clean();
		}

		void MovingPlatform::load(unique_ptr<LoadParams>const &inputParams)
		{
			PlatformerObject::load(inputParams);

			
			m_acceleration.set_y(0);
			m_acceleration.set_x(2);
			

			/*
			m_acceleration.set_y(2);
			m_acceleration.set_x(0);
			*/

			m_MaxVelocityLimiter = 0.005;

			InitialPoint = m_position;
		}

		std::string MovingPlatform::Get_objectType()
		{
			return ("MovingPlatform");
		}
	}
}