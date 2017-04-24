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

void nameInput(SDL_Window* &window, SDL_Renderer* &renderer,char Letter,char Name[],int i)
{
	changeColor_Correct(window,renderer,Letter);
	if (Letter!='1'&&Letter!='0') 
	{
		Name[i]=Letter;
		Name[i+1]=0;
	}
}

char chooseLetter1(SDL_Window* &window, SDL_Renderer* &renderer) ///return letter when click on the virtual keyboard
{
	int Ox,Oy;
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
					if (e.button.button == SDL_BUTTON_LEFT)	//Get mouse position when LMB clicked
					{
						SDL_GetMouseState(&Ox,&Oy);
						break;
					}
				}
			}
		}
		if(307<Ox && Ox<(307+ 62) && 271< Oy && Oy<(271+40))// Player choose to end input name
		{
			SDL_Rect position;
			position.x=307;
			position.y=271;
			position.w=62;
			position.h=40;
			SDL_Texture*texture=NULL;                                   //image_loading to position (x,y)
			SDL_Surface*surface=IMG_Load("image/ent_clicked.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			SDL_RenderPresent(renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			SDL_Delay(175);
			return '1';
			break;
		}
		if(170<Ox && Ox<(170+ 62) && 271< Oy && Oy<(271+40))// Player choose to end clear the last character
		{
			SDL_Rect position;
			position.x=170;
			position.y=271;
			position.w=62;
			position.h=40;
			SDL_Texture*texture=NULL;                                   //image_loading to position (x,y)
			SDL_Surface*surface=IMG_Load("image/clr_clicked.png");
			texture=SDL_CreateTextureFromSurface(renderer,surface);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			SDL_RenderPresent(renderer);
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
			return '0';
			break;
		}
		if (15<Ox && Ox<(15+ 40) && 340< Oy && Oy<(340+40)) //Q
        {
			return 'q';
			break;
		}
		if (70<Ox && Ox<(70+ 40) && 340< Oy && Oy<(340+40)) //W
		{
			return 'w';
			break;
		}
		if (125<Ox && Ox<(125+ 40) && 340< Oy && Oy<(340+40)) //E
		{
			return 'e';
			break; 
		}
		if (180<Ox && Ox<(180+ 40) && 340< Oy && Oy<(340+40)) //R
		{
			return 'r';
			break;
		}
		if (247<Ox && Ox<(247+ 40) && 340< Oy && Oy<(340+40)) //T
		{
			return 't';
			break;
		}
		if (290<Ox && Ox<(290+ 40) && 340< Oy && Oy<(340+40)) //Y
		{
			return 'y';
			break;
		}
		if (345<Ox && Ox<(345+ 40) && 340< Oy && Oy<(340+40)) //U
		{
			return 'u';
			break;
		}
		if (400<Ox && Ox<(400+ 40) && 340< Oy && Oy<(340+40)) //I
		{
			return 'i';
			break;
		}
		if (455<Ox && Ox<(455+ 40) && 340< Oy && Oy<(340+40)) //O
		{
			return 'o';
			break;
		}
		if (510<Ox && Ox<(510+ 40) && 340< Oy && Oy<(340+40)) //P
		{
			return 'p';
			break;
		}
		if (35<Ox && Ox<(35+ 40) && 395< Oy && Oy<(395+40)) //A
		{
			return 'a';
			break;
		}
		if (90<Ox && Ox<(90+ 40) && 395< Oy && Oy<(395+40)) //S
		{
			return 's';
			break;
		}
		if (145<Ox && Ox<(145+ 40) && 395< Oy && Oy<(395+40)) //D
		{
			return 'd';
			break;
		}
		if (200<Ox && Ox<(200+ 40) && 395< Oy && Oy<(395+40)) //F
		{
			return 'f';
			break;
		}
		if (255<Ox && Ox<(255+ 40) && 395< Oy && Oy<(395+40)) //G
		{
			return 'g';
			break;
		}
		if (310<Ox && Ox<(310+ 40) && 395< Oy && Oy<(395+40)) //H
		{
			return 'h';
			break;
		}
		if (365<Ox && Ox<(365+ 40) && 395< Oy && Oy<(395+40)) //J
		{
			return 'j';
			break;
		}
		if (420<Ox && Ox<(420+ 40) && 395< Oy && Oy<(395+40)) //K
		{
			return 'k';
			break;
		}
		if (475<Ox && Ox<(475+ 40) && 395< Oy && Oy<(395+40)) //L
		{
			return 'l';
			break;
		}
		if (90<Ox && Ox<(90+ 40) && 450< Oy && Oy<(450+40)) //Z
		{
			return 'z';
			break;
		}
		if (145<Ox && Ox<(145+ 40) && 450< Oy && Oy<(450+40)) //X
		{
			return 'x';
			break;
		}
		if (200<Ox && Ox<(200+ 40) && 450< Oy && Oy<(450+40)) //C
		{
			return 'c';
			break;
		}
		if (255<Ox && Ox<(255+ 40) && 450< Oy && Oy<(450+40)) //V
		{
			return 'v';
			break;
		}
		if (310<Ox && Ox<(310+ 40) && 450< Oy && Oy<(450+40)) //B
		{
			return 'b';
			break;
		}
		if (365<Ox && Ox<(365+ 40) && 450< Oy && Oy<(450+40)) //N
		{
			return 'n';
			break;
		}
		if (420<Ox && Ox<(420+ 40) && 450< Oy && Oy<(450+40)) //M
		{
			return 'm';
			break;
		}
	}
}
void Update(SDL_Window* &window, SDL_Renderer* &renderer,string& randWord, char guessWord[],char& guessLetter,int& countBad,int& addScore)
{
	Mix_Volume(-1,90);
	int i;
	int n=randWord.length();
	int t=randWord.find_first_of(guessLetter,0);
	if (guessLetter=='1'||guessLetter=='0')
	{
		return;
	}
	if (t<0)
	{
		//playWrongSoundEffect();	//play sound effect
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
		changeColor_Wrong(window,renderer,guessLetter); //keyboard's color changes to RED when choose wrong letter
		countBad++;
		addScore-=50;
	}
	else
	{
		//playCorrectSoundEffect(); //play sound effect
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
		changeColor_Correct(window,renderer,guessLetter); //keyboard's color changes to GREEN when choose correct letter
		for (i=0;i<n;++i)								//update the guess word
		{
			if (randWord[i]==guessLetter)
			{
				guessWord[i]=guessLetter;
				addScore+=100;
			}
		}
	}
}

