#pragma once
#ifndef BULLET_H
#define BULLET_H

#include"PlatformerObject.h"
#include"Camera.h"
#include"game.h"

namespace HDT_engine
{
	namespace Game
	{
		class PlayerBullet: public PlatformerObject
		{
		public:
			PlayerBullet():PlatformerObject()             //all the info of the bullet needs to be inited too through constructor
			{
				//EnterScreen = false;
			}

			virtual ~PlayerBullet()
			{

			}

			virtual void draw()
			{
				PlatformerObject::draw();
			}

			virtual void update()
			{
				
				//ENTESCREEN OF BULLET IS SET IN BULLETHANDLER
				//FALSE IS SET IN PLATFORMER OBJECT

				PlatformerObject::update();
			}

			virtual void clean()
			{

				PlatformerObject::clean();
			}

			virtual void load(unique_ptr<LoadParams> const& inputParams)
			{
				PlatformerObject::load(inputParams);

				//special load for bullet object
				//m_velocity.set_x(inputParams->get_BulletVel().get_x()); //already did this inside ShooterObject::load()
				//m_velocity.set_y(inputParams->get_BulletVel().get_y());
			}

			virtual std::string Get_objectType()
			{
				return ("PlayerBullet");
			}

			virtual void collision()
			{
				is_dead = true;            //Bullet Handler will take care of this and delete it
			}

			void set_EnterScreen(bool input)
			{
				EnterScreen = input;
			}

		private:
			
		};

		class EnemyBullet: public PlayerBullet            //Enemy bullet is just a Player bullet with different type
		{
		public:
			EnemyBullet():PlayerBullet()
			{

			}

			~EnemyBullet()
			{

			}

			virtual std::string Get_objectType()
			{
				return ("EnemyBullet");
			}

		private:
		};
	}
}
#endif