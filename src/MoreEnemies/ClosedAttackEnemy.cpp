#include"ClosedAttackEnemy.h"
#include"../Player.h"
#include"../ShowFuckingEffect.h"

namespace HDT_engine
{
	namespace Game
	{
		ClosedAttackEnemy::ClosedAttackEnemy()
		{

		}

		ClosedAttackEnemy::~ClosedAttackEnemy()
		{

		}

		void ClosedAttackEnemy::update()
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
						handleAnimation();
					}

					Enemy::update();                //standard update
				}

			}
		}

		void ClosedAttackEnemy::draw()
		{
			Enemy::draw();
		}

		void ClosedAttackEnemy::load(unique_ptr<LoadParams>const& inputParams)
		{
			Enemy::load(inputParams);

			m_Health = 2;

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

		void ClosedAttackEnemy::clean()
		{
			Enemy::clean();
		}

		void ClosedAttackEnemy::handleMovement()
		{
			if (!is_dying)
			{
				if (!LeftDetect && !RightDetect)         ///the enemy stands still and change direction
				{
					if (changeDirectionTimeCounter == changeDirectionTime)
					{
						if (goingLeft)
						{
							goingLeft = false;
							goingRight = true;
							m_b_Flipped = false;
						}
						else if (goingRight)
						{
							goingRight = false;
							goingLeft = true;
							m_b_Flipped = true;
						}

						changeDirectionTimeCounter = 0;
					}
					changeDirectionTimeCounter++;
				}

				Enemy::Detect_Player();   ///check detect the player
				attack();                 ///increase Vel --> and more complicated stuff
				Hurt();

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
						m_b_Flipped = false;  //THIS IS HOW WE SEE THE TEXTURE --> this should be in handleAnimation

						m_velocity.set_x(1);   ///to avoid the Enemy stick into the Tile

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


				checkPlayerAttack();
			}
		}

		void ClosedAttackEnemy::attack()
		{
			if (!is_dying)
			{
				if (LeftDetect)
				{
					m_velocity.set_x(-2);

					///move amazingly fast to kill the player
					if (m_position.get_x() - ThePlayer->Get_Position().get_x() <= 50)
					{
						attacking = true;
						m_velocity.set_x(-3);
					}
				}
				else if (RightDetect)
				{
					m_velocity.set_x(2);

					///move amazingly fast to kill the player
					if (ThePlayer->Get_Position().get_x() - m_position.get_x() <= 50)
					{
						attacking = true;
						m_velocity.set_x(3);
					}
				}
				else      ///standing still
				{
					m_velocity.set_x(0);

					if (attacking == true)
					{
						if (attackingTimeCounter == attackingTime)
						{
							attacking = false;
							attackingTimeCounter = 0;
						}
						attackingTimeCounter++;
					}

				}
			}
		}

		void ClosedAttackEnemy::handleAnimation()
		{
			if (!is_dying)
			{
				if (m_textureID == "NARUTO")
				{
					if (m_velocity.get_x() != 0)
					{
						m_currentRow = 1;
						m_numFrames = 6;
					}
					else /// == 0
					{
						m_currentRow = 0;
						m_numFrames = 4;
					}

					if (attacking)
					{
						m_numFrames = 7;
						m_currentRow = 2;

						if (m_currentColumn == 3)
						{
							SOUND::SoundManager::Instance()->PlaySoundEffect("CLOSEDENEMYATTACKSOUND",0);
						}
					}

					if (hurt)
					{
						m_currentRow = 3;
						m_numFrames = 1;

						if (hurtTimeCounter == 15)
						{
							SOUND::SoundManager::Instance()->PlaySoundEffect("ENEMYFUCKEDSOUND", 0);
						}
					}
				}

				if (m_textureID == "SASUKE")
				{
					if (m_velocity.get_x() != 0)
					{
						m_currentRow = 1;
						m_numFrames = 6;
					}
					else
					{
						m_currentRow = 0;
						m_numFrames = 6;
					}

					if (attacking)
					{
						m_numFrames = 6;
						m_currentRow = 2;

						if (m_currentColumn == 3)
						{
							SOUND::SoundManager::Instance()->PlaySoundEffect("CLOSEDENEMYATTACKSOUND", 0);
						}
					}

					if (hurt)
					{
						m_currentRow = 3;
						m_numFrames = 1;

						if (hurtTimeCounter == 15)
						{
							SOUND::SoundManager::Instance()->PlaySoundEffect("ENEMYFUCKEDSOUND", 0);
						}
					}
				}

				if (m_textureID == "SOLDIER")
				{
					if (m_velocity.get_x() != 0)
					{
						m_currentRow = 1;
						m_numFrames = 12;
					}
					else
					{
						m_currentRow = 0;
						m_numFrames = 6;
					}

					if (attacking)
					{
						m_numFrames = 4;
						m_currentRow = 2;

						if (m_currentColumn == 2)
						{
							SOUND::SoundManager::Instance()->PlaySoundEffect("CLOSEDENEMYATTACKSOUND", 0);
						}
					}

					if (hurt)
					{
						m_currentRow = 3;
						m_numFrames = 1;

						if (hurtTimeCounter == 15)
						{
							SOUND::SoundManager::Instance()->PlaySoundEffect("ENEMYFUCKEDSOUND", 0);
						}
					}
				}

				if (m_textureID == "SPIDERMAN")
				{
					if (m_velocity.get_x() != 0)
					{
						m_currentRow = 1;
						m_numFrames = 8;
					}
					else    /// == 0 (indie)
					{
						m_currentRow = 0;
						m_numFrames = 3;
					}

					if (attacking)
					{
						m_numFrames = 10;
						m_currentRow = 2;

						if (m_currentColumn == 3)
						{
							SOUND::SoundManager::Instance()->PlaySoundEffect("CLOSEDENEMYATTACKSOUND", 0);
						}
					}

					if (hurt)
					{
						m_currentRow = 3;
						m_numFrames = 1;

						if (hurtTimeCounter == 15)
						{
							SOUND::SoundManager::Instance()->PlaySoundEffect("ENEMYFUCKEDSOUND", 0);
						}
					}
				}
			}
		}

		void ClosedAttackEnemy::checkPlayerAttack()
		{
			
			if (!(LeftDetect || RightDetect))
			{
				if (!(ThePlayer->Get_Position().get_x() + ThePlayer->Get_ScreenWidth() < m_position.get_x() ||
					  ThePlayer->Get_Position().get_x() > m_position.get_x() + m_screenWidth ||
					  ThePlayer->Get_Position().get_y() + ThePlayer->Get_ScreenHeight() < m_position.get_y() ||
					  ThePlayer->Get_Position().get_y() > m_position.get_y() + m_screenHeight))
				{
					if (dynamic_cast<Player*>(ThePlayer)->is_attacking())
					{
						if (dynamic_cast<Player*>(ThePlayer)->is_canKillEnemyWhileAttacking())
						{
							collision();

							hurt = true;

							Game::StartFuckingEffect("FUCKINGEFFECT");
						}
					}
				}
			}
		}

		void ClosedAttackEnemy::Hurt()
		{
			if (hurt == true)
			{
				if (hurtTimeCounter == hurtTime)
				{
					hurt = false;
					hurtTimeCounter = 0;
				}
				hurtTimeCounter++;
			}
		}
	}
}
