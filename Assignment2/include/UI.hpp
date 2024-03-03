#ifndef UI_HPP
#define UI_HPP

#pragma once
#include "ECS/Component.hpp"
#include "Game.hpp"

class Button{
  public:
    typedef void (*FunctionPtr)();
  public:
    Entity* button= nullptr;
  private:
    FunctionPtr ptr;
  public:
    Button(FunctionPtr onClicked){
      Entity& b = Game::manager.addEntity();
      this->button = std::move(&b);
      this->ptr = onClicked;
    }

    void init(const char* spriteSheet, int x, int y, float scale = 1.0f){
      this->button->addComponent<TransformComponent>(x, y, scale);
      this->button->addComponent<SpriteComponent>(spriteSheet);
    }

    ~Button(){};

    void draw(){
      this->button->draw();
    }

    bool isClicked(int mouseX, int mouseY)
  {
    int x = (int) this->button->getComponent<TransformComponent>().position.x;
    int y = (int) this->button->getComponent<TransformComponent>().position.y;
    int w = this->button->getComponent<TransformComponent>().width;
    int h = this->button->getComponent<TransformComponent>().height;
    return (mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h);
  }

  void onClicked(){
    this->ptr();
  }
};

class Menu{
  public:
    Entity* background;
    std::vector<Button*> buttons;
  public:
    Menu(){
      Entity& b = Game::manager.addEntity();
      this->background = std::move(&b);
    };

    void init(const char* bg, float scale = 1.0f){
      this->background->addComponent<TransformComponent>(Game::camera.x, Game::camera.y, scale);
      this->background->addComponent<SpriteComponent>(bg);
    }

    void addButton(Button* button){
      this->buttons.push_back(button);
    }

    ~Menu(){
      for (Button *button : this->buttons)
      {
        delete button;
      }
      buttons.clear();
    };

    void draw()
    {
      this->background->draw();
      for (Button *button : buttons)
      {
        button->draw();
      }
    }

    void update(){
      if (Game::event.type == SDL_MOUSEBUTTONDOWN && Game::event.button.button == SDL_BUTTON_LEFT)
      {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        for (Button *button : this->buttons)
        {
          if (button->isClicked(mouseX, mouseY))
          {
            button->onClicked();
          }
        }
      }
    }
};

#endif