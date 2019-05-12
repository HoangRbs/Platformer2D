#pragma once
#ifndef PLAYERCONTROLSCROLLINGBACKGROUND_H
#define PLAYERCONTROLSCROLLINGBACKGROUND_H
#include"Math/Vector2D.h"
#include"GameObject.h"

namespace HDT_engine
{
	namespace Game
	{
		class PlayerControlScrollingBackground                     //SINGLETON --> is used in Player.cpp and Scrollingbackground.cpp
																   //if you do not want Player to take control over ScrollingBackground
																   //you can just disable the code in those two files --> reusable
		{
		public:
			PlayerControlScrollingBackground()
			{
				PlayerVel = Math::Vector2D(0,0);
				PlayerPos = Math::Vector2D(0,0);
				PlayerBackToLife = false;
			}

			~PlayerControlScrollingBackground()
			{

			}

			static PlayerControlScrollingBackground* Instance();              

			void set_PlayerVel(Math::Vector2D PlayerVel_);          //is used in Player::Update();
			void set_PlayerPos(Math::Vector2D PlayerPos_);          //is used in Player::Update();
			void set_PlayerStandingOnPlatform(GameObject* StandingOnPlatform_);			//is used in Player::Update();
			GameObject* get_PlayerStandingOnPlatform()              //this is used in ScrollingBackground
			{
				return StandingOnPlatform;							///this is used when Player is standing on a Platform
			}														///because of my code --> if not use this the scrollinBackground
																	///won't move properly
			Math::Vector2D get_PlayerVel()
			{
				return PlayerVel;
			}

			Math::Vector2D get_PlayerPos()
			{
				return PlayerPos;
			}

			bool isPlayerBackToLife()
			{
				return PlayerBackToLife;
			}

			void set_PlayerBackToLife(bool input_)
			{
				PlayerBackToLife = input_;
			}

			void Set_ThePlayer(GameObject* ThePlayer)        ///is used in Player Load()
			{
				this->ThePlayer = ThePlayer;
			}

			GameObject* Get_ThePlayer()                     ///is used in ScrollingBackground
			{
				return ThePlayer;
			}

		private:
			static PlayerControlScrollingBackground* instance;

			Math::Vector2D PlayerVel;
			Math::Vector2D PlayerPos;

			GameObject* StandingOnPlatform = NULL;
			GameObject* ThePlayer = NULL;

			bool PlayerBackToLife;
		};
	}
}
#endif