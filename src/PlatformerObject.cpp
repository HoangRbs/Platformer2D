#include"PlatformerObject.h"
#include"Camera.h"
#include"game.h"
#include"Collision.h"


//TESTING --> DELETE LATER
#include"graphic/TextureManager.h"
//

namespace HDT_engine
{
	namespace Game
	{

		PlatformerObject::~PlatformerObject()
		{

		}

		void PlatformerObject::draw()     
		{
			if (EnterScreen)
			{
				if (!is_dying)
				{
					if (m_b_Flipped)
					{
						Graphic::TextureManager::Instance()->drawFrameFlip(m_textureID,
							m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x(),
							m_position.get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y(),
							m_FrameWidth, m_FrameHeight,
							m_screenWidth, m_screenHeight,
							m_currentColumn, m_currentRow,
							m_angle, m_alpha, SDL_FLIP_HORIZONTAL);
					}
					else
					{
						Graphic::TextureManager::Instance()->drawFrame(m_textureID,
							m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x(),
							m_position.get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y(),
							m_FrameWidth, m_FrameHeight,
							m_screenWidth, m_screenHeight,
							m_currentColumn, m_currentRow,
							m_angle, m_alpha);
					}

				}
				else      //is dying cmnr
				{
					Graphic::TextureManager::Instance()->drawFrame(m_DyingTextureID,
						m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x(),
						m_position.get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y(),
						m_DyingFrameWidth, m_DyingFrameHeight,
						m_screenWidth, m_screenHeight,
						m_currentColumn, m_currentRow,
						m_angle, m_alpha);
				}
			}
			
		} 

		void PlatformerObject::update()
		{

			if (!is_dying)
			{
				if (EnterScreen)
					m_currentColumn = (SDL_GetTicks() / (animSpeed)) % m_numFrames; //standard animation
			}
			else         //dying cmnr
			{
				//if(EnterScreen)  //MAYBE WHEN DYING JUST LET IT DIE UNTIL IT IS DEAD --> no need to check
				m_currentColumn = (SDL_GetTicks() / (animSpeed)) % m_DyingNumFrames;
			}

			if (EnterScreen)
			{
				if (StandingOnPlatform != NULL)
				{
					///RELATIVE MOTION --> SEARCH FOR MORE DETAIL
					///WE'RE CALCULATING VEL_Player on DISK coordinate -->VEL_PLAYER-DISK


					m_velocity.set_x((m_velocity.get_x() - (m_velocity.get_x())* m_MaxVelocityLimiter)
						+ m_acceleration.get_x() * deltaTime);

					m_velocity.set_y(StandingOnPlatform->Get_velocity().get_y());

					m_position.set_y(m_position.get_y() + m_velocity.get_y());
					m_position.set_x(m_position.get_x() + m_velocity.get_x() + StandingOnPlatform->Get_velocity().get_x());

				}
				else if (CollideMovingPlatformHorizontally)
				{
					m_position += m_velocity;
				}
				else
				{
					m_velocity = (m_velocity - m_velocity * m_MaxVelocityLimiter) + m_acceleration * deltaTime;								  //standard movement
					m_position += m_velocity;								  //standard movement
				}

			}
		}

		void PlatformerObject::clean()
		{
			Graphic::TextureManager::Instance()->clearFromTextureMap(m_textureID);
			Graphic::TextureManager::Instance()->clearFromTextureMap(m_DyingTextureID);
			m_callBack = NULL;
		}

		void PlatformerObject::load(unique_ptr<LoadParams>const& inputParams)
		{
			//standard load(outside parsing/loading)
			m_position.set_x(inputParams->get_x());
			m_position.set_y(inputParams->get_y());
			m_screenWidth = inputParams->get_screenWidth();
			m_screenHeight = inputParams->get_screenHeight();
			m_textureID = inputParams->get_textureID();
			m_FrameWidth = inputParams->get_FrameWidth();
			m_FrameHeight = inputParams->get_FrameHeight();
			m_callBackID = inputParams->get_m_callbackID();
			m_numFrames = inputParams->get_numFrames();
			animSpeed = inputParams->get_animSpeed();
			m_scrollSpeed = inputParams->get_scrollSpeed();

			m_DyingTextureID = inputParams->get_DyingTextureID();
			m_DyingFrameWidth = inputParams->get_DyingFrameWidth();
			m_DyingFrameHeight = inputParams->get_DyingFrameHeight();
			m_DyingNumFrames = inputParams->get_DyingNumFrames();

			//special load(inside loading)
			m_velocity.set_x(0);
			m_velocity.set_y(0);
			m_acceleration.set_x(0);
			m_acceleration.set_y(0);

			//for bullets object
			m_velocity = inputParams->get_BulletVel();
			m_acceleration = inputParams->get_BulletAcc();

			//standard load
			m_MaxVelocityLimiter = 0.0f;
		}

		void PlatformerObject::collision()
		{
			//not implement in this class
		}

		PlatformerObject::PlatformerObject():GameObject()    //call init list in gameobject --> that's why it is PROTECTED
		{

		}

