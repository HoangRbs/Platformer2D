#include"ShowFuckingEffect.h"
#include"graphic/TextureManager.h"
#include"game.h"

namespace HDT_engine
{
	namespace Game
	{
		void StartFuckingEffect(std::string FUCKING_TEXTURE_ID)
		{
			FuckingTextureID = FUCKING_TEXTURE_ID;
			FuckingEffectAlpha = 200;
		}

		void UpdateFuckingEffect()
		{
			if (FuckingEffectAlpha > 0)
			{
				FuckingEffectAlpha--;
			}
			else       ///<= 0  ----- reset
			{
				FuckingEffectAlpha = 0;
				FuckingTextureID = "";
			}
		}

		void DrawFuckingEffect()
		{
			Graphic::TextureManager::Instance()->drawFrame(FuckingTextureID,0,0,FuckingTextureFrameWidth,
																				FuckingTextureFrameHeight,
																				game::Instance()->Get_GameWidth(),
																				game::Instance()->Get_GameHeight(),
																				0,0,0,FuckingEffectAlpha);
		}
	}
}