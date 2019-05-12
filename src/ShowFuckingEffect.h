#pragma once
#include<string>

#ifndef SHOWFUCKINGEFFECT_H
#define SHOWFUCKINGEFFECT_H

namespace HDT_engine
{
	namespace Game
	{
		static int FuckingEffectAlpha = 0;
		static std::string FuckingTextureID = "";
		static const int FuckingTextureFrameWidth = 640;
		static const int FuckingTextureFrameHeight = 360;

		void StartFuckingEffect(std::string FUCKING_TEXTURE_ID);       ///is used in  ClosedAttackEnemy::checkPlayerAttack()
		void UpdateFuckingEffect();         ///is used in PlayState Update
		void DrawFuckingEffect();		   ///is used in PlayState Draw
	}
}

#endif
