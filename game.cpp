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
#include "sound.h"
#include <SDL_mixer.h>

using namespace std;

const int SCREEN_WIDTH = 572;
const int SCREEN_HEIGHT = 530;
const string WINDOW_TITLE = "HANGMAN";

int playGame(SDL_Window* &window, SDL_Renderer* &renderer,int& totalScore)				
{
	srand(time(NULL));
   	int countBad=0,i,t,j;
   	int addScore=0;
   	drawKeyboard(window,renderer);			//draw game's background
   	drawBackground(window,renderer);		//draw game's virtual keyboard
    SDL_RenderPresent(renderer);
    string randWord;
    randWord=chooseWord();	//get a random word from the list
   	int n=randWord.length();
  	char*guessWord=new char[n];
  	char*s2=new char[n];
   	for (int i=0;i<n+1;i++)				
   	{
   		s2[i]=randWord[i];
	}
	for ( i=0;i<n;++i) guessWord[i]='-';
	guessWord[n]=0;  //to make sure that no "weird" character would appear in the game
	char guessLetter;
	int a =countBad;      //line 40-45: check if player make any wrong guesses
	int b;
	do
	{	
		b=a;         
		*&a=countBad;
		char*charTotalScore=new char[n];
		itoa(totalScore,charTotalScore,10);   //convert total score from int to char array
	    drawBackground(window,renderer);		//gallow lower animation
	   	if (countBad==8)						//when player lost the game
		{
			TTF_Font*font=TTF_OpenFont("font/calibri.ttf",28);  //display the random word
			SDL_Color color={0,0,0,255};
			SDL_Surface*textSurface=TTF_RenderText_Solid(font,s2,color);
			SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
			SDL_Rect textRect;
			textRect.x=572/2-8*(n-1);  //center words
			textRect.y=0;
			SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
			SDL_RenderCopy(renderer,text,NULL,&textRect);
			SDL_RenderPresent(renderer);
			SDL_FreeSurface(textSurface);
			SDL_DestroyTexture(text);
			TTF_CloseFont(font);
			SDL_Delay(450);
   			gameOver(window,renderer,totalScore);
   			SDL_DestroyRenderer(renderer);
		} 
	    if (a==b) 
		{
			drawHangman(window,renderer,countBad); //usisng drawHangman instead of drawHangmanAnimation to prevent re-draw hangman if there's no wrong guess
			SDL_RenderPresent(renderer);
		}
		if (a!=b||(a==0&&b==b))
		{
			drawHangmanAnimation(window,renderer,countBad);  //gallow lower animation
		}
		{
			TTF_Font*font=TTF_OpenFont("font/calibri.ttf",27);  //display the player's total score;
			SDL_Color color={170,0,4,255};
			SDL_Surface*textSurface=TTF_RenderText_Solid(font,charTotalScore,color);
			SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
			SDL_Rect textRect;
			textRect.x=61;  
			textRect.y=16;
			SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
			SDL_RenderCopy(renderer,text,NULL,&textRect);
			SDL_RenderPresent(renderer);
			SDL_FreeSurface(textSurface);
			SDL_DestroyTexture(text);
			TTF_CloseFont(font);
		}
		{
		TTF_Font*font=TTF_OpenFont("font/calibri.ttf",28);  //display the hidden word
		SDL_Color color={0,0,0,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,guessWord,color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=572/2-8*(n-1);  //center words
		textRect.y=0;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_RenderPresent(renderer);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(text);
		TTF_CloseFont(font);
		}
		guessLetter=chooseLetter(window,renderer,totalScore);  //guess a letter of the random word
		if (guessLetter=='0')	//see function: string_processing.cpp/char chooseLetter(SDL_Window* &window, SDL_Renderer* &renderer) for details
		{	
			SDL_Delay(1);					//player choose to exit to main menu
			mainMenu(window,renderer);
			SDL_RenderPresent(renderer);
			Menu(window,renderer);
		}
		else
		{
			if (guessLetter=='1') //see function: string_processing.cpp/char chooseLetter(SDL_Window* &window, SDL_Renderer* &renderer) for details
			{					//player choose to resume game
				drawKeyboard(window,renderer);
			}
			Update(window,renderer,randWord,guessWord,guessLetter,countBad,addScore);
			if (strcmp(guessWord,s2)==0)  //when player've guessed the hidden word
			{
				drawBackground(window,renderer);
				drawHangman(window,renderer,countBad);
				TTF_Font*font=TTF_OpenFont("font/calibri.ttf",28);  //display the hidden word
				SDL_Color color={0,0,0,255};
				SDL_Surface*textSurface=TTF_RenderText_Solid(font,s2,color);
				SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
				SDL_Rect textRect;
				textRect.x=572/2-8*(n-1);  //center words
				textRect.y=0;
				SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
				SDL_RenderCopy(renderer,text,NULL,&textRect);
				SDL_RenderPresent(renderer);	
				SDL_FreeSurface(textSurface);
				SDL_DestroyTexture(text);
				TTF_CloseFont(font);	
				SDL_Delay(250);					//pause the game for a while  to display the random word
				break;
			}
		}
	} 
	while (true);
	delete [] s2;
	delete [] guessWord;
	return addScore; //return the  score player earned from the world
}

void Menu(SDL_Window* &window, SDL_Renderer* &renderer)
{
	int Ox,Oy,totalScore=0,a;
	SDL_Event e;
    while (true)
	{	
		while (SDL_PollEvent(&e))    
		{
			switch (e.type)
			{
				//LMB pressed
				case SDL_MOUSEBUTTONDOWN:
				{
					if (e.button.button == SDL_BUTTON_LEFT)	//get mouse position when LMB clicked
					{
						SDL_GetMouseState(&Ox,&Oy);
						break;
					}
				}
			}
		}
		SDL_Delay(1);
		if (361<Ox && Ox<(361+ 29) && 213< Oy && Oy<(213+101)) //choose to quit game
        {
			quitSDL(window,renderer);
		}
		if (109<Ox && Ox<(109+ 27) && 213< Oy && Oy<(213+102)) //choose to play game
        {	
        	a=playGame(window,renderer,totalScore);   //continuously add scores to player's total score
        	totalScore+=a;
		} 
		if (232<Ox && Ox<(232+ 36) && 213< Oy && Oy<(213+101)) //choose to see the best score
		{	
			showBestScore(window,renderer);
		}
	} 
}
