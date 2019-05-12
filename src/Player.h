#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include"LoadParams.h"
#include"PlatformerObject.h"
#include"input/InputHandler.h"

namespace HDT_engine
{
	namespace Game                              //Player is singleton
	{
		
		class Player: public PlatformerObject      //inherit sdl game object
		{
			typedef void(*void_function_pointer)();

		public:
			Player();
			~Player();

			void draw();                       //Standard Update()
			void update();	                   //contains all the info of the Player				   
			void clean();
			void load(unique_ptr<LoadParams>const& inputParams);

			std::string Get_objectType();

			virtual void collision();          //GET THE RIGHT DYING TEXTURE HERE

			bool ProtectShieldEnable();

			///attacking system
			bool is_canKillEnemyWhileAttacking()
			{
				return CanKillEnemyWhileAttacking;
			}


			///check point pos
			void set_CheckPointPos(Math::Vector2D CheckPointPos_)
			{
				m_CheckPointPos = CheckPointPos_;
			}

			///change Player textureID --> is used in CheckPointObject
			void makePlayerInvisible()
			{
				m_textureID = "";
			}
			///is used in CheckPointObject  --> to make The Player stable
			void set_Position(Math::Vector2D Position_)
			{
				m_position = Position_;
			}

		private:                               //all these private I'll call new features

			void BringBackToLife();            //bring the Player back if there are lives (in the game.h system)left
											   //this is private cuz only Player has this feature
											   //GET THE RIGHT LIVING TEXTURE HERE
											   
			void HandleInput();				   //INPUT controls the Player

			void HandleAnimation();            //DO many kind of animation

			void HandleMovement();             //how the Player React when CollisionCheck
											   //BEST TILE COLLISION DETECTION AND COLLISION REACT

			void HandleFireBullet();

			//protect shield!!! --> the Player is invulnerable --> God mod -->for Ex: the Player reBorn --> it is TEMPORARILY invulnerable 
			bool m_ProtectShield;       //--->to protect the Player when brought back to live 
			int  m_ProtectShieldTime;   //--->protect about 3 sec(times)
			int  m_ProtectShieldTimeCounter;

			//attacking system
			const int attackingTime = 50;
			int attackingTimeCounter = 0;
			void attack();
			bool CanStartAttack = true;                 //always true at the first time
			
			const int DelayNextAttackTime = 20;
			int DelayNextAttackTimeCounter = 0;
			bool is_DelayNextAttack = false;           ///this is used when done one attack previously  ---> an we need to delay some amount of time
													   ///between 2 attack

			bool CanKillEnemyWhileAttacking = false;    ///we have to do this to only Kill Enemy 1 Health while the Player is attacking
														///because when the Player attack in a large amount of time --> it will have multiple
														///attack times --> which would kill our Enemy immediately
														///--> see more at ClosedAttackEnemy and FarAttackEnemy

		private:

			//saved info --> look into the collision() for more info
			int previousFrameWidth;
			int previousFrameHeight;
			int previousNumFrames;

			//jumping system
			bool Jumping = false;
			bool canStartJump = true;        //at first we are able to jump

			//changing direction
			bool goingLeft = false;
			bool goingRight = false;

			//CheckPointPos
			Math::Vector2D m_CheckPointPos = Math::Vector2D(100,100);   ///initial

			//3 random sound
			std::vector<string> PlayerDyingSounds;

			//ENTER SCREEN OF PLAYER IS ALWAYS TRUE
		};
	}
}

#endif