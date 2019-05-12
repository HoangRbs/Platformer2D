#pragma once
#ifndef COLLISION_H
#define COLLISION_H

#include"SDL.h"

namespace HDT_engine
{
	namespace Game
	{
		
		static bool Rects_Collided(SDL_Rect* Rect_1, SDL_Rect* Rect_2)
		{
			if ((Rect_1->y + (Rect_1->h) ) < Rect_2->y)
				return false;
			if ((Rect_1->x + (Rect_1->w) ) < Rect_2->x)
				return false;
			if (Rect_1->x > (Rect_2->x + (Rect_2->w)))
				return false;
			if (Rect_1->y > (Rect_2->y + (Rect_2->h)))
				return false;

			return true;
		}
	}
}
#endif // ! COLLISION_H
