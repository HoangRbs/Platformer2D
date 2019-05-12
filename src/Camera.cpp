#include"Camera.h"
#include"Game.h"

namespace HDT_engine
{
	namespace Game
	{
		Camera* Camera::instance = NULL;

		Camera::Camera()
		{
			JuicyPointPos = Math::Vector2D(game::Instance()->Get_GameWidth() / 2 + JUICY_RANGE,
										   game::Instance()->Get_GameHeight() / 2 + JUICY_RANGE);   

			JuicyPointVel = Math::Vector2D(0,0);

			CameraVel = Math::Vector2D(0,0);

			CameraPos = Math::Vector2D(0,0);

			OptimizeLagCamPos_x = 0;
			OptimizeLagCamPos_y = 0;
		}

		Camera* Camera::Instance()
		{
			if (instance == NULL)
			{
				instance = new Camera();
			}

			return instance;
		}

		Math::Vector2D& Camera::getCamPos()       ///is used in update() below
		{
			if (TargetPos != NULL)
			{
				CameraPos = Math::Vector2D(TargetPos->get_x() - JuicyPointPos.get_x(), TargetPos->get_y() - JuicyPointPos.get_y());
			}
			else
			{
				CameraPos.set_x(0);
				CameraPos.set_y(0);
			}

			return CameraPos;
		}

		Math::Vector2D& Camera::getCamVel()       ///is used in update() below
		{
			return CameraVel;
		}

		void Camera::Update()
		{
			
			if (TargetVel != NULL)
			{
				if (TargetVel->get_x() == 0)     //HORIZONTAL JUICY CAMERA ALGORITHM
				{
					JuicyPointVel.set_x((JuicyPointPos.get_x() - game::Instance()->Get_GameWidth() / 2) / JUICY_SPEED); ///Vel decreasing when standing still
					JuicyPointPos.set_x(JuicyPointPos.get_x() - JuicyPointVel.get_x());     ///after Vel change --> Pos change

					///for scrolling background purpose
					CameraVel.set_x(JuicyPointVel.get_x());
				}
				else if (TargetVel->get_x() > 0)
				{
					if (JuicyPointPos.get_x() < (game::Instance()->Get_GameWidth() / 2 + JUICY_RANGE)) //if player is standing in the middle of the screen
																									   //or maybe a little
																									   //but not in the beginning of the map
																									   //wanna know why? try disable this code
					{
						JuicyPointPos.set_x(JuicyPointPos.get_x() + TargetVel->get_x());

						///for scrolling background purpose
						CameraVel.set_x(0);
					}
					else // >= 0  --> now the Target goes to the JuicyRange point(+)
					{
						JuicyPointPos.set_x(game::Instance()->Get_GameWidth() / 2 + JUICY_RANGE);

						///for scrolling background purpose
						CameraVel.set_x(TargetVel->get_x());
					}
				}
				else  //Target Vel_x < 0
				{
					if (JuicyPointPos.get_x() > (game::Instance()->Get_GameWidth() / 2 - JUICY_RANGE)) //if player is standing in the middle of the screen
																									   //or maybe a little
																									   //but not in the beginning of the map
																									   //wanna know why? try disable this code
					{
						JuicyPointPos.set_x(JuicyPointPos.get_x() + TargetVel->get_x());
						
						///for scrolling background purpose
						CameraVel.set_x(0);
					}
					else // <= 0 --> now the Target goes to the JuicyRange point(-)
					{
						JuicyPointPos.set_x(game::Instance()->Get_GameWidth() / 2 - JUICY_RANGE);

						///for scrolling background purpose
						CameraVel.set_x(TargetVel->get_x());
					}
				}

				if (TargetVel->get_y() == 0)     //VERTICAL JUICY CAMERA ALGORITHM
				{
					JuicyPointVel.set_y((JuicyPointPos.get_y() - game::Instance()->Get_GameHeight() / 2) / JUICY_SPEED);
					JuicyPointPos.set_y(JuicyPointPos.get_y() - JuicyPointVel.get_y());      //remember this use both x and y
				}
				else if (TargetVel->get_y() > 0)
				{
					if (JuicyPointPos.get_y() < (game::Instance()->Get_GameHeight() / 2 + JUICY_RANGE)) //if player is standing in the middle of the screen
																									   //or maybe a little
																									   //but not in the beginning of the map
																									   //wanna know why? try disable this code
					{
						JuicyPointPos.set_y(JuicyPointPos.get_y() + TargetVel->get_y());
					}
					else // >= 0
					{
						JuicyPointPos.set_y(game::Instance()->Get_GameHeight() / 2 + JUICY_RANGE);
					}
				}
				else  //Target Vel_y < 0
				{
					if (JuicyPointPos.get_y() > (game::Instance()->Get_GameHeight() / 2 - JUICY_RANGE)) //if player is standing in the middle of the screen
																									    //or maybe a little
																									    //but not in the beginning of the map
																									    //wanna know why? try disable this code
					{
						JuicyPointPos.set_y(JuicyPointPos.get_y() + TargetVel->get_y());
					}
					else // <= 0
					{
						JuicyPointPos.set_y(game::Instance()->Get_GameHeight() / 2 - JUICY_RANGE);
					}
				}
			}

			/* THIS IS USELESS RIGHT NOW --> THERE IS STILL MEMORY LEAK
			else
			{
				//cout << "error no Camera Target" << endl;
				CameraPos.set_x(0);
				CameraPos.set_y(0);
			}
			*/

			OptimizeLagCamPos_x = getCamPos().get_x();
			OptimizeLagCamPos_y = getCamPos().get_y();
		}

		void Camera::Set_ThePlayer(GameObject* ThePlayer_)
		{
			ThePlayer = ThePlayer_;
		}

		GameObject* Camera::Get_ThePlayer()
		{
			return ThePlayer;
		}
	}
}