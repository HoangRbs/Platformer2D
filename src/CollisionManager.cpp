#include"CollisionManager.h"
#include"BulletHandler.h"
#include"Collision.h"
#include"sound/SoundManager.h"
#include"MoreEnemies/FarAttackEnemy.h"
#include"MoreEnemies/CantBeHurtEnemy.h"
#include"MoreEnemies/ClosedAttackEnemy.h"
#include"DeadSprite.h"

namespace HDT_engine
{
	namespace Game
	{
		/*
		void CollisionManager::CheckEnemies_PlayerBulletsCollision(std::vector<GameObject*>& m_gameObjects_)
		{

			vector<PlayerBullet*>* tempPlayerBullets = BulletHandler::Instance()->Get_PlayerBullets();
			SDL_Rect* Rect_1 = new SDL_Rect();
			SDL_Rect* Rect_2 = new SDL_Rect();

			for (int i = 0; i < m_gameObjects_.size(); i++)       //cuz we do not delete anything in the vector --> so i++ is still there
			{

				if (m_gameObjects_.at(i)->isDead() || m_gameObjects_.at(i)->isDying()
					|| m_gameObjects_.at(i)->Get_objectType() != std::string("Enemy")
					|| !m_gameObjects_.at(i)->isEnterScreen())        //Enemy is not in the screen
				{
					continue;
				}

				Rect_2->x = m_gameObjects_.at(i)->Get_Position().get_x();
				Rect_2->y = m_gameObjects_.at(i)->Get_Position().get_y();
				Rect_2->w = m_gameObjects_.at(i)->Get_ScreenWidth();
				Rect_2->h = m_gameObjects_.at(i)->Get_ScreenHeight();

				for (int j = 0; j < tempPlayerBullets->size(); j++)
				{
					//cout << "ERROR HERE" << endl;

					Rect_1->x = tempPlayerBullets->at(j)->Get_Position().get_x();
					Rect_1->y = tempPlayerBullets->at(j)->Get_Position().get_y();
					Rect_1->w = tempPlayerBullets->at(j)->Get_ScreenWidth();
					Rect_1->h = tempPlayerBullets->at(j)->Get_ScreenHeight();

					if (Rects_Collided(Rect_1, Rect_2))
					{

						SOUND::SoundManager::Instance()->PlaySoundEffect("Explosion", 0);
						tempPlayerBullets->at(j)->collision();
						m_gameObjects_.at(i)->collision();
					}
				}
			}

			delete Rect_1;
			delete Rect_2;
		}

		*/

		
		void CollisionManager::CheckPlayer_EnemyBulletCollision(Player* inputPlayer)
		{
			SDL_Rect* Rect_1 = new SDL_Rect();
			Rect_1->x = inputPlayer->Get_Position().get_x() ;
			Rect_1->y = inputPlayer->Get_Position().get_y() ;
			Rect_1->w = inputPlayer->Get_ScreenWidth() ;
			Rect_1->h = inputPlayer->Get_ScreenHeight();

			SDL_Rect* Rect_2 = new SDL_Rect();

			EnemyBullet* tempEnemyBullet = new EnemyBullet();



			for (int i = 0; i < BulletHandler::Instance()->Get_EnemyBullets()->size(); i++)
			{
				tempEnemyBullet = BulletHandler::Instance()->Get_EnemyBullets()->at(i);

				Rect_2->x = tempEnemyBullet->Get_Position().get_x();
				Rect_2->y = tempEnemyBullet->Get_Position().get_y();
				Rect_2->w = tempEnemyBullet->Get_ScreenWidth();
				Rect_2->h = tempEnemyBullet->Get_ScreenHeight();

				if ((!inputPlayer->isDying() && !inputPlayer->ProtectShieldEnable()) && !tempEnemyBullet->isDying())
				{

					if (Rects_Collided(Rect_1, Rect_2))
					{

						SOUND::SoundManager::Instance()->PlaySoundEffect("EXPLOSION", 0);
						inputPlayer->collision();
						tempEnemyBullet->collision();
					}
				}
			}

			delete Rect_1;
			delete Rect_2;
		}
		

