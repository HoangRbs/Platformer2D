#pragma once
#ifndef TURRETCREATOR_H
#define TURRETCREATOR_H

#include"BaseObjectCreator.h"
#include"Turret.h"

namespace HDT_engine
{
	namespace Game
	{
		class TurretCreator: public BaseObjectCreator
		{
		public:
			GameObject * createGameObject()
			{
				return new Turret();
			}

			TurretCreator()
			{

			}
		private:
		};
	}
}
#endif