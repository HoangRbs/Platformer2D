#include"Player.h"
#include"game.h"			//void circular include() :D :D //gotta say this is gold
#include"BulletHandler.h"
#include"Camera.h"
#include"PlayerControlScrollingBackground.h"

namespace HDT_engine
{
	namespace Game
	{

		Player::Player():PlatformerObject()
		{
			m_DyingTime = 100;
			m_DyingTimeCounter = 0;

			m_ProtectShield = false;
			m_ProtectShieldTimeCounter = 0;
			m_ProtectShieldTime = 200;

			m_BulletReloadTime = 20;
			m_BulletReloadTimeCounter = 0;

			EnterScreen = true;
		}

		Player::~Player()
		{

		}

		void Player::draw()
		{
			//Player has no special drawing effect here
			PlatformerObject::draw();
		}

		void Player::update()
		{
			//Math::Vector2D* mouse_vec = INPUT::InputHandler::Instance()->get_mouse_pos();  --> this will be in HandleInput
			//m_velocity = (*mouse_vec - m_position)/50;      --> this is a COOL function to PlayWith
			
			if (game::Instance()->Get_PlayerLives() == 0)
			{
				is_dead = true;                      
				int temp = PLAYERLIVESMAX;
				game::Instance()->Set_PlayerLives(temp); 

				//if not reset the Player lives-->or the new playstate will keep thinking the player is death
			}
			
			if (!is_dead)
			{
				///the standingOnPlatform controls the ScrollingBackground
				PlayerControlScrollingBackground::Instance()->set_PlayerStandingOnPlatform(StandingOnPlatform);

				if (Game::game::Instance()->Get_Level_Complete())         // the current Level completes if current bosslives == 0
				{
					/*
					if (m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x() > game::Instance()->Get_GameWidth())
					{
						game::Instance()->GoHigherLevel();				 
					}
					else                                                  //make the heli automatically go out 
					{
						m_velocity.set_x(3);
						m_velocity.set_y(0);

						PlatformerObject::update();                         //and then Update normally(Standard Update)

						HandleAnimation();									//now add a little bit more helicopter feel
					}
					*/

					game::Instance()->GoHigherLevel();
				}
				else                                                        // the current level does not complete
				{
					if (!is_dying)                                          //if the Player is not dying --> it is living
					{
							m_acceleration.set_y(DEFAULT_GRAVITY);				//there's always be gravity
																				//it is set to 0 again in movementHandler()

							HandleInput();										//now we'll control the Heli to do what ever we want
																				//it changes our velocity
																				//then Update() --> the position under this function

							HandleAnimation();									//now lets add a bit helicopter feel while it's moving
																				//and a bit shield enable

							HandleMovement();									//checking Tile Collision
																				//this function has to be operated before Update
																				//since this function decide our position OR velocity
																				//and the update below will update the postition from our
																				//velocity
																				//so the HandleMovement should only take care of velocity
							
							///HandleMovement is a function to check or calcualte for the next Frame --> so it should be placed after
							///Handle Animation --> which takes care of the current Frame Animation as in out scenario
							

							PlatformerObject::update();							//after handle input --> it controls the basic vel or acceleration 
																				//-->makes the position change(Update) right in standard Update
					}
					else														//now it is Dying cmnr (is_Dying == TRUE) right now
					{
						m_currentColumn = (SDL_GetTicks() / (1000 / 6)) % m_DyingNumFrames;	//first --> the draw function after this Update function..
																						//..will draw the HeliDying texture(exploding)..
																						//..and the Frames change speed will be a little different


						if (m_DyingTimeCounter == m_DyingTime)							//and it Dying for a bit amount of time Till it really Dead
						{
							m_DyingTimeCounter = 0;			//is_dead = true; --> we not use this here --> is_dead == true when the PlayerLives == 0 in the game system
							BringBackToLife();				//at that time --> the Player is already pushed out
															//and the game state change

															//for now, after Dying --> we'll gonna keep reviving the Player in update() function
						}

						m_DyingTimeCounter++;				//and when the Heli is dying (exploding) --> there will be no standard movement
															//so there will be no ShooterObject::Update() to make the heli move at the moment
					}

				}
			}
		}

		void Player::clean()
		{
			PlatformerObject::clean();
		}