		std::string PlatformerObject::Get_objectType()
		{
			return("PlatformerObject");
		}
		
		void PlatformerObject::set_CollisionLayers(std::vector<LEVEL::TileLayer*>* p_CollisionLayers)
		{
			this->p_CollisionLayers = p_CollisionLayers;
		}

		void PlatformerObject::set_p_CanBeInsidePlatforms(std::vector<GameObject*>* p_CanBeInsidePlatforms)
		{
			this->p_CanBeInsidePlatforms = p_CanBeInsidePlatforms;
		}

		void PlatformerObject::set_p_MovingPlatforms(std::vector<GameObject*>* p_MovingPlatforms)
		{
			this->p_MovingPlatforms = p_MovingPlatforms;
		}

		void PlatformerObject::set_Velocity(Math::Vector2D input)
		{
			m_velocity = input;
		}

		bool PlatformerObject::checkCollideTile(Math::Vector2D& newPos)
		{
			for (int layer_index = 0 ; layer_index < p_CollisionLayers->size() ; layer_index++)
			{
				Math::Vector2D MapPosition = p_CollisionLayers->at(layer_index)->Get_MapPosition();
				int MapWidthSize = p_CollisionLayers->at(layer_index)->Get_MapWidthSize();
				int MapHeightSize = p_CollisionLayers->at(layer_index)->Get_MapHeightSize();
				
				if (newPos.get_x() < MapPosition.get_x() - 32 || newPos.get_x() + m_screenWidth >= MapPosition.get_x() + MapWidthSize ||
					newPos.get_y() < MapPosition.get_y() - 32 || newPos.get_y() + m_screenHeight >= MapPosition.get_y() + MapHeightSize)      //outside of the current TileMapSize of the current CollisionLayer --> do nothing --> no check
				{
					//WAIT!!--> why - 32 --> just delete 32 to test it (test at the beginning)

					continue;           //no check anymore --> this step is really important
				}

				int MapTileSize = p_CollisionLayers->at(layer_index)->Get_TileSize();

				Math::Vector2D startPos = newPos;

				startPos.set_x(startPos.get_x() + 15);         //15 < tileSize / 2
				startPos.set_y(startPos.get_y() + 15);		   //20 < tileSize / 2

				Math::Vector2D endPos(newPos.get_x() + (m_screenWidth - 15), newPos.get_y() + (m_screenHeight - 4));  //4 < tileSize/2

				for (int i = startPos.get_y(); i < endPos.get_y(); i += 2)
				{
					for (int j = startPos.get_x(); j < endPos.get_x(); j += 2)
					{
						int currentTileMapRow = (i - MapPosition.get_y()) / MapTileSize;
						int currentTileMapColumn = (j - MapPosition.get_x()) / MapTileSize;

						if (p_CollisionLayers->at(layer_index)->Get_tileMapIDs()->at(currentTileMapRow).at(currentTileMapColumn) != 0)
						{
							return true;
						}
					}
				}
			}

			//no collide with any of those layers' TileMap
			return false;
		}

