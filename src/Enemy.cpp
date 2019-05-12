#include"Enemy.h"
#include"game.h"
#include"Camera.h"
#include"MoreEnemies/DeadYaranaicaManager.h"


namespace HDT_engine
{
	namespace Game
	{
		//Enemy class...
		Enemy::Enemy():PlatformerObject()
		{
			
		}

		Enemy::~Enemy()
		{

		}

		void Enemy::draw()
		{
			//no special draw here 
			if (!is_dead)
			{
				if (EnterScreen)
				{
					PlatformerObject::draw();
				}
			}
		}

		void Enemy::update()   //is in game update --> below game.handleEvent()
		{
			if (!is_dead)
			{
				if (!is_dying)
				{
					if (m_position.get_x() + m_screenWidth - Camera::Instance()->Get_OptimizeLagCamPos_x() < -320 ||
						m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x() > game::Instance()->Get_GameWidth() + 320 ||
						m_position.get_y() + m_screenHeight - Camera::Instance()->Get_OptimizeLagCamPos_y() < -320 ||
						m_position.get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y() > game::Instance()->Get_GameHeight() + 320)

					{
						EnterScreen = false;        //outside of the screen --> look at the specific enemy type 
													//to see how EnterScreen is used in its update() function
													//the purpose of EnterScreen is just to reduce the CPU when 
													//checking collision detection
					}

					PlatformerObject::update();   //standard Update
				}
				else
				{
					DoDyingAnimation();        //if dying == true --> do until Dead == true
				}
			}
		}

		void Enemy::clean()
		{
			PlatformerObject::clean();
		}

		void Enemy::load(unique_ptr<LoadParams>const& inputParams)
		{
			m_DyingTime = 130;
			m_DyingTimeCounter = 0;

			PlatformerObject::load(inputParams);

			scrollTime = 2;
			scrollTimeCounter = 0;

			if (m_position.get_x() - Camera::Instance()->Get_OptimizeLagCamPos_x() > game::Instance()->Get_GameWidth() + 320 || 
				m_position.get_x() + m_screenWidth - Camera::Instance()->Get_OptimizeLagCamPos_x() < -320 ||
				m_position.get_y() + m_screenHeight - Camera::Instance()->Get_OptimizeLagCamPos_y() < -320 ||
				m_position.get_y() - Camera::Instance()->Get_OptimizeLagCamPos_y() > game::Instance()->Get_GameHeight() + 320)
			{
				EnterScreen = false;
			}
			else
			{
				EnterScreen = true;
			}
		}

		std::string Enemy::Get_objectType()          //is also used as ID in gameObjectCreators map in gameObjectFactory
		{
			return ("Enemy");
		}

		void Enemy::collision()
		{
			m_Health--;

			if (m_Health == 0)
			{
				SOUND::SoundManager::Instance()->PlaySoundEffect("EXPLOSION", 0);

				//set dying to true --> prevent checking collision again too
				is_dying = true;

				//texture changed --> Frames changes
				
				m_currentRow = 0;
				
				if (m_textureID == "PINKRANGER")
				{
					DeadYaranaicaManager::Instance()->YaranaicaAdd(m_position.get_x(),m_position.get_y(),m_screenWidth ,m_screenHeight ,"DEADYARANAICA_PINKRANGER",
																   45,70,1,800);
				}

				if (m_textureID == "AGENT")
				{
					DeadYaranaicaManager::Instance()->YaranaicaAdd(m_position.get_x(), m_position.get_y(), m_screenWidth, m_screenHeight , "DEADYARANAICA_GENERAL",
																   60, 46, 1, 800);
				}

				if (m_textureID == "NARUTO")
				{
					DeadYaranaicaManager::Instance()->YaranaicaAdd(m_position.get_x(), m_position.get_y(), m_screenWidth , m_screenHeight , "DEADYARANAICA_NARUTO",
						40, 64, 1, 800);
				}

				if (m_textureID == "SASUKE")
				{
					DeadYaranaicaManager::Instance()->YaranaicaAdd(m_position.get_x(), m_position.get_y(), m_screenWidth , m_screenHeight , "DEADYARANAICA_SASUKE",
						41, 75, 1, 800);
				}

				if (m_textureID == "SOLDIER")
				{
					DeadYaranaicaManager::Instance()->YaranaicaAdd(m_position.get_x(), m_position.get_y(), m_screenWidth, m_screenHeight , "DEADYARANAICA_GENERAL",
						60, 46, 1, 800);
				}

				if (m_textureID == "SPIDERMAN")
				{
					DeadYaranaicaManager::Instance()->YaranaicaAdd(m_position.get_x(), m_position.get_y(), m_screenWidth , m_screenHeight , "DEADYARANAICA_SPIDERMAN",
						55, 101, 1, 800);
				}
			}
		}

		void Enemy::DoDyingAnimation()
		{
			//enemy dies only one time --> when it dies --> it is dead
			m_currentColumn = (SDL_GetTicks()/(1000/10)) % m_DyingNumFrames;
			
			if (m_DyingTimeCounter == m_DyingTime)
			{
				is_dead = true;
				m_DyingTimeCounter = 0; 
			}

			m_DyingTimeCounter++;
		}

		void Enemy::Detect_Player()
		{
			if (ThePlayer != NULL)
			{
				
				int RightDetectRange = m_position.get_x() + DetectPlayerRange;
				int LeftDetectRange = m_position.get_x() - DetectPlayerRange;

				LeftDetect = false;
				RightDetect = false;

				if (ThePlayer->Get_Position().get_x() >= LeftDetectRange && ThePlayer->Get_Position().get_x() <= m_position.get_x())
				{
					///CUNG PHUONG :)))
					if (ThePlayer->Get_Position().get_y() + ThePlayer->Get_ScreenHeight() >= m_position.get_y() - 5 &&
						ThePlayer->Get_Position().get_y() + 20 <= m_position.get_y() + m_screenHeight + 5)
					{
						if (goingLeft)
						{
							LeftDetect = true;
						}
					}
				}
				else if (ThePlayer->Get_Position().get_x() >= m_position.get_x() && ThePlayer->Get_Position().get_x() <= RightDetectRange)
				{
					///CUNG PHUONG :)))
					if (ThePlayer->Get_Position().get_y() + ThePlayer->Get_ScreenHeight() >= m_position.get_y() - 5 &&
						ThePlayer->Get_Position().get_y() + 20 <= m_position.get_y() + m_screenHeight + 5)
					{
						if(goingRight)
							RightDetect = true;
					}
				}
				
			}
		}
		//....
	}
}