string chooseWord()  //choose a random word from word list
{
	srand(time(NULL));
	int i,r;
	vector<string> wordList;
	ifstream file;
	file.open("data/list.txt");
	string word;
	if (file.is_open())
	{
		while (getline(file,word))
		{
			wordList.push_back(word);
		}
		file.close();
	}
	if (wordList.size()>0)
	{
		r=rand()%wordList.size();
		cout<<wordList[r]<<endl;
		return wordList[r];
	}
	else
	{
		return "";
	}
}

char chooseLetter(SDL_Window* &window, SDL_Renderer* &renderer,int totalScore) ///return letter when click on the virtual keyboard
{
	int Ox,Oy;
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
					if (e.button.button == SDL_BUTTON_LEFT)	//Get mouse position when LMB clicked
					{
						SDL_GetMouseState(&Ox,&Oy);
						break;
					}
				}
			}
		}
		{
		if (532<Ox && Ox<(532+ 40) && 0< Oy && Oy<(0+40))	//Exit to main menu
		{
			{
				SDL_Rect position;
				position.x=532;
				position.y=0;
				position.w=40;
				position.h=40;
				SDL_Texture*texture=NULL;                                   //image_loading to position (x,y)
				SDL_Surface*surface=IMG_Load("image/pause_clicked.png");
				texture=SDL_CreateTextureFromSurface(renderer,surface);
				SDL_RenderCopy(renderer,texture,NULL,&position);
				SDL_RenderPresent(renderer);
				SDL_FreeSurface(surface);
				SDL_DestroyTexture(texture);
			}
			
			SDL_Delay(175);
			SDL_Rect position;
			position.x=110;
			position.y=330/2;
			position.w=352;
			position.h=232;
			SDL_Texture*texture=NULL;                                   //ask if player want to quit game
			SDL_Surface*image=IMG_Load("image/ask_if_quit.png");
			texture=SDL_CreateTextureFromSurface(renderer,image);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			SDL_RenderPresent(renderer);
			SDL_FreeSurface(image);
			SDL_DestroyTexture(texture);
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
				if(143<Ox && Ox<(143+ 104) && 302< Oy && Oy<(302+59)) //RESUME game when player choose "NO"
				{
					SDL_Rect position;
					position.x=143;
					position.y=302;
					position.w=104;
					position.h=59;
					SDL_Texture*texture=NULL;                                 
					SDL_Surface*image=IMG_Load("image/no.png");
					texture=SDL_CreateTextureFromSurface(renderer,image);
					SDL_RenderCopy(renderer,texture,NULL,&position);
					SDL_RenderPresent(renderer);
					SDL_FreeSurface(image);
					SDL_DestroyTexture(texture);
					SDL_Delay(175);
					return '1';
					break;
				}
				if(310<Ox && Ox<(310+ 104) && 302< Oy && Oy<(302+59)) //QUIT game when player choose "YES"
				{
					SDL_Rect position;
					position.x=310;
					position.y=302;
					position.w=104;
					position.h=59;
					SDL_Texture*texture=NULL;                                   
					SDL_Surface*image=IMG_Load("image/yes.png");
					texture=SDL_CreateTextureFromSurface(renderer,image);
					SDL_RenderCopy(renderer,texture,NULL,&position);
					SDL_RenderPresent(renderer);
					SDL_FreeSurface(image);
					SDL_DestroyTexture(texture);
				    //Mix_CloseAudio();  
					SDL_Delay(175);
					//check if player break the score record
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
					if (totalScore>playerScore)
					{
						//playHighScoreSoundEffect();
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
						char Name[999];
						int i=0;
						char Letter;
						while (true)
						{
							//display input content 2 times to prevent pverlapping
							SDL_Delay(1);
							Letter=chooseLetter1(window,renderer);
							if (Letter=='1'||Letter=='0')
							{
								if (Letter=='1')        
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
								nameInput(window,renderer,Letter,Name,i);
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
					}
					return '0';
					break;
				}
			}
		}
	}
		if (15<Ox && Ox<(15+ 40) && 340< Oy && Oy<(340+40)) //Q
        {
			return 'q';
			break;
		}
		if (70<Ox && Ox<(70+ 40) && 340< Oy && Oy<(340+40)) //W
		{
			return 'w';
			break;
		}
		if (125<Ox && Ox<(125+ 40) && 340< Oy && Oy<(340+40)) //E
		{
			return 'e';
			break; 
		}
		if (180<Ox && Ox<(180+ 40) && 340< Oy && Oy<(340+40)) //R
		{
			return 'r';
			break;
		}
		if (247<Ox && Ox<(247+ 40) && 340< Oy && Oy<(340+40)) //T
		{
			return 't';
			break;
		}
		if (290<Ox && Ox<(290+ 40) && 340< Oy && Oy<(340+40)) //Y
		{
			return 'y';
			break;
		}
		if (345<Ox && Ox<(345+ 40) && 340< Oy && Oy<(340+40)) //U
		{
			return 'u';
			break;
		}
		if (400<Ox && Ox<(400+ 40) && 340< Oy && Oy<(340+40)) //I
		{
			return 'i';
			break;
		}
		if (455<Ox && Ox<(455+ 40) && 340< Oy && Oy<(340+40)) //O
		{
			return 'o';
			break;
		}
		if (510<Ox && Ox<(510+ 40) && 340< Oy && Oy<(340+40)) //P
		{
			return 'p';
			break;
		}
		if (35<Ox && Ox<(35+ 40) && 395< Oy && Oy<(395+40)) //A
		{
			return 'a';
			break;
		}
		if (90<Ox && Ox<(90+ 40) && 395< Oy && Oy<(395+40)) //S
		{
			return 's';
			break;
		}
		if (145<Ox && Ox<(145+ 40) && 395< Oy && Oy<(395+40)) //D
		{
			return 'd';
			break;
		}
		if (200<Ox && Ox<(200+ 40) && 395< Oy && Oy<(395+40)) //F
		{
			return 'f';
			break;
		}
		if (255<Ox && Ox<(255+ 40) && 395< Oy && Oy<(395+40)) //G
		{
			return 'g';
			break;
		}
		if (310<Ox && Ox<(310+ 40) && 395< Oy && Oy<(395+40)) //H
		{
			return 'h';
			break;
		}
		if (365<Ox && Ox<(365+ 40) && 395< Oy && Oy<(395+40)) //J
		{
			return 'j';
			break;
		}
		if (420<Ox && Ox<(420+ 40) && 395< Oy && Oy<(395+40)) //K
		{
			return 'k';
			break;
		}
		if (475<Ox && Ox<(475+ 40) && 395< Oy && Oy<(395+40)) //L
		{
			return 'l';
			break;
		}
		if (90<Ox && Ox<(90+ 40) && 450< Oy && Oy<(450+40)) //Z
		{
			return 'z';
			break;
		}
		if (145<Ox && Ox<(145+ 40) && 450< Oy && Oy<(450+40)) //X
		{
			return 'x';
			break;
		}
		if (200<Ox && Ox<(200+ 40) && 450< Oy && Oy<(450+40)) //C
		{
			return 'c';
			break;
		}
		if (255<Ox && Ox<(255+ 40) && 450< Oy && Oy<(450+40)) //V
		{
			return 'v';
			break;
		}
		if (310<Ox && Ox<(310+ 40) && 450< Oy && Oy<(450+40)) //B
		{
			return 'b';
			break;
		}
		if (365<Ox && Ox<(365+ 40) && 450< Oy && Oy<(450+40)) //N
		{
			return 'n';
			break;
		}
		if (420<Ox && Ox<(420+ 40) && 450< Oy && Oy<(450+40)) //M
		{
			return 'm';
			break;
		}
	}
}