		void PlatformerObject::checkCollideMovingPlatform(Math::Vector2D& newPos)
		{
			SDL_Rect* Rect_1_current = new SDL_Rect();  //save current info
			SDL_Rect* Rect_1 = new SDL_Rect();
			SDL_Rect* Rect_2_current = new SDL_Rect();
			SDL_Rect* Rect_2 = new SDL_Rect();
			
			//just to make the all Objects' RECT smaller a little bit except MovingPlatform
			int BUFFERw_ = m_screenWidth / 10;
			int BUFFERh_ = m_screenHeight / 10; // --> for now this is the most accurate

			Rect_1_current->x = m_position.get_x(); + BUFFERw_;
			Rect_1_current->y = m_position.get_y(); + BUFFERh_;

			Rect_1->x = newPos.get_x() + BUFFERw_;
			Rect_1->y = newPos.get_y() + BUFFERh_;
			Rect_1->w = Rect_1_current->w = m_screenWidth - 2*BUFFERw_;
			Rect_1->h = Rect_1_current->h = m_screenHeight - 2 * BUFFERh_;

			Math::Vector2D* Rect_1_Vel = &m_velocity;   ///do not delete this shit --> WTF this is the old velocity!!! --> do we really need
			                                            ///the new one

			for (int i = 0; i < p_MovingPlatforms->size(); i++)
			{
				if (!p_MovingPlatforms->at(i)->isEnterScreen())
				{
					continue;
				}

				Math::Vector2D* Rect_2_Vel = &p_MovingPlatforms->at(i)->Get_velocity();  ///do not delete this shit
		
				Rect_2_current->x = Rect_2->x = p_MovingPlatforms->at(i)->Get_Position().get_x();
				Rect_2_current->y = Rect_2->y = p_MovingPlatforms->at(i)->Get_Position().get_y(); 
				Rect_2_current->w = Rect_2->w = p_MovingPlatforms->at(i)->Get_ScreenWidth();
				Rect_2_current->h = Rect_2->h = p_MovingPlatforms->at(i)->Get_ScreenHeight();


				///horizontally
				if (Rects_Collided(Rect_1,Rect_2) && Rect_1_current->x > Rect_2->x + Rect_2->w)
				{
					MovingPlatform_Collide_Right_x = true;
				}

				if (Rects_Collided(Rect_1, Rect_2) && Rect_1_current->x + Rect_1_current->w < Rect_2->x)
				{
					MovingPlatform_Collide_Left_x = true;
				}

				///for more precise when cheking vertically
				if (Rect_1_Vel->get_y() * Rect_2_Vel->get_y() < 0)    ///if Rect_2 and Rect_1 are reversed directions(VERTICALLY)
					                       ///this is only used for VERTICALLY CHECKING BELOW CUZ WHEN FALLING --> WE'LL HAVE GRAVITY
					                       ///--> WHICH IS QUITE COMPLICATED
				{
					Rect_2->y += Rect_2_Vel->get_y();
				}
				///else no change


				if (Rects_Collided(Rect_1, Rect_2) && Rect_1_current->y >= Rect_2->y + Rect_2->h)//this is the most tricky part
														//have to add some more features in this --> newPos Rect_2 , Vel1 * Vel2 >< 0
				{
					MovingPlatform_Collide_Bottom_y = true;
				}

				//STANDING ON PLATFORM AND TOP Y
				if (StandingOnPlatform == NULL)         
				{
					if (Rects_Collided(Rect_1, Rect_2) && Rect_1_current->y + Rect_1_current->h <= Rect_2->y) //this is the most tricky part
															
					{
						MovingPlatform_Collide_Top_y = true;
					}
				}
				else  ///the object is connecting with the Disk platform
				{
					if (p_MovingPlatforms->at(i) == StandingOnPlatform)        ///is the current Disk the platform we're standing on
					{

						if (!Rects_Collided(Rect_1, Rect_2))    ///this happens when we try to jump from it
						{
							StandingOnPlatform = NULL;
						}
					}
				}
				//

				if (MovingPlatform_Collide_Right_x || MovingPlatform_Collide_Left_x)
				{
					Rect_1_Vel->set_x(Rect_2_Vel->get_x());
					CollideMovingPlatformHorizontally = true;
				}
				else
				{
					CollideMovingPlatformHorizontally = false;
				}
				
				//STANDING ON PLATFORM AND TOP Y
				if (MovingPlatform_Collide_Top_y)          ///standing on platform --> gonna add some more functions into this
				{
					///gotta do something different here
					StandingOnPlatform = p_MovingPlatforms->at(i);
					
				}
				//

				if (MovingPlatform_Collide_Bottom_y)
				{
					Rect_1_Vel->set_y(0);
					m_acceleration.set_y(3);
				}
			

				MovingPlatform_Collide_Left_x = false;
				MovingPlatform_Collide_Right_x = false;
				MovingPlatform_Collide_Top_y = false;
				MovingPlatform_Collide_Bottom_y = false;
			}

			delete Rect_1;
			delete Rect_2;
			delete Rect_1_current;
			delete Rect_2_current;
		}

		void PlatformerObject::checkCollideCanBeInsidePlatform()
		{
			SDL_Rect* Rect_1 = new SDL_Rect();
			SDL_Rect* Rect_2 = new SDL_Rect();

			Rect_1->x = m_position.get_x();
			Rect_1->y = m_position.get_y();
			Rect_1->w = m_screenWidth;
			Rect_1->h = m_screenHeight;

			for(int i = 0; i< p_CanBeInsidePlatforms->size();i++)
			{

				if (!p_CanBeInsidePlatforms->at(i)->isEnterScreen())
				{
					continue;
				}

				Rect_2->x = p_CanBeInsidePlatforms->at(i)->Get_Position().get_x();
				Rect_2->y = p_CanBeInsidePlatforms->at(i)->Get_Position().get_y();
				Rect_2->w = p_CanBeInsidePlatforms->at(i)->Get_ScreenWidth();
				Rect_2->h = p_CanBeInsidePlatforms->at(i)->Get_ScreenHeight();

				if (Rects_Collided(Rect_1, Rect_2))
				{
					if (Rect_1->y + 15 >= Rect_2->y && Rect_1->y + 15 < Rect_2->y + Rect_2->h)            ///disable this if to understand when in a InsidePlatform
					{
						InsidePlatform = p_CanBeInsidePlatforms->at(i);

						///init new environment
						if (Get_objectType() == "Player")        ///this check type should be used for Player only
						{
							m_MaxVelocityLimiter = p_CanBeInsidePlatforms->at(i)->Get_DefaultMaxVelocityLimiter();
						}
					}
				}
				else
				{
					///not collide with the CURRENT platfrom any more
					///the init every thing back to normal
					if (Get_objectType() == "Player")
					{
						if (p_CanBeInsidePlatforms->at(i) == InsidePlatform)
						{
							InsidePlatform = NULL;
							m_MaxVelocityLimiter = DEFAUT_MAXVELOCITYLIMITER;
						}
					}
				}
			}

			delete Rect_1;
			delete Rect_2;
		}
	}
}