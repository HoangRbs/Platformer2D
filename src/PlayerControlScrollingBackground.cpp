#include"PlayerControlScrollingBackground.h"

namespace HDT_engine
{
	namespace Game
	{
		PlayerControlScrollingBackground* PlayerControlScrollingBackground::instance = NULL;

		PlayerControlScrollingBackground* PlayerControlScrollingBackground::Instance()
		{
			if (instance == NULL)
			{
				instance = new PlayerControlScrollingBackground();
			}

			return instance;
		}

		void PlayerControlScrollingBackground::set_PlayerVel(Math::Vector2D PlayerVel_)
		{
			PlayerVel = PlayerVel_;
		}

		void PlayerControlScrollingBackground::set_PlayerPos(Math::Vector2D PlayerPos_)
		{
			PlayerPos = PlayerPos_;
		}

		void PlayerControlScrollingBackground::set_PlayerStandingOnPlatform(GameObject* StandingOnPlatform_)
		{
			StandingOnPlatform = StandingOnPlatform_;
		}
	}
}