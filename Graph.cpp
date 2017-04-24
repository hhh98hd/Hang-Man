#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Graph.h"
#include <cstdlib>
#include "game.h"
#include <cstring>
#include <fstream>
#include "string_processing.h"
#include "sound.h"
#include <SDL_mixer.h>

using namespace std;

const int SCREEN_WIDTH = 572;
const int SCREEN_HEIGHT = 530;
const string WINDOW_TITLE = "HANGMAN";

void showBestScore(SDL_Window* &window, SDL_Renderer* &renderer)
{
	int n1,n2,i;				
	ifstream file;
	file.open("data/best_score.txt");
	string playerName;
	int playerScore;
	if (file.is_open())
	{
		getline(file,playerName);				//Load the best player's name
		file>>playerScore;						//Load the best score
	}
	else
	{
		cout<<"Unable to open file!"<<endl;
	}
	char*Name=new char[99];
	char*Score=new char[99];
	n1=playerName.length();
	itoa(playerScore,Score,10);
	n2=strlen(Score);
	for (i=0;i<n1;++i)				//convert from string to char array
	{
		Name[i]=playerName[i];
	}
	Name[n1]=0;
	
	SDL_Rect position;				//Display the background
	position.x=0;
	position.y=0;
	position.w=572;
	position.h=530;
	SDL_Texture*texture=NULL;                                   
	SDL_Surface*surface=IMG_Load("image/bestscore.png");   
	texture=SDL_CreateTextureFromSurface(renderer,surface);
	SDL_RenderCopy(renderer,texture,NULL,&position);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	{
		TTF_Font*font=TTF_OpenFont("font/gabriola.ttf",72);  						//Display the besr player'sname
		SDL_Color color={140,0,7,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,Name,color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=572/2-15*(n1-1);										//center char
		textRect.y=230;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
		TTF_CloseFont(font);
	}
	{
		TTF_Font*font=TTF_OpenFont("font/arial.ttf",48);  						//Display the besr player'score
		SDL_Color color={140,0,7,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,Score,color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=572/2-20*(n2-1);									//center char
		textRect.y=330;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
		TTF_CloseFont(font);
	}
	SDL_RenderPresent(renderer);
	int Ox,Oy;
	SDL_Event ev;
   	while (true)
	{
		while (SDL_PollEvent(&ev))    
		{
			switch (ev.type)
			{
				case SDL_MOUSEBUTTONDOWN:  //LMB pressed
				{
					if (ev.button.button == SDL_BUTTON_LEFT)	//Get mouse position when LMB clicked
					{
						SDL_GetMouseState(&Ox,&Oy);
						break;
					}
				}
			}
		}
		if (532<Ox && Ox<(532+ 40) && 0< Oy && Oy<(0+40))	//Exit to main menu
		{
			SDL_Rect position;
			position.x=532;
			position.y=0;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/pause_clicked.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			SDL_RenderPresent(renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			SDL_Delay(175);
			mainMenu(window,renderer);
			SDL_RenderPresent(renderer);
			Menu(window,renderer);
		}
	}
	delete [] Name;
	delete [] Score;
}

void gameOver(SDL_Window* &window, SDL_Renderer* &renderer,int totalScore)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) 	//Init SDL_mixer
	{
		cout<<Mix_GetError();
	}
	Mix_Chunk*chunk = NULL;
	chunk = Mix_LoadWAV("sound/shark_chew.mp3");
	SDL_Rect position;				//end game background
	position.x=0;
	position.y=0;
	position.w=572;
	position.h=530;
	SDL_Texture*texture=NULL;                                   
	SDL_Surface*surface=IMG_Load("image/endgamebk.png");   
	texture=SDL_CreateTextureFromSurface(renderer,surface);
	SDL_RenderCopy(renderer,texture,NULL,&position);
	SDL_RenderPresent(renderer);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	int i;
	for (i=530;i>=100;i-=2)					//shark mouth animation
	{
		SDL_Rect position;
		position.x=0;
		position.y=i;
		position.w=572;
		position.h=530;
		SDL_Texture*texture=NULL;                                   
		SDL_Surface*surface=IMG_Load("image/sharkmouth.jpg");   
		texture=SDL_CreateTextureFromSurface(renderer,surface);
		SDL_RenderCopy(renderer,texture,NULL,&position);
		SDL_RenderPresent(renderer);
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
		if (i==110) 
		{
			Mix_PlayChannel (-1,chunk,0);
		}
	}
	{
		char*charTotalScore=new char[10];
		itoa(totalScore,charTotalScore,10);   //convert total score from int to char array
		SDL_Rect position;				//end game background
		position.x=0;
		position.y=0;
		position.w=572;
		position.h=530;
		SDL_Texture*texture=NULL;                                   
		SDL_Surface*surface=IMG_Load("image/oops.png");   
		texture=SDL_CreateTextureFromSurface(renderer,surface);
		SDL_RenderCopy(renderer,texture,NULL,&position);
		SDL_RenderPresent(renderer);
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
		{
			TTF_Font*font=TTF_OpenFont("font/calibri.ttf",27);  //display the player's total score;
			SDL_Color color={140,0,7,255};
			SDL_Surface*textSurface=TTF_RenderText_Solid(font,charTotalScore,color);
			delete [] charTotalScore;
			SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
			SDL_Rect textRect;
			textRect.x=61;  
			textRect.y=16;
			SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
			SDL_RenderCopy(renderer,text,NULL,&textRect);
			SDL_RenderPresent(renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);		
		}
	}
	int playerScore;
	string xxx;  //we don't care the best player's name now
	ifstream file;
	file.open("data/best_score.txt");
	if (file.is_open())
	{
		getline(file,xxx);				//We don't care the best player's name now
		file>>playerScore;						//Load the best score
	}
	else
	{
		cout<<"Unable to open file!"<<endl;
	}
	file.close();
	char Letter;
	if (totalScore>playerScore) 		//if player break record
	{
		SDL_Delay(500);
		//playHighScoreSoundEffect();		//play sound if player break the score record
		{
			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) 	//Init SDL_mixer
			{
				cout<<Mix_GetError();
			}
			Mix_Chunk*chunk = NULL;
			chunk = Mix_LoadWAV("sound/achievement.mp3");
			Mix_PlayChannel (-1,chunk,0);
			if (Mix_Playing(-1)==0) Mix_FreeChunk(chunk);
		}

		SDL_Rect position;				//end game background
		position.x=110;
		position.y=330/2;
		position.w=352;
		position.h=232;
		SDL_Texture*texture=NULL;                                   
		SDL_Surface*surface=IMG_Load("image/entername.png");   
		texture=SDL_CreateTextureFromSurface(renderer,surface);
		SDL_RenderCopy(renderer,texture,NULL,&position);
		drawKeyboard(window,renderer);
		SDL_RenderPresent(renderer);
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
		char*Name=new char[99];
		int i=0;
		while (true)
		{
			//display input content 2 times to prevent overlapping
			SDL_Delay(1);
			Letter=chooseLetter1(window,renderer);
			if (Letter=='1'||Letter=='0')
			{
				if (Letter=='1')		//player choose to exit to main menu
				{
					ofstream file;							//write new best score and player's name to data file
					file.open("data/best_score.txt");
					if (file.is_open())
					{
						file<<Name<<endl;
						file<<totalScore<<endl;;
					}
					else cout<<"Unable to open file !"<<endl;
					file.close();
					mainMenu(window,renderer);			//exit to main menu after writing to data file
					SDL_RenderPresent(renderer);
					Menu(window,renderer);
				}
				if (Letter=='0')	//"backspace" the last character
				{
					Name[i-1]=0;
					i-=1;
					goto A;
				}
			}
			else
			{
				A:
				nameInput(window,renderer,Letter,Name,i);  //input player's name;
				if (Letter!='1'&&Letter!='0') 
				{
					i++;
				}
				int n=strlen(Name);
				{
					SDL_Rect position;				//end game background
					position.x=110;
					position.y=330/2;
					position.w=352;
					position.h=232;
					SDL_Texture*texture=NULL;                                   
					SDL_Surface*surface=IMG_Load("image/entername.png");   
					texture=SDL_CreateTextureFromSurface(renderer,surface);
					SDL_RenderCopy(renderer,texture,NULL,&position);
					drawKeyboard(window,renderer);
					SDL_FreeSurface(surface);
					SDL_DestroyTexture(texture);
				} 
				{
					int n=strlen(Name);
					TTF_Font*font=TTF_OpenFont("font/calibri.ttf",28);  
					SDL_Color color={0,0,0,255};
					SDL_Surface*textSurface=TTF_RenderText_Solid(font,Name,color);  //display input content
					SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
					SDL_Rect textRect;
					textRect.x=572/2-8*(n-1);  //center words
					textRect.y=235;
					SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
					SDL_RenderCopy(renderer,text,NULL,&textRect);
					SDL_RenderPresent(renderer);
					TTF_CloseFont(font);
				}
			}
		}
		delete [] Name;
	}
	else
	{
		TTF_Font*font=TTF_OpenFont("font/calibri.ttf",27);  //display the player's total score;
		SDL_Color color={140,0,7,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,"(Press any key to exit to main menu)",color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=80;  
		textRect.y=415;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_RenderPresent(renderer);
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
		TTF_CloseFont(font);
		//endgame music
		
		Mix_Music* music = NULL;
		music = Mix_LoadMUS("sound/end_game.mp3");
		Mix_Volume(-1,128);
		Mix_PlayMusic(music,-1);
		waitUntilKeyPressed();
		Mix_HaltMusic();
		Mix_FreeMusic(music);
		mainMenu(window,renderer);			//exit to main menu 
		SDL_RenderPresent(renderer);
		Menu(window,renderer);
	}
}

void drawHangman(SDL_Window* &window, SDL_Renderer* &renderer,int countBad)
{
	int y;
	if (countBad==0) y=103;
	if (countBad==1) y=113;
	if (countBad==2) y=123;
	if (countBad==3) y=133;
	if (countBad==4) y=143;
	if (countBad==5) y=153;
	if (countBad==6) y=163;
	if (countBad==7) y=172;
	SDL_Rect position;
	position.x=318;
	position.y=y;  
	position.w=97;
	position.h=157;
	SDL_Texture*texture=NULL;                                   
	SDL_Surface*surface=IMG_Load("image/hangman.png");
	texture=SDL_CreateTextureFromSurface(renderer,surface);
	SDL_RenderCopy(renderer,texture,NULL,&position);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void drawHangmanAnimation(SDL_Window* &window, SDL_Renderer* &renderer,int countBad)
{
	//gallow lowering animation
	if (countBad==0)   //wrong guess =0 (beginning)
	{
		SDL_Rect position;
		position.x=318;
		position.y=103;  
		position.w=97;
		position.h=157;
		SDL_Texture*texture=NULL;                                   
		SDL_Surface*surface=IMG_Load("image/hangman.png");
		texture=SDL_CreateTextureFromSurface(renderer,surface);
		SDL_RenderCopy(renderer,texture,NULL,&position);
		SDL_RenderPresent(renderer);
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);	
	}
	if (countBad==1) 
	{									//wrong guess=1
		for (int i=104;i<=113;i++)
		{
			SDL_Rect position;
			position.x=318;
			position.y=i;  
			position.w=97;
			position.h=157;
			SDL_Texture*texture=NULL;                                   //image_loading to position (x,y)
			SDL_Surface*surface=IMG_Load("image/hangman.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			SDL_RenderPresent(renderer);	
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
		}
	}
	if (countBad==2) 
	{								//wrong guess =2
		for (int i=113;i<=123;i++)
		{
			SDL_Rect position;
			position.x=318;
			position.y=i;  
			position.w=97;
			position.h=157;
			SDL_Texture*texture=NULL;                                   //image_loading to position (x,y)
			SDL_Surface*surface=IMG_Load("image/hangman.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			SDL_RenderPresent(renderer);	
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
		}
	}
	if (countBad==3) 
	{
		for (int i=123;i<=133;i++)
		{
			SDL_Rect position;
			position.x=318;
			position.y=i; 
			position.w=97;
			position.h=157;
			SDL_Texture*texture=NULL;                                   //image_loading to position (x,y)
			SDL_Surface*surface=IMG_Load("image/hangman.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			SDL_RenderPresent(renderer);	
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
		}
	}
	if (countBad==4) 
	{
		for (int i=133;i<=143;i++)
		{
			SDL_Rect position;
			position.x=318;
			position.y=i;  
			position.w=97;
			position.h=157;
			SDL_Texture*texture=NULL;                                   //image_loading to position (x,y)
			SDL_Surface*surface=IMG_Load("image/hangman.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			SDL_RenderPresent(renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);	
		}
	}
	if (countBad==5) 
	{
		for (int i=143;i<=153;i++)
		{
			SDL_Rect position;
			position.x=318;
			position.y=i; 
			position.w=97;
			position.h=157;
			SDL_Texture*texture=NULL;                                   //image_loading to position (x,y)
			SDL_Surface*surface=IMG_Load("image/hangman.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			SDL_RenderPresent(renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);	
		}
	}
	if (countBad==6) 
	{
		for (int i=153;i<=163;i++)
		{
			SDL_Rect position;
			position.x=318;
			position.y=i;  
			position.w=97;
			position.h=157;
			SDL_Texture*texture=NULL;                                   //image_loading to position (x,y)
			SDL_Surface*surface=IMG_Load("image/hangman.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			SDL_RenderPresent(renderer);	
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
		}
	}
	if (countBad==7) 
	{
		for (int i=163;i<=172;i++)
		{
			SDL_Rect position;
			position.x=318;
			position.y=i; 
			position.w=97;
			position.h=157;
			SDL_Texture*texture=NULL;                                   //image_loading to position (x,y)
			SDL_Surface*surface=IMG_Load("image/hangman.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			SDL_RenderPresent(renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
		}
	}
}
void changeColor_Correct(SDL_Window* &window, SDL_Renderer* &renderer,char guessLetter)   //keyboard's color changes to GREEN when choose correct letter
{
	switch (guessLetter)
	{
		case 'q':		//Q
		{
			SDL_Rect position;
			position.x=15;
			position.y=340;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/correct.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'w':		//W
		{
			SDL_Rect position;
			position.x=70;
			position.y=340;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/correct.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'e':		//E
		{
			SDL_Rect position;
			position.x=125;
			position.y=340;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/correct.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'r':		//R
		{
			SDL_Rect position;
			position.x=180;
			position.y=340;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/correct.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 't':		//T
		{
			SDL_Rect position;
			position.x=235;
			position.y=340;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/correct.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'y':		//Y
		{
			SDL_Rect position;
			position.x=290;
			position.y=340;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/correct.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'u':		//U
		{
			SDL_Rect position;
			position.x=345;
			position.y=340;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/correct.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'i':		//i
		{
			SDL_Rect position;
			position.x=400;
			position.y=340;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/correct.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'o':		//O
		{
			SDL_Rect position;
			position.x=455;
			position.y=340;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/correct.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'p':		//P
		{
			SDL_Rect position;
			position.x=510;
			position.y=340;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/correct.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'a':		//A
		{
			SDL_Rect position;
			position.x=35;
			position.y=395;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/correct.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 's':		//S
		{
			SDL_Rect position;
			position.x=90;
			position.y=395;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/correct.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'd':		//D
		{
			SDL_Rect position;
			position.x=145;
			position.y=395;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/correct.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'f':		//F
		{
			SDL_Rect position;
			position.x=200;
			position.y=395;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/correct.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'g':		//G
		{
			SDL_Rect position;
			position.x=255;
			position.y=395;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/correct.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'h':		//H
		{
			SDL_Rect position;
			position.x=310;
			position.y=395;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/correct.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'j':		//J
		{
			SDL_Rect position;
			position.x=365;
			position.y=395;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/correct.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'k':		//K
		{
			SDL_Rect position;
			position.x=420;
			position.y=395;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/correct.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'l':		//L
		{
			SDL_Rect position;
			position.x=475;
			position.y=395;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/correct.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'z':		//Z
		{
			SDL_Rect position;
			position.x=90;
			position.y=450;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/correct.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'x':		//X
		{
			SDL_Rect position;
			position.x=145;
			position.y=450;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/correct.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'c':		//C
		{
			SDL_Rect position;
			position.x=200;
			position.y=450;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/correct.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'v':		//V
		{
			SDL_Rect position;
			position.x=255;
			position.y=450;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/correct.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'b':		//B
		{
			SDL_Rect position;
			position.x=310;
			position.y=450;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/correct.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'n':		//N
		{
			SDL_Rect position;
			position.x=365;
			position.y=450;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/correct.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'm':		//M
		{
			SDL_Rect position;
			position.x=420;
			position.y=450;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/correct.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
	}
	SDL_RenderPresent(renderer);
}
void changeColor_Wrong(SDL_Window* &window, SDL_Renderer* &renderer,char guessLetter)	//keyboard's color changes to RED when choose wrong letter
{
	switch (guessLetter)
	{
		case 'q':		//Q
		{
			SDL_Rect position;
			position.x=15;
			position.y=340;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/wrong.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'w':		//W
		{
			SDL_Rect position;
			position.x=70;
			position.y=340;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/wrong.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'e':		//E
		{
			SDL_Rect position;
			position.x=125;
			position.y=340;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/wrong.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'r':		//R
		{
			SDL_Rect position;
			position.x=180;
			position.y=340;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/wrong.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 't':		//T
		{
			SDL_Rect position;
			position.x=235;
			position.y=340;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/wrong.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'y':		//Y
		{
			SDL_Rect position;
			position.x=290;
			position.y=340;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/wrong.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'u':		//U
		{
			SDL_Rect position;
			position.x=345;
			position.y=340;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/wrong.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'i':		//I
		{
			SDL_Rect position;
			position.x=400;
			position.y=340;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/wrong.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'o':		//O
		{
			SDL_Rect position;
			position.x=455;
			position.y=340;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/wrong.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'p':		//P
		{
			SDL_Rect position;
			position.x=510;
			position.y=340;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/wrong.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'a':		//A
		{
			SDL_Rect position;
			position.x=35;
			position.y=395;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/wrong.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 's':		//S
		{
			SDL_Rect position;
			position.x=90;
			position.y=395;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/wrong.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'd':		//D
		{
			SDL_Rect position;
			position.x=145;
			position.y=395;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/wrong.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'f':		//F
		{
			SDL_Rect position;
			position.x=200;
			position.y=395;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/wrong.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'g':		//G
		{
			SDL_Rect position;
			position.x=255;
			position.y=395;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/wrong.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'h':		//H
		{
			SDL_Rect position;
			position.x=310;
			position.y=395;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/wrong.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'j':		//J
		{
			SDL_Rect position;
			position.x=365;
			position.y=395;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/wrong.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'k':		//K
		{
			SDL_Rect position;
			position.x=420;
			position.y=395;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/wrong.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'l':		//L
		{
			SDL_Rect position;
			position.x=475;
			position.y=395;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/wrong.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'z':		//Z
		{
			SDL_Rect position;
			position.x=90;
			position.y=450;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/wrong.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'x':		//X
		{
			SDL_Rect position;
			position.x=145;
			position.y=450;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/wrong.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'c':		//C
		{
			SDL_Rect position;
			position.x=200;
			position.y=450;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/wrong.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'v':		//V
		{
			SDL_Rect position;
			position.x=255;
			position.y=450;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/wrong.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'b':		//B
		{
			SDL_Rect position;
			position.x=310;
			position.y=450;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/wrong.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'n':		//N
		{
			SDL_Rect position;
			position.x=365;
			position.y=450;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/wrong.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
		case 'm':		//M
		{
			SDL_Rect position;
			position.x=420;
			position.y=450;
			position.w=40;
			position.h=40;
			SDL_Texture*texture=NULL;                                   
			SDL_Surface*surface=IMG_Load("image/wrong.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			textKeyboard(window,renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			break;
		}
	}
	SDL_RenderPresent(renderer);
}

void drawBackground(SDL_Window* &window, SDL_Renderer* &renderer)
{
	SDL_Rect position;
	position.x=0;
	position.y=0;
	position.w=572;
	position.h=331;
	SDL_Texture*texture=NULL;                                   //image_loading to position (x,y)
	SDL_Surface*surface=IMG_Load("image/background.png");
	texture=SDL_CreateTextureFromSurface(renderer,surface);
	SDL_RenderCopy(renderer,texture,NULL,&position);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void drawKeyboard(SDL_Window* &window, SDL_Renderer* &renderer)
{
	SDL_Rect position;
	position.x=0;
	position.y=331;
	position.w=572;
	position.h=201;
	SDL_Texture*texture=NULL;                                   //image_loading
	SDL_Surface*surface=IMG_Load("image/keyboard.png");
	texture=SDL_CreateTextureFromSurface(renderer,surface);
	SDL_RenderCopy(renderer,texture,NULL,&position);
}

void mainMenu(SDL_Window* &window, SDL_Renderer* &renderer)
{
	SDL_Texture*texture=NULL;                                   //image_loading
	SDL_Surface*surface=IMG_Load("image/gallow.jpg");
	texture=SDL_CreateTextureFromSurface(renderer,surface);
	SDL_RenderCopy(renderer,texture,NULL,NULL);
}

void textKeyboard(SDL_Window* &window, SDL_Renderer* &renderer)
{	
	{
		TTF_Font*font=TTF_OpenFont("font/arial.ttf",25);  						//Q
		SDL_Color color={0,0,0,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,"q",color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=27;
		textRect.y=347;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(text);
		TTF_CloseFont(font);
	}
	{
		TTF_Font*font=TTF_OpenFont("font/arial.ttf",25);  						//W
		SDL_Color color={0,0,0,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,"w",color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=80;
		textRect.y=347;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(text);
		TTF_CloseFont(font);
	}
	{
		TTF_Font*font=TTF_OpenFont("font/arial.ttf",25);  						//E
		SDL_Color color={0,0,0,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,"e",color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=137;
		textRect.y=347;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(text);
		TTF_CloseFont(font);
	}
	{
		TTF_Font*font=TTF_OpenFont("font/arial.ttf",25);  						//R
		SDL_Color color={0,0,0,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,"r",color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=192;
		textRect.y=347;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(text);
		TTF_CloseFont(font);
	}
	{
		TTF_Font*font=TTF_OpenFont("font/arial.ttf",25);  						//T
		SDL_Color color={0,0,0,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,"t",color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=247;
		textRect.y=347;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(text);
		TTF_CloseFont(font);
	}
	{
		TTF_Font*font=TTF_OpenFont("font/arial.ttf",25);  						//Y
		SDL_Color color={0,0,0,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,"y",color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=302;
		textRect.y=347;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(text);
		TTF_CloseFont(font);
	}
	{
		TTF_Font*font=TTF_OpenFont("font/arial.ttf",25);  						//U
		SDL_Color color={0,0,0,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,"u",color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=357;
		textRect.y=347;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(text);
		TTF_CloseFont(font);
	}
	{
		TTF_Font*font=TTF_OpenFont("font/arial.ttf",25);  						//I
		SDL_Color color={0,0,0,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,"i",color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=417;
		textRect.y=347;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(text);
		TTF_CloseFont(font);
	}
	{
		TTF_Font*font=TTF_OpenFont("font/arial.ttf",25);  						//O
		SDL_Color color={0,0,0,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,"o",color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=467;
		textRect.y=347;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(text);
		TTF_CloseFont(font);
	}
	{
		TTF_Font*font=TTF_OpenFont("font/arial.ttf",25);  						//P
		SDL_Color color={0,0,0,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,"p",color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=522;
		textRect.y=347;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(text);
		TTF_CloseFont(font);
	}
	{
		TTF_Font*font=TTF_OpenFont("font/arial.ttf",25);  						//A
		SDL_Color color={0,0,0,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,"a",color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=48;
		textRect.y=403;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(text);
		TTF_CloseFont(font);
	}
	{
		TTF_Font*font=TTF_OpenFont("font/arial.ttf",25);  						//S
		SDL_Color color={0,0,0,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,"s",color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=102;
		textRect.y=403;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(text);
		TTF_CloseFont(font);
	}
	{
		TTF_Font*font=TTF_OpenFont("font/arial.ttf",25);  						//D
		SDL_Color color={0,0,0,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,"d",color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=157;
		textRect.y=403;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(text);
		TTF_CloseFont(font);
	}
	{
		TTF_Font*font=TTF_OpenFont("font/arial.ttf",25);  						//F
		SDL_Color color={0,0,0,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,"f",color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=212;
		textRect.y=403;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(text);
		TTF_CloseFont(font);
	}
	{
		TTF_Font*font=TTF_OpenFont("font/arial.ttf",25);  						//G
		SDL_Color color={0,0,0,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,"g",color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=267;
		textRect.y=403;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(text);
		TTF_CloseFont(font);
	}
	{
		TTF_Font*font=TTF_OpenFont("font/arial.ttf",25);  						//H
		SDL_Color color={0,0,0,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,"h",color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=322;
		textRect.y=403;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(text);
		TTF_CloseFont(font);
	}
	{
		TTF_Font*font=TTF_OpenFont("font/arial.ttf",25);  						//J
		SDL_Color color={0,0,0,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,"j",color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=379;
		textRect.y=403;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(text);
		TTF_CloseFont(font);
	}
	{
		TTF_Font*font=TTF_OpenFont("font/arial.ttf",25);  						//K
		SDL_Color color={0,0,0,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,"k",color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=432;
		textRect.y=403;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(text);
		TTF_CloseFont(font);
	}
	{
		TTF_Font*font=TTF_OpenFont("font/arial.ttf",25);  						//L
		SDL_Color color={0,0,0,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,"l",color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=489;
		textRect.y=403;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(text);
		TTF_CloseFont(font);
	}
	{
		TTF_Font*font=TTF_OpenFont("font/arial.ttf",25);  						//Z
		SDL_Color color={0,0,0,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,"z",color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=104;
		textRect.y=458;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(text);
		TTF_CloseFont(font);
	}
	{
		TTF_Font*font=TTF_OpenFont("font/arial.ttf",25);  						//X
		SDL_Color color={0,0,0,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,"x",color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=157;
		textRect.y=458;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(text);
		TTF_CloseFont(font);
	}
	{
		TTF_Font*font=TTF_OpenFont("font/arial.ttf",25);  						//C
		SDL_Color color={0,0,0,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,"c",color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=212;
		textRect.y=458;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(text);
		TTF_CloseFont(font);
	}
	{
		TTF_Font*font=TTF_OpenFont("font/arial.ttf",25);  						//V
		SDL_Color color={0,0,0,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,"v",color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=267;
		textRect.y=458;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(text);
		TTF_CloseFont(font);
	}
	{
		TTF_Font*font=TTF_OpenFont("font/arial.ttf",25);  						//B
		SDL_Color color={0,0,0,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,"b",color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=322;
		textRect.y=458;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(text);
		TTF_CloseFont(font);
	}
	{
		TTF_Font*font=TTF_OpenFont("font/arial.ttf",25);  						//N
		SDL_Color color={0,0,0,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,"n",color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=377;
		textRect.y=458;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(text);
		TTF_CloseFont(font);
	}
	{
		TTF_Font*font=TTF_OpenFont("font/arial.ttf",25);  						//M
		SDL_Color color={0,0,0,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,"m",color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=431;
		textRect.y=458;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(text);
		TTF_CloseFont(font);
	}
}
void gameIntro(SDL_Window* &window, SDL_Renderer* &renderer)
{
	
	{//Load UET incon						
		SDL_Rect position;
		position.x=0;
		position.y=0;
		position.w=572;
		position.h=530;
		SDL_Texture*texture=NULL;                                   
		SDL_Surface*surface=IMG_Load("image/uet.jpg");   
		texture=SDL_CreateTextureFromSurface(renderer,surface);
		SDL_RenderCopy(renderer,texture,NULL,&position);
		SDL_RenderPresent(renderer);
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);	
		SDL_Delay(800);
		SDL_RenderClear(renderer);
	}
	{//Load FET icon
		SDL_SetRenderDrawColor(renderer,255,255,255,255);
		SDL_RenderClear(renderer);
		SDL_Rect position;
		position.x=0;
		position.y=0;
		position.w=572;
		position.h=530;
		SDL_Texture*texture=NULL;                                   
		SDL_Surface*surface=IMG_Load("image/fet.png");
		texture=SDL_CreateTextureFromSurface(renderer,surface);
		SDL_RenderCopy(renderer,texture,NULL,&position);
		SDL_RenderPresent(renderer);	
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
		SDL_Delay(800);
		SDL_RenderClear(renderer);
	}
	{
		SDL_Texture*texture=NULL;                                   //image_loading
		SDL_Surface*surface=IMG_Load("image/rope.jpg");
		texture=SDL_CreateTextureFromSurface(renderer,surface);
		SDL_RenderCopy(renderer,texture,NULL,NULL);
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
	}
	{
		TTF_Font*font=TTF_OpenFont("font/upperFontIntro.ttf",43);  						//upper_text_font_setup
		SDL_Color color={170,0,4,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,"H A N G    M A N",color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=50;
		textRect.y=80;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_RenderPresent(renderer);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(text);
		TTF_CloseFont(font);
	}
	{
		TTF_Font*font=TTF_OpenFont("font/arial.ttf",25);  						//lower_text_font_setup
		SDL_Color color={0,0,0,255};
		SDL_Surface*textSurface=TTF_RenderText_Solid(font,"(Press any key to continue)",color);
		SDL_Texture*text=SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_Rect textRect;
		textRect.x=140;
		textRect.y=490;
		SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);
		SDL_RenderCopy(renderer,text,NULL,&textRect);
		SDL_RenderPresent(renderer);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(text);
		TTF_CloseFont(font);
	}
}

void logSDLError(std::ostream& os, const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (window == nullptr)
        logSDLError(std::cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
    if (renderer == nullptr)
        logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

