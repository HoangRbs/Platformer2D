#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include"math/Vector2D.h"
#include"GameObject.h"

namespace HDT_engine
{
	//THIS IS REALLY IMPORTANT CLASS
	//IT IS USED IN EVERY CORNER IN THIS ENGINE
	//WHERE HAVE COORDINATE AND SCREEN
	//THERE HAS CAMERA

	namespace Game                   //singleton
	{
		class Camera
		{
		public:
			~Camera()
			{

			}

			static Camera* Instance();

			void setTargetInfo(Math::Vector2D* p_TargetPos, Math::Vector2D* p_TargetVel)  //is used in Player::load() and in levelParser
			{ 
				this->TargetPos = p_TargetPos; 
				this->TargetVel = p_TargetVel;
			}


			void Update();             //will be used in game::update() because the whole game system display uses camera()
									   //even menustate

			void saveTargetPosPausedState(Math::Vector2D* p_TargetPos) { this->savedTargetPosPausedState = p_TargetPos; }   //is used in pauseState
			void saveTargetVelPausedState(Math::Vector2D* p_TargetVel) { this->savedTargetVelPausedState = p_TargetVel; }	//is used in pauseState

			Math::Vector2D* getTargetPos() { return TargetPos; }           //is used in pauseState
			Math::Vector2D* getTargetVel() { return TargetVel; }		   //is used in paused state
			
			Math::Vector2D* getSavedTargetPosPausedState() { return savedTargetPosPausedState; }              //is used in PauseState
			Math::Vector2D* getSavedTargetVelPausedState() { return savedTargetVelPausedState; }			  //is used in paused state

			Math::Vector2D& getCamPos();
			Math::Vector2D& getCamVel();

			void Set_ThePlayer(GameObject* ThePlayer_);         /// used in Player Load
			GameObject* Get_ThePlayer();                      /// used in Scrolling Background Object

			///for optimizing--> since the camera update only once a loop --> so its info only change once a loop
			///no need to call getPos multiple times in one loop --> just one time a loop and then we'll save the camara info
			///then use for all other objects
			float& Get_OptimizeLagCamPos_x()
			{
				return OptimizeLagCamPos_x;
			}

			float& Get_OptimizeLagCamPos_y()
			{
				return OptimizeLagCamPos_y;
			}			

      	private:
			Camera();

			Math::Vector2D* TargetVel;
			Math::Vector2D* TargetPos;

			Math::Vector2D* savedTargetPosPausedState;       //is used in Pausedstate --> look in to it for more information
			Math::Vector2D* savedTargetVelPausedState;
			
			Math::Vector2D CameraPos;
			Math::Vector2D CameraVel;

			//Juicy camera movement algorithm
			Math::Vector2D JuicyPointPos;
			Math::Vector2D JuicyPointVel;
			const int JUICY_SPEED = 100;
			const int JUICY_RANGE = 50;

			static Camera* instance;

			///for optimizing--> since the camera update only once a loop --> so its info only change once a loop
			///no need to call getPos multiple times in one loop --> just one time a loop and then we'll save the camara info
			///then use for all other objects
			float OptimizeLagCamPos_x;
			float OptimizeLagCamPos_y;

			GameObject* ThePlayer = NULL;
		};
	}
}
#endif