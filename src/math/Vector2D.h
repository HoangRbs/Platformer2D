#pragma once

#ifndef VECTOR2D_H
#define VECTOR2D_H

#include"math.h"
#include<iostream>

using namespace std;

namespace HDT_engine
{
	namespace Math
	{
		class Vector2D
		{
		public:
			Vector2D();
			Vector2D(float x,float y);
			void set_x(float x);
			void set_y(float y);
			float get_x();
			float get_y();
			float length();
			void normalize();

		private:
			float x;
			float y;

		public:
			Vector2D operator+(const Vector2D& right_vector);
			Vector2D operator+=(const Vector2D& right_vector);

			Vector2D operator-(const Vector2D& right_vector);
			Vector2D operator-=(const Vector2D& right_vector);

			Vector2D operator*(const float scalar);
			Vector2D operator*=(const float scalar);

			Vector2D operator/(const float scalar);
			Vector2D operator/=(const float scalar);

			friend ostream& operator << (ostream& m_console,Vector2D& right_vector);
		};

		
	}
}
#endif
