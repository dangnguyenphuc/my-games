#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "config.hpp"
#include <vector>

// game states
#define EXIT                          0
#define IS_RUNNING                    1
#define IS_RUNNING_VS_COMPUTER        2
#define ACTIVE_START                  3
#define ACTIVE_END                    4

class CollisionComponent;
class Manager;
class Ball;

class Game{
  public:
    Game();
    ~Game();

    void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);

    void handleEvent();
    void update();
    void render();
    void clean();
    void runGame();
    void drawGameWhileRunning();
    void updateCamera();

    int getGameState(){
      return (this->gameState);
    };

    static void addTile(int x, int y, int id = 0, float scale = 1.0f);

  private:
    SDL_Window* window;

  public:
    static SDL_Renderer *renderer;
    static SDL_Event event;
    static std::vector<CollisionComponent*> colliders;
    static SDL_Rect camera;
    static Manager manager;
    static Ball* ball;
    static TTF_Font* font;
    static int gameState;
};

#endif