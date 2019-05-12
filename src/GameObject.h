#pragma once

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include<iostream> //use precompiled header
#include<memory>
#include<string>

#include<SDL.h>

#include"graphic/TextureManager.h"
#include"LoadParams.h"

#include"math/Vector2D.h"           //implementing vector in SDL object

#include"Level/TileLayer.h"         //saving collision layer


using namespace std;

namespace HDT_engine
{

	namespace Game
	{

		class GameObject
		{
		public:

			virtual ~GameObject();   //virtual destructor -->this is IMPORTANT

			virtual void draw() = 0;
			
			virtual void update() = 0;
			
			virtual void clean() = 0;
			
			virtual void load(unique_ptr<LoadParams>const &inputParams) = 0;     //abstract -->remember to use smart pointer

			virtual void collision() = 0;         

			virtual void set_CollisionLayers(std::vector<LEVEL::TileLayer*>* p_CollisionLayers) = 0;	//remember ScrollingBackground Object 
																										//will have this but won't use this 
																										//...practically
																										//...this is used in parseGameObjectsLayers()
			virtual void set_p_MovingPlatforms(std::vector<GameObject*>* p_MovingPlatforms) = 0;
																	//for collision checking --> is used in parse ObjectLayer

			virtual void set_p_CanBeInsidePlatforms(std::vector<GameObject*>* p_CanBeInsidePlatforms) = 0;
																	//for collision checking --> is used in parse ObjectLayer

			virtual std::string Get_objectType() = 0;

			Math::Vector2D& Get_Position();						  //not virtual anymore

			int& Get_ScreenWidth();								  //how the object is drawn on the screen(do not get me wrong)

			int& Get_ScreenHeight();

			void Scroll(int scrollVelocity_);                     //scroll along with TileMAP (int TileLayer class)--->in this case if the object is moving toward-->
																  //-->then the (scroll speed is < 0) cuz the TileMAP is moving backward relative to
																  //the screen coordinate
			
			bool isWithinScreen();								  //is the object currently being updated ? --> but what to do ? -->to see if ...
																  //...the object is still WITHIN the screen after being scrolled with the TILEMAP
																  //right now it is only used for Player

			void Set_isWithinScreen(bool is_withinscreen_);

			bool isDead();

			bool isDying();        

			bool isEnterScreen();

			Math::Vector2D& Get_position();

			Math::Vector2D& Get_velocity()
			{
				return m_velocity;
			}

			virtual void Set_scrollSpeed(int input_) = 0;   //not implement here --> at the moment this is only used for SCROLLINGBACKGROUND
			virtual void Set_scrollSpeedBUFFER(int input_) = 0;


			virtual void set_Velocity(Math::Vector2D input) = 0;

			///is used for Water and Ladder
			virtual float& Get_DefaultMaxVelocityLimiter() = 0;

		protected:             //used by derived class

			//PROTECTED CONSTUCTOR !!!
			GameObject();									//init list (init all variables below) -->just to avoid GARBAGE VALUE


			bool is_withinscreen;                           //the object IS WITHIN SCREEN  (true or false) --> riht now used for PLAYER only
			bool is_dead;										
			bool is_dying;
			bool EnterScreen;							    //-->have this cuz of scrolling --> check for enemy only

			//(parse all these)     //from now on, we'll parse the the most basic attribute of a gameObject, the rest is managed within game
			int m_screenWidth;                  
			int m_screenHeight;
			int m_FrameWidth;		//for cutting and animating
			int m_FrameHeight;
			int m_numFrames;        //remember this is only for animatedGraphic ? --> well cuz we are making a real game so -->TAKE RISK
			int animSpeed;          //same for animation speed
			int m_callBackID;
			string m_textureID;	    //a gameobject has its own texture "ID"
			float m_scrollSpeed;      //right now it is only used for ScrollingBackground objects
									//---->but has potential in the future
			string m_DyingTextureID;
			int m_DyingFrameWidth;
			int m_DyingFrameHeight;
			int m_DyingNumFrames;

			//animating variable
			int m_currentRow;       //always = 0 for now
			int m_currentColumn;
			
			//rotation 
			int m_angle;

			//blending the object's texture
			int m_alpha;
			
			Math::Vector2D m_position;               //this one is PARSED

			Math::Vector2D m_velocity;
			Math::Vector2D m_acceleration;
			float m_MaxVelocityLimiter;    ///value should be 0<= value <1

			//pointing to a function  --> Set_CallBack() is used by each state
			void(*m_callBack)();

			//pointer to collisionLayers
			std::vector<LEVEL::TileLayer*>* p_CollisionLayers;

			//pointer to MovingPlatforms  // for checking collision
			std::vector<GameObject*>* p_MovingPlatforms;

			//pointer to CanBeInsidePlatforms
			std::vector<GameObject*>* p_CanBeInsidePlatforms;

			///DEFAULT VALUES --> is used when moving out of a InsidePlatform (WATER , LADDER)
			float  DEFAUT_MAXVELOCITYLIMITER;
			float  DEFAULT_GRAVITY;
		};
	}
}

#endif