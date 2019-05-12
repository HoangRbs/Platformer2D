#include"GameObject.h"

namespace HDT_engine
{
	namespace Game
	{
		GameObject::GameObject() :             //MUST init all these --> to compatible with all kind GameObject
			is_withinscreen(true),
			is_dead(false),
			is_dying(false),
			EnterScreen(false),
			m_position(0,0),				
			m_velocity(0,0),				  //if don't do this --> the MenuButton will move 
			m_acceleration(0,0),			  //same with all the below value --> you get the ideas
			m_screenWidth(0),
			m_screenHeight(0),
			m_currentRow(0),
			m_currentColumn(0),
			m_numFrames(1),
			animSpeed(800),                  //default for all Objects --> never set to 0 --> devide by zero!!!
			m_FrameWidth(0),
			m_FrameHeight(0),
			m_angle(0),
			m_alpha(255),
			m_callBackID(0),
			m_callBack(NULL),
			m_scrollSpeed(0),
			m_DyingFrameWidth(0),
			m_DyingFrameHeight(0),
			m_DyingNumFrames(1)         //numFrames always begin at 1
		{

		}

		GameObject::~GameObject()
		{

		}

		Math::Vector2D& GameObject::Get_Position()
		{
			return m_position;
		}

		int& GameObject::Get_ScreenWidth()
		{
			return m_screenWidth;
		}

		int& GameObject::Get_ScreenHeight()
		{
			return m_screenHeight;
		}

		void GameObject::Scroll(int scrollVelocity_)
		{
			if(Get_objectType() != std::string("Player"))        //Player never scroll
				m_position.set_x(m_position.get_x() + scrollVelocity_); 
		}

		bool GameObject::isWithinScreen()
		{
			return is_withinscreen;
		}

		void GameObject::Set_isWithinScreen(bool is_withinscreen_)
		{
			this->is_withinscreen = is_withinscreen_;
		}

		bool GameObject::isDead()
		{
			return is_dead;
		}

		bool GameObject::isDying()
		{
			return is_dying;
		}

		bool GameObject::isEnterScreen()
		{
			return EnterScreen;
		}

		Math::Vector2D& GameObject::Get_position()
		{
			return m_position;
		}
	}
}