		void Player::load(unique_ptr<LoadParams>const& inputParams)
		{
			PlatformerObject::load(inputParams);

			m_velocity.set_x(0);
			m_velocity.set_y(0);

			goingLeft = false;
			goingRight = false;
			m_b_Flipped = false;
			
			DEFAUT_MAXVELOCITYLIMITER = 0.005f;
			DEFAULT_GRAVITY = 3;

			m_MaxVelocityLimiter = DEFAUT_MAXVELOCITYLIMITER;

			Camera::Instance()->setTargetInfo(&m_position,&m_velocity);
			Camera::Instance()->Set_ThePlayer(this);
			//PlayerControlScrollingBackground::Instance()->Set_ThePlayer(this);

			m_CheckPointPos.set_x(100);
			m_CheckPointPos.set_y(400);

			//random Dying sounds
			PlayerDyingSounds.push_back("PLAYERDYINGSOUND1");
			PlayerDyingSounds.push_back("PLAYERDYINGSOUND2");
		}

		std::string Player::Get_objectType()
		{
			return ("Player");                    //to register the PLAYER CREATOR, similar to the type in PARSESTATE.xml file
		}

		void Player::BringBackToLife()
		{
			m_position = m_CheckPointPos;

			m_ProtectShield = true;				   //Protect Shield enable

			//after Rivival --> minus one PlayerLives in the game system
			game::Instance()->Set_PlayerLives(game::Instance()->Get_PlayerLives() - 1);    

			// since Player texture and the Dying one must have different image info --> so we'll just gonna reset some shit
			m_currentColumn = 0;
			m_currentRow = 0;
		
			//now set dying to false so Player can go to the right section in Update
			is_dying = false;

			m_velocity.set_x(0);
			m_acceleration.set_x(0);

			PlayerControlScrollingBackground::Instance()->set_PlayerBackToLife(true);
		}

		void Player::HandleAnimation()
		{
		
			if (m_ProtectShield == true)								   //the shield is protecting --> this only happens when it is alive
			{
				if (m_ProtectShieldTimeCounter == m_ProtectShieldTime)     //done protecting animation
				{
					m_ProtectShield = false;
					m_alpha = 255;						//visible again
					m_ProtectShieldTimeCounter = 0;     //it does not protect anymore
				}
				else													   //still protecting animation
				{
					if (m_alpha == 255)                                    //Flashing the Heli 
					{
						if (m_ProtectShieldTimeCounter % 5 == 0)           //control the speed of alpha
						{
							m_alpha = 0;
						}
					}
					else if(m_alpha == 0)
					{
						if (m_ProtectShieldTimeCounter % 5 == 0)
						{
							m_alpha = 255;
						}
					}

					m_ProtectShieldTimeCounter++;
				}
			}

			if ((!is_dead)&&(!is_dying))							
			{
				if (m_velocity.get_y() < 0)     //jumping
				{
					m_numFrames = 1;
					m_currentRow = 2; 
					m_FrameWidth = 35;
					
					if (m_velocity.get_x() < 0)
					{
						m_b_Flipped = true;
					}
					else if (m_velocity.get_x() > 0)
					{
						m_b_Flipped = false;
					}
					// == 0 --> do nothing 
				}
				else if (m_velocity.get_y() > 0)   //falling
				{
					m_numFrames = 1;
					m_currentRow = 3;
					m_FrameWidth = 32;

					if (m_velocity.get_x() < 0)
					{
						m_b_Flipped = true;
					}
					else if(m_velocity.get_x() > 0)
					{
						m_b_Flipped = false;
					}
					// == 0 --> do nothing 
				}
				else    //vel_y == 0 --> on the ground //if this was not called --> that's means vel_y always > 0 or < 0
				{
					if (m_velocity.get_x() > 0)		        ///RUNNING			
					{
						//m_angle = 10;
						m_numFrames = 6;
						m_currentRow = 1;
						m_FrameWidth = 40;
						m_b_Flipped = false;   //REALITY

						//REALITY
						if(m_currentColumn == 0 || m_currentColumn == 4)
							SOUND::SoundManager::Instance()->PlaySoundEffect("PLAYERFOOTSTEPSOUND",0);
					} 
					else if (m_velocity.get_x() < 0)          ///RUNNING
					{
						//m_angle = -10;
						m_numFrames = 6;
						m_currentRow = 1;
						m_FrameWidth = 40;
						m_b_Flipped = true;  //REALITY

						if (m_currentColumn == 0 || m_currentColumn == 4)
							SOUND::SoundManager::Instance()->PlaySoundEffect("PLAYERFOOTSTEPSOUND", 0);
					}
					else if (m_velocity.get_x() == 0)          ///INDIE
					{
						//m_angle = 0;
						m_FrameWidth = 35;
						m_numFrames = 10;
						m_currentRow = 0;
					}
				}

				if (StandingOnPlatform != NULL)
				{
					if (m_velocity.get_x() > 0)		        ///RUNNING			
					{
						//m_angle = 10;
						m_numFrames = 6;
						m_currentRow = 1;
						m_FrameWidth = 40;
						m_b_Flipped = false;   //REALITY
					}
					else if (m_velocity.get_x() < 0)          ///RUNNING
					{
						//m_angle = -10;
						m_numFrames = 6;
						m_currentRow = 1;
						m_FrameWidth = 40;
						m_b_Flipped = true;  //REALITY
					}
					else if (m_velocity.get_x() == 0)          ///INDIE
					{
						//m_angle = 0;
						m_FrameWidth = 35;
						m_numFrames = 10;
						m_currentRow = 0;
					}
				}

				if (attacking == true)
				{
					m_numFrames = 1;
					m_FrameWidth = 32;
					m_currentRow = 4;
				}
			}
		}

