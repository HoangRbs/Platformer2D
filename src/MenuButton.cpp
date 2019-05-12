#include"MenuButton.h"
#include"Camera.h"
#include"game.h"

namespace HDT_engine
{
	namespace Game
	{
		MenuButton::MenuButton(): PlatformerObject()
		{
			//inittialization

			m_currentColumn = MOUSE_OUT;       //always start at MOUSE_OUT first
		}

		void MenuButton::draw()
		{
			PlatformerObject::draw();

			//Graphic::TextureManager::Instance()->drawFrame(textureID,m_position.get_x(),m_position.get_y(),
			//											     400,100,screenWidth,screenHeight,m_currentColumn,m_currentRow);
		}

		void MenuButton::update()
		{
			if (m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x() <= game::Instance()->Get_GameWidth()
				&& m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x() > 0
				&& m_position.get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y() > 0 &&
				m_position.get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y() <= game::Instance()->Get_GameHeight())
			{
				EnterScreen = true;
			}
			else
			{
				EnterScreen = false;
			}

			Math::Vector2D* trackingMousePos = INPUT::InputHandler::Instance()->get_mouse_pos();


			//if(MOUSE is OVER the button)
			if (trackingMousePos->get_x() > m_position.get_x() &&
				trackingMousePos->get_x() < m_position.get_x() + this->m_screenWidth &&
				trackingMousePos->get_y() > m_position.get_y() &&
				trackingMousePos->get_y() < m_position.get_y() + this->m_screenHeight)
			{
				m_currentColumn = MOUSE_OVER;

				//if (MOUSE LEFT CLICK)
				if (is_LeftMouseReleasedPrev && INPUT::InputHandler::Instance()->is_thisMouseButton_pressed(INPUT::mouse_buttons::LEFT))
				{

					m_currentColumn = MOUSE_CLICKED;

					if (m_callBack == NULL)
					{
						//do nothing
					}
					else
					{
						SOUND::SoundManager::Instance()->PlaySoundEffect("CLICKBUTTONSOUND", 0);
						m_callBack();       //after clicking --> operate functionality.
					}
				}

			}
			else
			{

				m_currentColumn = MOUSE_OUT;       //if not MOUSE_OVER;
			}

			//ShooterObject::update();     //standard update --> we wont use this in MenuButton type
			//cuz the current Column is calculated above --> in this function it recal the m_currentColumn --> which is bad
			//that's why that Update is only used for Platformer Object

			if (INPUT::InputHandler::Instance()->is_thisMouseButton_pressed(INPUT::mouse_buttons::LEFT))
			{
				is_LeftMouseReleasedPrev = false;
			}
			else
			{
				is_LeftMouseReleasedPrev = true;
			}
		}

		void MenuButton::clean()
		{
			PlatformerObject::clean();
		}

		void MenuButton::load(unique_ptr<LoadParams> inputParams)
		{
			PlatformerObject::load(inputParams);   

			is_LeftMouseReleasedPrev = false;
		}

		void MenuButton::SetCallBack(void_function_pointer m_callBack_)
		{
			this->m_callBack = m_callBack_;
		}

		int MenuButton::getCallBackID()
		{
			return m_callBackID; 
		}
	}
}