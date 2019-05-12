#include"Snail.h"
#include"Camera.h"
#include"game.h"

namespace HDT_engine
{
	namespace Game
	{
		void Snail::draw()
		{
			Enemy::draw();
		}

		void  Snail::update()
		{
			if (!is_dead)
			{
				if (!EnterScreen)
				{

					if (m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x() <= game::Instance()->Get_GameWidth() + 320
						&& m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x() > - 320
						&& m_position.get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y() > - 320 &&
						m_position.get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y() <= game::Instance()->Get_GameHeight() + 320)
					{
						EnterScreen = true;
					}

				}
				else           //ENTER SCREEN CMNR
				{
					if (!is_dying)
					{
						m_acceleration.set_y(DEFAULT_GRAVITY);          //there's always be gravity
																		//it is set to 0 again in movementHandler()

						handleMovement();         //TileCollisionDetection
					}

					Enemy::update();              //standard update
				}

			}
		}

		void Snail::load(unique_ptr<LoadParams>const& inputParams)
		{
			Enemy::load(inputParams);
			m_Health = 5;

			m_velocity.set_x(-1);		  //horizontal

			m_acceleration.set_x(0);
			m_acceleration.set_y(1);      //gravity

			goingLeft = true;
			
			//AS IN REALITY (CAN BE SEEN)
			m_b_Flipped = true;
			goingRight = false;

			DEFAULT_GRAVITY = 3;
			DEFAUT_MAXVELOCITYLIMITER = 0;   ///we should not use this for other type of object
		}

		void Snail::clean()
		{
			Enemy::clean();
		}

		void Snail::handleMovement()
		{
			if (goingLeft)         ///try disable this code to know what happens
			{
				m_velocity.set_x(-1);
			}
			else if (goingRight)
			{
				m_velocity.set_x(1);
			}

			Enemy::Detect_Player();   ///check detect the player
			attack();                 ///increase Vel

			Math::Vector2D newPos = m_position;
			Math::Vector2D newVel = m_velocity;

			newVel.set_x((m_velocity.get_x() - m_velocity.get_x() * m_MaxVelocityLimiter) + m_acceleration.get_x() * deltaTime);
			newPos.set_x(m_position.get_x() + newVel.get_x());


			if (!checkCollideTile(newPos))        //checking horizontally
			{
				
			}
			else      //COLLIDE!!!
			{
		
				if (goingLeft)
				{
					if(LeftDetect)
					{
						m_velocity.set_x(0);
					}
					else        ///no detect
					{
						goingLeft = false;
						goingRight = true;
						m_b_Flipped = false;  //THIS IS HOW WE SEE THE TEXTURE
						m_velocity.set_x(1);
					}
				}
				else if(goingRight)
				{
				
					if(RightDetect)
					{
						m_velocity.set_x(0);
					}
					else
					{
						goingRight = false;
						goingLeft = true;
						m_b_Flipped = true;
						m_velocity.set_x(-1);
					}
				}
			}

			newPos = m_position;   //reset
			newVel = m_velocity;

			newVel.set_y((m_velocity.get_y() - m_velocity.get_y() * m_MaxVelocityLimiter) + m_acceleration.get_y() * deltaTime);
			newPos.set_y(m_position.get_y() + newVel.get_y());

			if (!checkCollideTile(newPos))               //checking vertically
			{
				//do nothing
				//the ShooterObject::update() will take care of changing position from our velocity
			}
			else      //COLLIDE!!!
			{
				m_velocity.set_y(0);      //do not move vertically anymore
				m_acceleration.set_y(0);
			}
		}

		void Snail::attack()
		{
			if (LeftDetect)          ///goinf left and going right is set by bool Flip of a texture
			{
				m_velocity.set_x(-3);
			}
			else if (RightDetect)
			{
				m_velocity.set_x(3);
			}
		}
	}
}