		void Player::HandleInput()
		{
			if (!is_dead)
			{
				if (INPUT::InputHandler::Instance()->is_thiskey_pressed(SDL_SCANCODE_LEFT) /*&& m_position.get_x() > 0*/ )
				{
						m_acceleration.set_x(-3);
				}
				else
				{
					if (INPUT::InputHandler::Instance()->is_LeftKey_Released())
					{
						m_acceleration.set_x(0);
					}
				}

				if (INPUT::InputHandler::Instance()->is_thiskey_pressed(SDL_SCANCODE_RIGHT) /*&& 
					m_position.get_x() < game::Instance()->Get_GameWidth()*/)					//we using camera so have to diasble this
																								//want to know how it works --> enable it
				{
						m_acceleration.set_x(3);
				}
				else
				{
					if (INPUT::InputHandler::Instance()->is_RightKey_Released())
					{
						m_acceleration.set_x(0);
						
					}
				}

				if (INPUT::InputHandler::Instance()->is_thiskey_notpressed(SDL_SCANCODE_RIGHT) && 
					INPUT::InputHandler::Instance()->is_thiskey_notpressed(SDL_SCANCODE_LEFT))
				{
					if(StandingOnPlatform != NULL)
					{
						m_acceleration.set_x(0);
						m_velocity.set_x(0);

						if (m_velocity.get_x() < StandingOnPlatform->Get_velocity().get_x() + 0.811f && m_velocity.get_x() > StandingOnPlatform->Get_velocity().get_x() -0.811f)
						{

							m_velocity.set_x(0);

						}
					}
					else if (m_velocity.get_x() < 0.811f && m_velocity.get_x() > -0.811f)
					{
						
						m_velocity.set_x(0);
						
					}
				}

				if (INPUT::InputHandler::Instance()->is_thiskey_pressed(SDL_SCANCODE_UP) /*&& m_position.get_y() > 0*/)
				{
					if (StandingOnPlatform != NULL)
					{
						canStartJump = true;
						Jumping = false;
						
						StandingOnPlatform = NULL;
					}

					if(canStartJump)
					{
						Jumping = true;
						canStartJump = false;  
						m_velocity.set_y(-2);

						SOUND::SoundManager::Instance()->PlaySoundEffect("PLAYERJUMPSOUND",0);
					}

					if (InsidePlatform != NULL)
					{
						m_acceleration.set_y(0);
						m_velocity.set_y(-1);
					}
				}

				/*
				if (INPUT::InputHandler::Instance()->is_thiskey_pressed(SDL_SCANCODE_DOWN) &&
					m_position.get_y() < game::Instance()->Get_GameHeight())
				{
					if (InsidePlatform != NULL)
					{
						///do nothing
					}
					else
					{
						m_velocity.set_y(2);
					}
				}
				*/

				if (INPUT::InputHandler::Instance()->is_thiskey_pressed(SDL_SCANCODE_SPACE))         
				{		
					attack();
				}
			}
		}

		bool Player::ProtectShieldEnable()
		{
			return m_ProtectShield;
		}


