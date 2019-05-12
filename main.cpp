#include<cstdlib>
#include<time.h>

#include"src/level/AnimatedTiles.h"
#include"src/graphic/window.h"
#include"src/game.h"
#include"src/sound/SoundManager.h"

#undef main
using namespace std;
using namespace HDT_engine;

int DelayTime = 1000.0f / FPS;
Uint32 framestart = 0;
Uint32 frametime = 0;

int main()
{
	srand(time(0));

	cout << "EV ENGINE DEMO" << endl;
	cout << "IT'S NOT REALLY A BIRD, JUST A FUCKING CAT" << endl;
	cout << "CREATOR : MINH HOANG" << endl;
	cout << "CREATOR : DOB : 17/06/1999" << endl;
	cout << "CREATOR : DEMO TEST DAY : 3/JULY/2018" << endl << endl << endl;
	
	cout << "<---------------------ALL THE CREDIT--------------------->" << endl << endl;
	cout << " ---- MAGIC CLIFFS ENVIRONMENT (cut used in background) ----" << " https://ansimuz.itch.io/magic-cliffs-environment " << endl;
	cout << " ---- WILLS PIXEL EXPLOSION SAMPLE ---- : "<<" https://untiedgames.itch.io/five-free-pixel-explosions "<< endl;
	cout << " ---- PIXEL PLATFORMER ASSETS ---- : " << " https://pixelprogrammer.itch.io/pixel-platformer-art-pack " << endl;
	cout << " ---- 32x32 DUNGEON PACK ---- : " << " https://alexs-assets.itch.io/32x32-dungeon-pack " << endl;
	cout << " ---- HILLS SIMPLE PACK ---- : " << " https://allfenom.itch.io/hills-simple-pack " << endl;
	cout << " ---- ANIMATING WATERFALL TILESET ---- : " << " https://opengameart.org/content/lpc-animated-water-and-waterfalls " << endl;
	cout << " ---- WIND BACKGROUND MUSIC ---- : " << " https://freesound.org/people/InspectorJ/sounds/405561/ " << endl;
	cout << " ---- 8 BIT BACKGROUND MUSIC ---- : " << " https://freesound.org/people/Volvion/sounds/265308/ " << endl;
	cout << " ---- BIRD WHISTLING BACKGROUND MUSIC ---- : " << " https://freesound.org/people/InspectorJ/sounds/339326/ " << endl;
	cout << " ---- HURT DUDE SOUND ---- : " << " https://freesound.org/people/ecfike/sounds/154554/ " << endl;
	cout << " ---- SCREAM HIGH SOUND (edited with audacity for higher voice)---- : " << " https://freesound.org/people/Adam_N/sounds/166154/ " << endl;
	cout << " ---- WHAT THE FUCK SOUND ---- : " << " https://freesound.org/people/Magic-Cap/sounds/412869/ " << endl;
	cout << endl << "<------------------------------------------------------------------->" << endl << endl;


	HDT_engine::Game::game::Instance()->Init();              //every thing need to be Init is all in the game bitches
	
	while (!HDT_engine::Game::game::Instance()->close())     
	{
									    
		framestart = SDL_GetTicks();

		HDT_engine::Game::game::Instance()->handleEvents();

		HDT_engine::Game::game::Instance()->update();
										       
		HDT_engine::Game::game::Instance()->render();	
		

		frametime = SDL_GetTicks() - framestart;

		///cout << frametime << endl;

		if (frametime < DelayTime)
		{
			SDL_Delay(int(DelayTime - frametime));
		}

		LEVEL::AnimatedTiles::Instance()->set_DoneOneFrameToPlusCounterForAll();
	}
	return 0;
}

//hoang branch test
