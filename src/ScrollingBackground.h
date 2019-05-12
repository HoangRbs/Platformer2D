#pragma once
#ifndef SCROLLINGBACKGROUND_H
#define SCROLLINGBACKGROUND_H

#include"PlatformerObject.h"
#include"BaseObjectCreator.h"

namespace HDT_engine
{
	namespace Game
	{
		class ScrollingBackground :public PlatformerObject
		{
		public:
			ScrollingBackground()
			{

			}
			~ScrollingBackground()
			{

			}

			virtual void draw();
			virtual void update();
			virtual void clean();
			virtual void load(unique_ptr<LoadParams>const &inputParams);
			virtual void LeverParserLoad();           ///this is used in Level Parser --> only if the load() above is done first --> which also means
													  ///all the Objects is parsed first the this function is done in the last

			virtual std::string Get_objectType()
			{
				return ("ScrollingBackground");
			}

			virtual void Set_scrollSpeed(int input_);       //is used in objectsLayer


			virtual void Set_scrollSpeedBUFFER(int input_)
			{
				//m_scrollSpeedBUFFER = input_;
			}

		private:
			enum BackGroundsRepeatIndex
			{
				LEFT= 0,
				RIGHT = 1
			};

			vector<Math::Vector2D> BackgroundsRepeat;
		};


		class ScrollingBackgroundCreator :public BaseObjectCreator
		{
		public:
			GameObject * createGameObject();

			ScrollingBackgroundCreator()
			{

			}
		private:
		};
	}
}
#endif