		void CollisionManager::CheckPlayer_EnemiesCollision(Player* inputPlayer, std::vector<GameObject*>& m_gameObjects_)
		{

			SDL_Rect* Rect_1 = new SDL_Rect();
			SDL_Rect* Rect_2 = new SDL_Rect();

			//just to make the PLAYER RECT smaller a little bit 
			int BUFFERw_ = inputPlayer->Get_ScreenWidth() / 5;
			int BUFFERh_ = inputPlayer->Get_ScreenHeight() / 5;

			Rect_1->x = inputPlayer->Get_Position().get_x() + BUFFERw_;
			Rect_1->y = inputPlayer->Get_Position().get_y() + BUFFERh_;
			Rect_1->w = inputPlayer->Get_ScreenWidth() - 2 * BUFFERw_;
			Rect_1->h = inputPlayer->Get_ScreenHeight() - 2 * BUFFERh_;

			if (inputPlayer->isDying() || inputPlayer->ProtectShieldEnable())
			{
				return;
			}

			for (int i = 0; i < m_gameObjects_.size(); i++)
			{
			
				if (m_gameObjects_.at(i)->isDead() || m_gameObjects_.at(i)->isDying() ||
					m_gameObjects_.at(i)->Get_objectType() != "Enemy"
					|| !m_gameObjects_.at(i)->isEnterScreen())
				{
					continue;
				}

				GameObject* tempEnemyObject = m_gameObjects_.at(i);

				Rect_2->x = tempEnemyObject->Get_Position().get_x();
				Rect_2->y = tempEnemyObject->Get_Position().get_y();
				Rect_2->w = tempEnemyObject->Get_ScreenWidth();
				Rect_2->h = tempEnemyObject->Get_ScreenHeight();


				if (Rects_Collided(Rect_1, Rect_2))
				{
					if (dynamic_cast<CantBeHurtEnemy*>(tempEnemyObject))
					{
						SOUND::SoundManager::Instance()->PlaySoundEffect("EXPLOSION", 0);
						inputPlayer->collision();
						tempEnemyObject->collision();
					}

					if (dynamic_cast<ClosedAttackEnemy*>(tempEnemyObject))
					{
						ClosedAttackEnemy* thisEnemy = dynamic_cast<ClosedAttackEnemy*>(tempEnemyObject);
						///the case if Enemy is being attacked by the Player will be checked inside that Enemy

						///the case Enemy attacking our Player
						if (thisEnemy->is_attacking())
						{
							SOUND::SoundManager::Instance()->PlaySoundEffect("EXPLOSION", 0);
							inputPlayer->collision();
						}
					}

					if (dynamic_cast<DeadSprite*>(tempEnemyObject))
					{
						SOUND::SoundManager::Instance()->PlaySoundEffect("EXPLOSION", 0);
						inputPlayer->collision();
					}

					///the FarAttackOne will use Bullet to check

				}

			}

			delete Rect_1;
			delete Rect_2;
		}

		//void CollisionManager::CheckPlayer_TileLayerCollision(Player* inputPlayer, std::vector<LEVEL::TileLayer*>& CollisionLayers ,
		//													  int numTileMapWidth, int numTileMapHeight)
		//{
			//this collision checking will be a little different

