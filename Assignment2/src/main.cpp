#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>

std::string backgroundPath = "D:/ASS2/GameProgamming/Assignment2/assets/image/Menu/start_bg.png";
std::string buttonPath = "D:/ASS2/GameProgamming/Assignment2/assets/image/Menu/pwp_btn.png";

class Button
{
private:
  SDL_Rect rect;
  SDL_Texture *texture;

public:
  Button(SDL_Renderer *renderer, int x, int y, int width, int height)
  {
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;

    SDL_Surface *surface = IMG_Load(buttonPath.c_str());
    if (surface == nullptr)
    {
      std::cerr << "Failed to load button image: " << IMG_GetError() << std::endl;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
  }

  ~Button()
  {
    SDL_DestroyTexture(texture);
  }

  void render(SDL_Renderer *renderer)
  {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
  }

  bool isClicked(int mouseX, int mouseY)
  {
    return (mouseX >= rect.x && mouseX <= rect.x + rect.w && mouseY >= rect.y && mouseY <= rect.y + rect.h);
  }

  SDL_Rect getRect() const
  {
    return rect;
  }

  void setPosition(int x, int y)
  {
    rect.x = x;
    rect.y = y;
  }
};

class Menu
{
private:
  SDL_Renderer *renderer;
  SDL_Texture *background;
  std::vector<Button *> buttons;

public:
  Menu(SDL_Renderer *ren) : renderer(ren)
  {
    SDL_Surface *surface = IMG_Load(backgroundPath.c_str());
    if (surface == nullptr)
    {
      std::cerr << "Failed to load background image: " << IMG_GetError() << std::endl;
    }
    background = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
  }

  ~Menu()
  {
    SDL_DestroyTexture(background);
    for (Button *button : buttons)
    {
      delete button;
    }
    buttons.clear();
  }

  void addButton(Button *button)
  {
    buttons.push_back(button);
  }

  void render()
  {
    SDL_RenderCopy(renderer, background, NULL, NULL);
    for (Button *button : buttons)
    {
      button->render(renderer);
    }
  }

  int handleEvents(SDL_Event event)
  {
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
    {
      int mouseX, mouseY;
      SDL_GetMouseState(&mouseX, &mouseY);
      for (Button *button : buttons)
      {
        if (button->isClicked(mouseX, mouseY))
        {
          return 1;
        }
      }
    }
    return 0;
  }

  void setButtonsCentered(int screenWidth, int screenHeight)
  {
    int totalHeight = 0;
    for (Button *button : buttons)
    {
      totalHeight += button->getRect().h;
    }
    int offsetY = (screenHeight - totalHeight) / 2;
    for (Button *button : buttons)
    {
      button->setPosition((screenWidth - button->getRect().w) / 2, offsetY);
      offsetY += button->getRect().h;
    }
  }
};

int main(int argc, char *argv[])
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow("Game Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
  if (window == nullptr)
  {
    std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr)
  {
    std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  Menu menu(renderer);

  // Tạo và cấu hình buttons
  Button *startButton = new Button(renderer, 0, 0, 200, 50); // Thêm các tham số vào đây để cấu hình vị trí của button
  menu.addButton(startButton);

  // Đặt buttons vào giữa màn hình
  menu.setButtonsCentered(800, 600);

  bool quit = false;
  SDL_Event event;
  while (!quit)
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        quit = true;
      }
      if (event.type == SDL_MOUSEBUTTONDOWN)
      {
        int result = menu.handleEvents(event);
        if (result == 1)
        {
          std::cout << "Button clicked!" << std::endl;
        }
      }
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    menu.render();

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
