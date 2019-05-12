#include"SoundManager.h"
namespace HDT_engine
{
	namespace SOUND
	{
		SoundManager* SoundManager::instance = NULL;            //static variable definition

		SoundManager::SoundManager()                            //init sound system
		{
			Mix_OpenAudio(44100,AUDIO_S16,1,4096);
		}

		SoundManager::~SoundManager()
		{
			Clean();
			Mix_CloseAudio();
		}

		SoundManager* SoundManager::Instance()
		{
			if (instance == NULL)
			{
				instance = new SoundManager();   //cuz private variable(static) can use private constructor
				return instance;
			}

			return instance;
		}

		bool SoundManager::Load(std::string FilePath,int AudioType_,std::string AudioID)
		{
			if (AudioType_ == AudioType::Sound_Music)			//load long music
			{
				Mix_Music* tempMusic = Mix_LoadMUS(FilePath.c_str());
				if (tempMusic == NULL)
				{
					std::cout << Mix_GetError() << " _at_ : "<<FilePath<<std::endl;
					return false;
				}
				m_musics[AudioID] = tempMusic;
				return true;
			}
			else if (AudioType_ == AudioType::Sound_SFX)      //load soun effect
			{
				Mix_Chunk* tempSFX = Mix_LoadWAV(FilePath.c_str());
				if (tempSFX == NULL)
				{
					std::cout << Mix_GetError() << " _at_ : " << FilePath << std::endl;
					return false;
				}
				m_soundEffects[AudioID] = tempSFX;
				return true;
			}

			return false;         //if there is no matched Audio type like the two above
		}

		void SoundManager::PlayMusic(std::string MusicID,int numLoops)
		{
			Mix_PlayMusic(m_musics[MusicID], numLoops);
		}

		void SoundManager::PlaySoundEffect(std::string SoundID, int numLoops)
		{
			Mix_PlayChannel(-1,m_soundEffects[SoundID],numLoops);
		}

		void SoundManager::Clean()
		{
			for (auto i = m_musics.begin() ; i != m_musics.end() ; i++)
			{
				Mix_FreeMusic(i->second);
			}

			for (auto i = m_soundEffects.begin() ; i != m_soundEffects.end() ; i++)
			{
				Mix_FreeChunk(i->second);
			}

			delete instance;        ///after doing this --> the memory of sound instance is gone
			///do nothing under this statement
		}

		void SoundManager::PauseMusic()
		{
			Mix_PausedMusic();
		}

		void SoundManager::ResumeMusic()
		{
			Mix_ResumeMusic();
		}

		void SoundManager::HaltMusic()
		{
			Mix_HaltMusic();
		}
	}
}