#pragma once
#include<iostream>
#include"Math/Vector2D.h"
using namespace std;

#ifndef LOADPARAMS_H
#define LOADPARAMS_H

namespace HDT_engine
{
	namespace Game
	{
		//this is the place having all the info that need to be PARSED
		class LoadParams  
		{

		public:
			LoadParams(int x_, int y_, int screenWidth_, int screenHeight_, string textureID_, 
					   int FrameWidth_, int FrameHeight_, int numFrames_, int animSpeed_,float scrollSpeed_,
					   string DyingTextureID_,int DyingFrameWidth_,int DyingFrameHeight_,int DyingNumFrames_,
					   int callBackID = 0, Math::Vector2D BulletVel_ = Math::Vector2D(0,0),
					   Math::Vector2D BulletAcc_ = Math::Vector2D(0, 0), 
				       bool PlayerCanControlBackground_ = false)  //there is a default parameter
			: x(x_), y(y_), 
			  screenWidth(screenWidth_), 
			  screenHeight(screenHeight_), 
			  textureID(textureID_),
			  m_FrameWidth(FrameWidth_),
			  m_FrameHeight(FrameHeight_),
			  m_callBackID(callBackID),
			  m_numFrames(numFrames_),
			  m_animSpeed(animSpeed_),
			  m_BulletVel(BulletVel_),              //the BulletVel is only used for bullet object
			  m_BulletAcc(BulletAcc_),
			  m_scrollSpeed(scrollSpeed_),           //right now is only used for ScrollingBackground object
			  m_DyingTextureID(DyingTextureID_),
			  m_DyingFrameWidth(DyingFrameWidth_),
			  m_DyingFrameHeight(DyingFrameHeight_),
			  m_DyingNumFrames(DyingNumFrames_)
			{

			}

			int get_x();
			int get_y();
			int get_screenWidth();
			int get_screenHeight();
			int get_FrameWidth();
			int get_FrameHeight();
			int get_m_callbackID();
			int get_numFrames();
			int get_animSpeed();
			float get_scrollSpeed();
			int get_DyingFrameWidth();
			int get_DyingFrameHeight();
			int get_DyingNumFrames();
			Math::Vector2D get_BulletVel();
			Math::Vector2D get_BulletAcc();

			string get_textureID();
			string get_DyingTextureID();

		private:
			int x; int y;
			int screenWidth; 
			int screenHeight;
			string textureID;
			int m_FrameWidth; 
			int m_FrameHeight;
			int m_callBackID;
			int m_numFrames;
			int m_animSpeed;
			Math::Vector2D m_BulletVel;
			Math::Vector2D m_BulletAcc;
			float m_scrollSpeed;

			string m_DyingTextureID;
			int m_DyingFrameWidth;
			int m_DyingFrameHeight;
			int m_DyingNumFrames;
		};


	}
}

#endif