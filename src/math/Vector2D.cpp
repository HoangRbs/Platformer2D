#include"Vector2D.h"

namespace HDT_engine
{
	namespace Math
	{
		Vector2D::Vector2D()
		{
		}

		Vector2D::Vector2D(float x,float y)
		{
			this->x = x;
			this->y = y;
		}

		void Vector2D::set_x(float x)
		{
			this->x = x;
		}

		void Vector2D::set_y(float y)
		{
			this->y = y;
		}

		float Vector2D::get_x()
		{
			return x;
		}
		float Vector2D::get_y()
		{
			return y;
		}

		float Vector2D::length()
		{
			return sqrt(x*x + y*y);
		}

		void Vector2D::normalize()
		{
			float l = length();
			
			(*this) *= 1 / l;   //make use of *= overloaded operator!!!
		}

		Vector2D Vector2D::operator +(const Vector2D& right_vector)
		{
			return Vector2D(this->x + right_vector.x,
							this->y + right_vector.y);
		}
		Vector2D Vector2D::operator +=(const Vector2D& right_vector)
		{
			this->x += right_vector.x;
			this->y += right_vector.y;
			return *this;
		}

		Vector2D Vector2D::operator-(const Vector2D& right_vector)
		{
			return Vector2D(this->x - right_vector.x,
							this->y - right_vector.y);
		}
		Vector2D Vector2D::operator-=(const Vector2D& right_vector)
		{
			this->x -= right_vector.x;
			this->y -= right_vector.y;
			return *this;
		}

		Vector2D Vector2D::operator*(const float scalar)
		{
			return Vector2D(this->x * scalar,this->y * scalar);
		}
		Vector2D Vector2D::operator*=(const float scalar)
		{
			this->x *= scalar;
			this->y *= scalar;
			return *this;
		}

		Vector2D Vector2D::operator/(const float scalar)
		{
			return Vector2D(this->x /scalar, this->y/scalar);
		}
		Vector2D Vector2D::operator/=(const float scalar)
		{
			this->x /= scalar;
			this->y /= scalar;
			return *this;
		}

		ostream& operator << (ostream& m_console,Vector2D& right_vector)  //friend function of Vector2D
		{
			m_console << right_vector.x << " " << right_vector.y << " ";
			return m_console;
		}
	}
}
