#pragma once
#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include"SDL_Mixer.h"
#include<string>
#include<map>
#include<iostream>

namespace HDT_engine
{
	namespace SOUND
	{
		enum AudioType
		{
			Sound_Music = 0,
			Sound_SFX = 1
		};

		class SoundManager									//singleton
		{
		public:
			bool Load(std::string FilePath, int AudioType, std::string AudioID);
			void PlayMusic(std::string MusicID,int numLoops);
			void PauseMusic();
			void ResumeMusic();
			void HaltMusic();
			void PlaySoundEffect(std::string SoundID,int numLoops);
			void Clean();

			static SoundManager* Instance();
		private:
			SoundManager();
			~SoundManager();

			static SoundManager* instance;

			std::map<std::string, Mix_Music*> m_musics;					  //MUSIC type
			std::map<std::string, Mix_Chunk*> m_soundEffects;             //SFX   type
		};
	}
}
#endif