#include"LoadParams.h"
namespace HDT_engine
{
	namespace Game
	{
		//LoadParams class
		int LoadParams::get_x()
		{
			return x;
		}

		int LoadParams::get_y()
		{
			return y;
		}

		int LoadParams::get_screenWidth()
		{
			return screenWidth;
		}

		int LoadParams::get_screenHeight()
		{
			return screenHeight;
		}

		int LoadParams::get_FrameWidth()
		{
			return m_FrameWidth;
		}

		int LoadParams::get_FrameHeight()
		{
			return m_FrameHeight;
		}
		
		int LoadParams::get_m_callbackID()
		{
			return m_callBackID;
		}

		string LoadParams::get_textureID()
		{
			return textureID;
		}

		int LoadParams::get_numFrames()
		{
			return m_numFrames;
		}

		int LoadParams::get_animSpeed()
		{
			return m_animSpeed;
		}
		
		float LoadParams::get_scrollSpeed()
		{
			return m_scrollSpeed;
		}

		Math::Vector2D LoadParams::get_BulletVel()
		{
			return m_BulletVel;
		}

		Math::Vector2D LoadParams::get_BulletAcc()
		{
			return m_BulletAcc;
		}

		string LoadParams::get_DyingTextureID()
		{
			return m_DyingTextureID;
		}

		int LoadParams::get_DyingFrameWidth()
		{
			return m_DyingFrameWidth;
		}

		int LoadParams::get_DyingFrameHeight()
		{
			return m_DyingFrameHeight;
		}

		int LoadParams::get_DyingNumFrames()
		{
			return m_DyingNumFrames;
		}
	}
}