#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Graph.h"
#include <cstdlib>
#include "string_processing.h"
#include <fstream>
#include <ctime>
#include <vector>
#include <cstring>
#include "game.h"
#include <SDL_mixer.h>
#include "sound.h"

using namespace std;

const int SCREEN_WIDTH = 572;
const int SCREEN_HEIGHT = 530;
const string WINDOW_TITLE = "HANG MAN";

int main(int argc, char* argv[])
{
	SDL_Window* window=nullptr;
    SDL_Renderer* renderer=nullptr;
    initSDL(window, renderer);
    
   	TTF_Init();		//Init True-Type-Font
   	//pre-load sound files
   	{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) 	//Init SDL_mixer
		{
			cout<<Mix_GetError();
		}
		Mix_Chunk*chunk = NULL;
		chunk = Mix_LoadWAV("sound/wrong.mp3");
		Mix_PlayChannel (-1,chunk,0);
		if (Mix_Playing(-1)==0) Mix_FreeChunk(chunk);
	}
	{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) 	//Init SDL_mixer
		{
			cout<<Mix_GetError();
		}
		Mix_Chunk*chunk = NULL;
		chunk = Mix_LoadWAV("sound/correct.mp3");
		Mix_PlayChannel (-1,chunk,0);
		if (Mix_Playing(-1)==0) Mix_FreeChunk(chunk);
	}
   	Mix_Volume(-1,0);		//we just want to load sound files, not play now	
   	gameIntro(window,renderer);  //render game intro
	waitUntilKeyPressed();
	SDL_RenderClear(renderer);
	mainMenu(window,renderer);  //render main menu 
	SDL_RenderPresent(renderer);
	Menu(window,renderer);  //game menu
}

