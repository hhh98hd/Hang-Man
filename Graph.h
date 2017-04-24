

void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();

void drawBackground(SDL_Window* &window, SDL_Renderer* &renderer);
void drawKeyboard(SDL_Window* &window, SDL_Renderer* &renderer);
void textKeyboard(SDL_Window* &window, SDL_Renderer* &renderer);
void gameIntro(SDL_Window* &window, SDL_Renderer* &renderer);
void mainMenu(SDL_Window* &window, SDL_Renderer* &renderer);
void raven(SDL_Window* &window, SDL_Renderer* &renderer);
void changeColor_Wrong(SDL_Window* &window, SDL_Renderer* &renderer,char guessLetter);
void changeColor_Correct(SDL_Window* &window, SDL_Renderer* &renderer,char guessLetter);
void drawHangmanAnimation(SDL_Window* &window, SDL_Renderer* &renderer,int countBad);
void drawHangman(SDL_Window* &window, SDL_Renderer* &renderer,int countBad);
void gameOver(SDL_Window* &window, SDL_Renderer* &renderer,int totalScore);
void showBestScore(SDL_Window* &window, SDL_Renderer* &renderer);

