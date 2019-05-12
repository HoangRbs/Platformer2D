#include"CantBeHurtEnemy.h"

namespace HDT_engine
{
	namespace Game
	{
		CantBeHurtEnemy::CantBeHurtEnemy()
		{

		}

		CantBeHurtEnemy::~CantBeHurtEnemy()
		{

		}

		void CantBeHurtEnemy::update()
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

		void CantBeHurtEnemy::draw()
		{
			Enemy::draw();
		}

		void CantBeHurtEnemy::load(unique_ptr<LoadParams>const& inputParams)
		{
			Enemy::load(inputParams);

			m_Health = 1;

			m_acceleration.set_x(0);
			m_acceleration.set_y(1);      //gravity

			//AS IN REALITY (CAN BE SEEN)
			m_velocity.set_x(-1);		  //horizontal
			goingLeft = true;
			goingRight = false;
			m_b_Flipped = true;

			DEFAULT_GRAVITY = 3;
			DEFAUT_MAXVELOCITYLIMITER = 0;   ///we should not use this for other type of object
		}

		void CantBeHurtEnemy::clean()
		{
			Enemy::clean();
		}


		void CantBeHurtEnemy::handleMovement()
		{
			
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

					goingLeft = false;
					goingRight = true;
					m_b_Flipped = false;  //THIS IS HOW WE SEE THE TEXTURE
					m_velocity.set_x(1);

				}
				else if (goingRight)
				{


					goingRight = false;
					goingLeft = true;
					m_b_Flipped = true;
					m_velocity.set_x(-1);

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

		void CantBeHurtEnemy::attack()
		{
			//nothing in here --> they just move and no detect + can't be hurt
		}
	}
}
