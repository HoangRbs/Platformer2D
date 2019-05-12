#include"FarAttackEnemy.h"
#include"../ShowFuckingEffect.h"

namespace HDT_engine
{
	namespace Game
	{
		FarAttackEnemy::FarAttackEnemy()
		{

		}

		FarAttackEnemy::~FarAttackEnemy()
		{

		}

		void FarAttackEnemy::update()
		{
			if (!is_dead)
			{
				if (!EnterScreen)
				{

					if (m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x() <= game::Instance()->Get_GameWidth() + 320
						&& m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x() > -320
						&& m_position.get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y() > -320 &&
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
						handleAnimation();        ///thought to put it outside to handle dying animation but the draw() function already did it
					}

					Enemy::update();              //standard update
				}

			}
		}

		void FarAttackEnemy::draw()
		{
			Enemy::draw();
		}

		void FarAttackEnemy::load(unique_ptr<LoadParams>const& inputParams)
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

			m_BulletReloadTime = 60;
			m_BulletReloadTimeCounter = 0;
		}

		void FarAttackEnemy::clean()
		{
			Enemy::clean();
		}

		void FarAttackEnemy::handleMovement()
		{
			if (!is_dying)
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
				attack();
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

				checkPlayerAttack();
			}
		}

		void FarAttackEnemy::attack()
		{
			attacking = false;

			if (LeftDetect || RightDetect)
			{
				m_velocity.set_x(0);
				handleFireBullet();
				attacking = true;
			}

		}

		void FarAttackEnemy::handleFireBullet()
		{
			if (m_BulletReloadTimeCounter == m_BulletReloadTime)
			{
				if (LeftDetect)
				{
					if (m_textureID == "PINKRANGER")
					{
						BulletHandler::Instance()->AddEnemyBullet(m_position.get_x(), m_position.get_y() + 10, 10, 10,
							"BULLET2", 32, 32, 1, 800,
							Math::Vector2D(-5, 0), Math::Vector2D(0, 0));
					}
					
					if (m_textureID == "AGENT")
					{
						BulletHandler::Instance()->AddEnemyBullet(m_position.get_x(), m_position.get_y() + 10, 10, 10,
							"BULLET1", 32, 32, 1, 800,
							Math::Vector2D(-5, 0), Math::Vector2D(0, 0));
					}

					SOUND::SoundManager::Instance()->PlaySoundEffect("FARENEMYATTACKSOUND",0);
				}
				else if (RightDetect)
				{
					if (m_textureID == "PINKRANGER")
					{
						BulletHandler::Instance()->AddEnemyBullet(m_position.get_x(), m_position.get_y() + 10, 10, 10,
							"BULLET2", 32, 32, 1, 800,
							Math::Vector2D(5, 0), Math::Vector2D(0, 0));
					}

					if (m_textureID == "AGENT")
					{
						BulletHandler::Instance()->AddEnemyBullet(m_position.get_x(), m_position.get_y() + 10, 10, 10,
							"BULLET1", 32, 32, 1, 800,
							Math::Vector2D(5, 0), Math::Vector2D(0, 0));
					}

					SOUND::SoundManager::Instance()->PlaySoundEffect("FARENEMYATTACKSOUND",0);
				}

				m_BulletReloadTimeCounter = 0;
			}

			m_BulletReloadTimeCounter++;
		}

		void FarAttackEnemy::handleAnimation()
		{
			if (!is_dying)
			{
				if (m_textureID == "PINKRANGER")          ///right now we'll just gonna do this --> for the sake of time 
				{
					if (m_velocity.get_x() != 0)
					{
						m_currentRow = 0;
						m_numFrames = 6;
					}
					else
					{

						m_currentRow = 1;
						m_numFrames = 6;
					}

					if (hurt == true)
					{
						m_currentRow = 2;
						m_numFrames = 1;

						if (hurtTimeCounter == 15)
						{
							SOUND::SoundManager::Instance()->PlaySoundEffect("ENEMYFUCKEDSOUND",0);
						}
					}

				}

				if (m_textureID == "AGENT")
				{
					if (m_velocity.get_x() != 0)
					{
						m_currentRow = 0;
						m_numFrames = 6;
					}
					else
					{
						m_currentRow = 1;
						m_numFrames = 4;
					}

					if (hurt == true)
					{
						m_currentRow = 2;
						m_numFrames = 1;

						if (hurtTimeCounter == 15)
						{
							SOUND::SoundManager::Instance()->PlaySoundEffect("ENEMYFUCKEDSOUND", 0);
						}
					}
				}
			}
		}

		void FarAttackEnemy::checkPlayerAttack()
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
							hurt = true;

							collision();

							Game::StartFuckingEffect("FUCKINGEFFECT");

							SOUND::SoundManager::Instance()->PlaySoundEffect("EXPLOSION",0);
						}
					}
				}
			}
		}

		void FarAttackEnemy::Hurt()
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