			/*      RIGHT NOW WE'LL NOT GONNA USE THIS ----> USE FOR LATER ADVENTURE GAME

			if ((!inputPlayer->isDying()) && !inputPlayer->ProtectShieldEnable())
			{

				for (int i = 0; i < CollisionLayers.size(); i++)
				{
					int tileSize = CollisionLayers.at(i)->Get_TileSize();

					int Map_TilePos_x = CollisionLayers.at(i)->Get_MapPosition().get_x() / tileSize;
					int Map_TilePos_y = CollisionLayers.at(i)->Get_MapPosition().get_y() / tileSize;

					int Player_TilePos_x = 0;
					int Player_TilePos_y = 0;

					int PlayerColumnOnMap = 0;
					int PlayerRowOnMap = 0;

					int Player_Vel_x = inputPlayer->Get_velocity().get_x();
					int Player_Vel_y = inputPlayer->Get_velocity().get_y();

					int Player_Pos_x = inputPlayer->Get_Position().get_x();
					int Player_Pos_y = inputPlayer->Get_Position().get_y();

					int Player_ScreenWidth = inputPlayer->Get_ScreenWidth();
					int Player_ScreenHeight = inputPlayer->Get_ScreenHeight();

					int Map_Pos_x = CollisionLayers.at(i)->Get_MapPosition().get_x();
					int Map_Pos_y = CollisionLayers.at(i)->Get_MapPosition().get_y();

					int Player_Pos_x = inputPlayer->Get_Position().get_x();
					int Player_Pos_y = inputPlayer->Get_Position().get_y();

					int Player_Vel_x = inputPlayer->Get_velocity().get_x();
					int Player_Vel_y = inputPlayer->Get_velocity().get_y();

					int PlayerPosOnMap_x = 0;
					int PlayerPosOnMap_y = 0;



					if (Player_Vel_x >= 0 || Player_Vel_y >= 0)
					{

						Player_TilePos_x = (Player_Pos_x + Player_ScreenWidth) / tileSize;

						if (((Player_Pos_x + Player_ScreenWidth) % tileSize) > 0)     //more precise
						{
							Player_TilePos_x++;
						}

						Player_TilePos_y = (Player_Pos_y + Player_ScreenHeight) / tileSize;

						if (((Player_Pos_y + Player_ScreenHeight) % tileSize) > 0)
						{
							Player_TilePos_y++;
						}

					}
					else if (Player_Vel_x < 0 || Player_Vel_y < 0)
					{

						Player_TilePos_x = Player_Pos_x / tileSize;


						if ((Player_Pos_x % tileSize) > 0)
						{
							Player_TilePos_x++;					//this is my later edit --> not quite true --> gonna look at it later
						}

						Player_TilePos_y = Player_Pos_y / tileSize;

						if ((Player_Pos_y % tileSize) > 0)
						{
							Player_TilePos_y++;         //this is my later edit --> not quite true --> gonna look at it later
						}


					}


					PlayerColumnOnMap = (Player_TilePos_x) - (Map_TilePos_x + 1);
					PlayerRowOnMap = (Player_TilePos_y) - (Map_TilePos_y + 1);


					if (PlayerRowOnMap < (numTileMapHeight) && PlayerColumnOnMap < (numTileMapWidth)
						&& PlayerRowOnMap >= 0 && PlayerColumnOnMap >= 0)									     //avoid causing ERROR
					{

						if (CollisionLayers.at(i)->Get_tileMapIDs()[PlayerRowOnMap][PlayerColumnOnMap] != 0)     //this SHIT cause ERROR abort()
						{
							cout << "Player and Tile collided" << endl;
							cout << "Row : " << PlayerRowOnMap << " , Column: "<<PlayerColumnOnMap<<endl;
							SOUND::SoundManager::Instance()->PlaySoundEffect("Explosion", 0);
							inputPlayer->collision();
						}
					}


				}

			}

			*/




			//}

