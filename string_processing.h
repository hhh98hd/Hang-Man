using namespace std;
char chooseLetter(SDL_Window* &window, SDL_Renderer* &renderer,int totalScore);
char chooseLetter1(SDL_Window* &window, SDL_Renderer* &renderer);
string chooseWord();
void Update(SDL_Window* &window, SDL_Renderer* &renderer,string& randWord, char guessWord[],char& guessLetter,int& countBad,int& addScore);
void nameInput(SDL_Window* &window, SDL_Renderer* &renderer,char Letter,char Name[],int i);
