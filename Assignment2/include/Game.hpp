#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "config.hpp"
#include <vector>

class CollisionComponent;
class Manager;

class Game{
  public:
    Game();
    ~Game();

    void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);

    void handleEvent();
    void update();
    void render();
    void clean();

    void updateCamera();

    bool running(){
      return this->isRunning;
    };

    static void addTile(int x, int y, int id = 0, float scale = 1.0f);

  private:
    bool isRunning;
    SDL_Window* window;

  public:
    static SDL_Renderer *renderer;
    static SDL_Event event;
    static std::vector<CollisionComponent*> colliders;
    static SDL_Rect camera;
    static Manager manager;
};

#endif