		void CollisionManager::CheckOtherObjects_MovingPlatformsCollision(std::vector<GameObject*>* gameObjects,
			std::vector<GameObject*>* MovingPlatforms)
		{
			SDL_Rect* Rect_1 = new SDL_Rect();
			SDL_Rect* Rect_2 = new SDL_Rect();

			for (int i = 0; i < gameObjects->size(); i++)
			{
				if (gameObjects->at(i)->isDead() || gameObjects->at(i)->isDying() ||
					gameObjects->at(i)->Get_objectType() == std::string("MovingPlatform")
					|| !gameObjects->at(i)->isEnterScreen())
				{
					continue;
				}

				//just to make the all Objects' RECT smaller a little bit except MovingPlatform
				int BUFFERw_ = gameObjects->at(i)->Get_ScreenWidth() / 5;
				int BUFFERh_ = gameObjects->at(i)->Get_ScreenHeight() / 5;

				//getting the velocity
				///do not delete this pointer!!!
				Math::Vector2D* Rect_1_Vel = &gameObjects->at(i)->Get_velocity();     

				//Rect_1.x.y is actually NEW POS cuz the current object(except )
				Rect_1->x = (gameObjects->at(i)->Get_Position().get_x() + BUFFERw_) + Rect_1_Vel->get_x();
				Rect_1->y = (gameObjects->at(i)->Get_Position().get_y() + BUFFERh_) + Rect_1_Vel->get_y();
				//this is actually the NEW POS --> we apply the same technic like we did with Tile Collide

				Rect_1->w = gameObjects->at(i)->Get_ScreenWidth() - 2 * BUFFERw_;
				Rect_1->h = gameObjects->at(i)->Get_ScreenHeight() - 2 * BUFFERh_;

				///do not delete this pointer!!!
				Math::Vector2D* Rect_2_Vel;

				for (int j = 0; j < MovingPlatforms->size(); j++)
				{
					if (!MovingPlatforms->at(j)->isEnterScreen())
					{
						continue;
					}

					/*static */ Rect_2_Vel = &MovingPlatforms->at(j)->Get_velocity();
					///I call it static so that it won't have to create and delete a new variable
					///test that later ^^

					Rect_2->x = (MovingPlatforms->at(j)->Get_Position().get_x()) + Rect_2_Vel->get_x();
					Rect_2->y = (MovingPlatforms->at(j)->Get_Position().get_y()) + Rect_2_Vel->get_y();
					//NEW POS METHOD

					Rect_2->h = MovingPlatforms->at(j)->Get_ScreenHeight();
					Rect_2->w = MovingPlatforms->at(j)->Get_ScreenWidth();

					//we cannot use Rect Collided here --> with MovingPlatform --> we gonna have to use different method

					//if the objects is pushed by moving platforms horizontally
					///checking horizontally
					if (Rect_1_Vel->get_x() * Rect_2_Vel->get_x() > 0)   ///the same direction
					{
						if (Rects_Collided(Rect_1,Rect_2))
						{

							Rect_1_Vel->set_x(0);                   ///stop the object right now (horizontally)
							gameObjects->at(i)->set_Velocity(*Rect_1_Vel);
						}
					}
					else    /// <= 0 , reverse direction                                      
					{
						if (Rects_Collided(Rect_1, Rect_2))
						{
							Rect_1_Vel->set_x(Rect_2_Vel->get_x());       ///be pushed by moving platform
							gameObjects->at(i)->set_Velocity(*Rect_1_Vel);
						}
					}

					/*
					///checking vertically      --> quite tricky
					if (Rect_1_Vel->get_y() * Rect_2_Vel->get_y() > 0)
					{
						if (abs(Rect_1_Vel->get_y()) <= abs(Rect_2_Vel->get_y()))       ///if the object vel is < moving platform vel
						{
							if ()       ///if the object collide above the moving platform
							{
								///set standing object pointer to the moving platform
							}
							else          ///object collide below the moving platform
							{

							}
						}

						//else (>)  ---> do nothing

						///if object vel > moving object vel --> it definite ly not gonna collide --> he object move faster
						///but with gravity (object is falling down)--> rect_1_vel may be < rect_2_vel like above ...
						///which will be pushed by moving object ,but with time ,the rect_1 vel will > rect_2_vel --> but it cannot ...
						///move faster any more cuz the object is pushing by the moving object ---> need to solve this bug later
						///in the code above --> this is like VA CHAM MEM in physic
					}
					else   //<= 0
					{
						if ()       ///if collide above
						{

						}
						else       ///if collide below --> day xuong voi 1 after vel = -vel before
						{

						}
					}
					*/
				}
			}

			delete Rect_1;
			delete Rect_2;
		}
	}
}