#pragma once

#ifndef SDLGAMEOBJECT_H
#define SDLGAMEOBJECT_H

#include"GameObject.h"
#include"LoadParams.h"
#include"graphic/TextureManager.h"  //draw() purpose


//#include"game.h"  --> this messed up -> circular include ! --> initial purpose was to get renderer from the game -> let's fix this


namespace HDT_engine
{
	namespace Game
	{

		class PlatformerObject: public GameObject            //inherit GameObject(abstract)
		{

		public:

			virtual ~PlatformerObject();					//for polymorphysm

			virtual void draw();
			virtual void update();						//standard animation and standard movement
			virtual void clean();						//over ride --> but not implement in this class
			virtual void load(unique_ptr<LoadParams>const &inputParams);   //over ride
			
			virtual void collision();                     //override --> but not implement in this class

			virtual void set_CollisionLayers(std::vector<LEVEL::TileLayer*>* p_CollisionLayers);
			virtual void set_p_MovingPlatforms(std::vector<GameObject*>* p_MovingPlatforms);
			virtual void set_p_CanBeInsidePlatforms(std::vector<GameObject*>* p_CanBeInsidePlatforms);

			virtual std::string Get_objectType();         //override 

			virtual void Set_scrollSpeed(int input_) {}   //not implement here --> at the moment this is only used for SCROLLINGBACKGROUND 
			virtual void Set_scrollSpeedBUFFER(int input_) {}

			virtual void set_Velocity(Math::Vector2D input);   //this is used in collision manager

			///is used for Water and Ladder
			virtual float& Get_DefaultMaxVelocityLimiter(){ return DEFAUT_MAXVELOCITYLIMITER; }

			bool is_attacking() { return attacking; }

		protected:
			PlatformerObject();					   //protected constructor
												   //----->The Player has its own dying in the Update

			bool checkCollideTile(Math::Vector2D& newPos);   //is used in Snail and Player for now
															//checking the newPos first then finally decide
															//the position to EQUAL to the newPos
															//see more at handleMovement() 

			void checkCollideMovingPlatform(Math::Vector2D& newPos);  //is used in handleMovement()

			void checkCollideCanBeInsidePlatform();  //is used in handleMovement()

			bool CollideMovingPlatformHorizontally = false;   ///is used in update
	
			bool MovingPlatform_Collide_Left_x = false;
			bool MovingPlatform_Collide_Right_x = false;
			bool MovingPlatform_Collide_Top_y = false;
			bool MovingPlatform_Collide_Bottom_y = false;												  //for more detail
																	  //MovingObject Collision system checking --> used in the function above
			GameObject* StandingOnPlatform = NULL;                    //is used for all kind of GameObject except MovingPlatform
			GameObject* InsidePlatform = NULL;                        ///inside WATER or LADDER

			int m_DyingTime;
			int m_DyingTimeCounter;

			int m_BulletReloadTime;                //reload one by one in this case
			int m_BulletReloadTimeCounter;

			bool m_b_Flipped = false;

			///ATTACK
			bool attacking = false;
		};


	}

}

#endif // !SDLGAMEOBJECT_H