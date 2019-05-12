#include"ScrollingBackground.h"
#include"game.h"
#include"graphic/TextureManager.h"
#include"PlayerControlScrollingBackground.h"
#include"game.h"
#include"Camera.h"

namespace HDT_engine
{
	namespace Game
	{
		void ScrollingBackground::draw()
		{
			//if (Camera::Instance()->Get_ThePlayer() != NULL)
			//{
				for (int i = 0; i < BackgroundsRepeat.size(); i++)
				{
					Graphic::TextureManager::Instance()->drawFrame(m_textureID,
						BackgroundsRepeat.at(i).get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x(),
						BackgroundsRepeat.at(i).get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y(),
						m_FrameWidth, m_FrameHeight,
						m_screenWidth, m_screenHeight,
						m_currentColumn, m_currentRow,
						m_angle, m_alpha);
				}
			//}
		}

		void ScrollingBackground::update()
		{
			//if (Camera::Instance()->Get_ThePlayer() != NULL)
			//{
				if (PlayerControlScrollingBackground::Instance()->isPlayerBackToLife())
				{
					BackgroundsRepeat.at(LEFT).set_x(Camera::Instance()->Get_OptimizeLagCamPos_x() - 32);
					BackgroundsRepeat.at(RIGHT).set_x(BackgroundsRepeat.at(LEFT).get_x() + m_screenWidth + 1);

					PlayerControlScrollingBackground::Instance()->set_PlayerBackToLife(false);
				}

				m_velocity.set_x(Camera::Instance()->getCamVel().get_x() * 1.0f / m_scrollSpeed);        ///this is the scrollspeed

				if (PlayerControlScrollingBackground::Instance()->get_PlayerStandingOnPlatform() != NULL)
				{
					m_velocity.set_x((PlayerControlScrollingBackground::Instance()->
						get_PlayerStandingOnPlatform()->Get_velocity().get_x()
						+
						Camera::Instance()->getCamVel().get_x()) * 1.0f / m_scrollSpeed);
				}


				for (int i = 0; i < BackgroundsRepeat.size(); i++)
				{
					BackgroundsRepeat.at(i).set_y(Camera::Instance()->Get_OptimizeLagCamPos_y() - 32.0f);

					BackgroundsRepeat.at(i) += m_velocity;
				}

				///ALMOST OUT OF BACKGROUND VIEW
				if (Camera::Instance()->Get_OptimizeLagCamPos_x() + game::Instance()->Get_GameWidth() >= BackgroundsRepeat.at(RIGHT).get_x() + m_screenWidth - 15)
				{
					//switch value
					Math::Vector2D temp = BackgroundsRepeat.at(RIGHT);
					BackgroundsRepeat.at(RIGHT) = BackgroundsRepeat.at(LEFT);
					BackgroundsRepeat.at(LEFT) = temp;

					BackgroundsRepeat.at(RIGHT).set_x(BackgroundsRepeat.at(LEFT).get_x() + m_screenWidth + 1);
				}
				else if (Camera::Instance()->Get_OptimizeLagCamPos_x() <= BackgroundsRepeat.at(LEFT).get_x() + 15)
				{
					//switch value
					Math::Vector2D temp = BackgroundsRepeat.at(RIGHT);
					BackgroundsRepeat.at(RIGHT) = BackgroundsRepeat.at(LEFT);
					BackgroundsRepeat.at(LEFT) = temp;

					BackgroundsRepeat.at(LEFT).set_x(BackgroundsRepeat.at(RIGHT).get_x() - m_screenWidth - 1);
				}
			//}
		

		}

		void ScrollingBackground::clean()
		{
			PlatformerObject::clean();
		}

		void ScrollingBackground::load(unique_ptr<LoadParams>const &inputParams)
		{
			PlatformerObject::load(inputParams);

			m_velocity = Math::Vector2D(0,0);
			m_acceleration = Math::Vector2D(0,0);
			is_dying = false;

			///m_MaxVelocityLimiter = 0.006;     ///for scrolling background

			EnterScreen = true;

			/*  ---> is used below function													
			m_screenHeight = game::Instance()->Get_GameHeight() + 32 * 2;
			m_screenWidth = game::Instance()->Get_GameWidth() + 32 * 2;

			m_position.set_x(-32.0f + Camera::Instance()->Get_OptimizeLagCamPos_x());
			m_position.set_y(-32.0f + Camera::Instance()->Get_OptimizeLagCamPos_y());

			///testing
			///m_scrollSpeed = 1;

			Math::Vector2D LeftRectPos = m_position;
			Math::Vector2D RightRectPos = m_position;

			RightRectPos.set_x(LeftRectPos.get_x() + m_screenWidth + 1);

			BackgroundsRepeat.push_back(LeftRectPos);
			BackgroundsRepeat.push_back(RightRectPos);
			*/

			///avoid ERROR
			try
			{
				if (m_scrollSpeed == 0)
				{
					throw 0;
				}
			}
			catch (int ThrowdError)
			{
				cout<<"...................."<<endl;
				cout <<"m_scrollSpeed is "<<m_scrollSpeed<<"  --> m_scrollSpeed has to be > 0" << endl;
				cout<<"...................."<<endl;
			}
		}

		void ScrollingBackground::LeverParserLoad()
		{
			m_screenHeight = game::Instance()->Get_GameHeight() + 32 * 2;
			m_screenWidth = game::Instance()->Get_GameWidth() + 32 * 2;

			m_position.set_x(-32.0f + Camera::Instance()->Get_OptimizeLagCamPos_x());
			m_position.set_y(-32.0f + Camera::Instance()->Get_OptimizeLagCamPos_y());

			///testing
			///m_scrollSpeed = 1;

			Math::Vector2D LeftRectPos = m_position;
			Math::Vector2D RightRectPos = m_position;

			RightRectPos.set_x(LeftRectPos.get_x() + m_screenWidth + 1);

			BackgroundsRepeat.push_back(LeftRectPos);
			BackgroundsRepeat.push_back(RightRectPos);

		}

		GameObject* ScrollingBackgroundCreator::createGameObject()
		{
			return new ScrollingBackground();
		}

		void ScrollingBackground::Set_scrollSpeed(int input_)
		{
			
		}
	}
}