		void Player::HandleMovement()
		{
			if (attacking)
			{
				m_velocity.set_x(0);

				if (attackingTimeCounter == attackingTime)
				{
					attacking = false;
					is_DelayNextAttack = true;
					attackingTimeCounter = 0;
				}
				attackingTimeCounter++;

				CanKillEnemyWhileAttacking = false;

				if (attackingTimeCounter == 25)          
				{
					CanKillEnemyWhileAttacking = true;
				}
			}

			if (is_DelayNextAttack)
			{
				if (DelayNextAttackTimeCounter == DelayNextAttackTime)
				{
					is_DelayNextAttack = false;
					CanStartAttack = true;
					DelayNextAttackTimeCounter = 0;
				}
				DelayNextAttackTimeCounter++;
			}

			Math::Vector2D newPos = m_position;
			Math::Vector2D newVel = m_velocity;
			
			newVel.set_x(newVel .get_x() - newVel.get_x() * m_MaxVelocityLimiter + (m_acceleration.get_x()) * deltaTime);
			newPos.set_x(m_position.get_x() + newVel.get_x());


			if (!checkCollideTile(newPos))        //checking horizontally
			{
				//do nothing
				//the velocity is now currently holding some values due to our HandleInput()
				//just don't change it
				//the ShooterObject::update() will take care of changing position from our velocity
				
				m_MaxVelocityLimiter = DEFAUT_MAXVELOCITYLIMITER;        ///for friction on the wall --> and reset to default after changing
																		 ///in the below code
			}
			else                ///COLIDE HORIZONTALLY cmnr
			{
				int savePreviousAcc = m_acceleration.get_x();
				int savePreviousVel = m_velocity.get_x();

				m_velocity.set_x(0);      //do no move horizontally anymore --> then ShooterObject::Update
				m_acceleration.set_x(0);

				///special skill --> can multiple jump when on the wall--> disable this to understand

				canStartJump = true;
				Jumping = false;

				if (m_velocity.get_y() < 0 && INPUT::InputHandler::Instance()->is_thiskey_pressed(SDL_SCANCODE_UP))  ///when vertical jumping and colliding horizontally
				{
				
					if (savePreviousAcc < 0)
					{
						m_velocity.set_x(1);
						m_acceleration.set_x(2);
					}
					else if (savePreviousAcc > 0)
					{
						m_velocity.set_x(-1);
						m_acceleration.set_x(-2);
					}
				}
				else   /// > or < or == .... slide down slowly on the wall
				{
					if (m_velocity.get_y() >= 0 || m_velocity.get_y() < 0)
					{
						m_MaxVelocityLimiter = 0.1f;
					}
				}
			}

			newPos = m_position;   //reset
			newVel = m_velocity;

			newVel.set_y(newVel.get_y() - newVel.get_y() * m_MaxVelocityLimiter + (m_acceleration.get_y()) * deltaTime);
			newPos.set_y(m_position.get_y() + newVel.get_y());

			if (!checkCollideTile(newPos))               //checking vertically
			{
				//the velocity is now currently holding some values due to our HandleInput()
				//just don't change it
				//the ShooterObject::update() will take care of changing position from our velocity
				

				///in this case --> the Player does not collide with the Tile below
				///for ex: standing on a tile and go forward until it fall -->and press JUMP to see the reaction
				
				//canStartJump = false;
				//Jumping = true;
			}
			else
			{
			
				///SPECIAL CASE --> THE PLAYER IS STILL MOVING UP
				///--> TO KNOW HOW IT WORKS --> JUST DISABLE THIS IF CODE AND COLLIDE WITH A TILE WHEN JUMPING AND STILL
				///HOLDING THE UP BUTTON

				if (m_velocity.get_y() < 0)          ///TOUCH THE TILE FROM ABOVE
				{
					m_velocity.set_y(0);
					m_acceleration.set_y(3);
				}
				else                                ///TOUCHING THE TILE ON THE GROUND
				{
					m_acceleration.set_y(0);		//TOUCHING THE GROUND
					m_velocity.set_y(0);			//do not move vertically anymore

													//remember to we're touching the ground at the first start --> so at the first start ,we try not to implement this
					if (Jumping)					//RIGHT NOW WE'RE TOUCHING THE GROUND
					{
						canStartJump = true;
						Jumping = false;
					}
				}
			}

			//checking with MovingPlatforms
			newPos = m_position;        //reset
			newVel = m_velocity;		//reset

			newVel = newVel - newVel * m_MaxVelocityLimiter + (m_acceleration) * deltaTime;       //the checking function below requires both x,y dimension
			newPos += newVel;

			checkCollideMovingPlatform(newPos);
			checkCollideCanBeInsidePlatform();             ///this one is easy
		}

		void Player::HandleFireBullet()
		{
			if (m_BulletReloadTimeCounter == m_BulletReloadTime)
			{
				BulletHandler::Instance()->AddPlayerBullet(m_position.get_x(),m_position.get_y() + 10,
														   20,30,"PLAYERBULLET",20,35,1,800,
														   Math::Vector2D(8,0), Math::Vector2D(0, 0));
				m_BulletReloadTimeCounter = 0;
			}

			m_BulletReloadTimeCounter++;
		}

		void Player::collision()
		{
			SOUND::SoundManager::Instance()->PlaySoundEffect(PlayerDyingSounds.at(rand() % 2),0);       //only 3 dying sounds total      
			m_currentRow = 0;
			m_currentColumn = 0;

			//now set dying to true --> so player can go to the right SECTION in Update()
			is_dying = true;
		}

		void Player::attack()
		{
			if (CanStartAttack)
			{
				SOUND::SoundManager::Instance()->PlaySoundEffect("PLAYERATTACKSOUND", 0);
				attacking = true;
				CanStartAttack = false;
			}
		}
	//.........
	}
}