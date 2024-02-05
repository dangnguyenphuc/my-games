#ifndef ECS_HPP
#define ECS_HPP
#pragma once

#include <algorithm>
#include <bitset>
#include <array>
#include <vector>
#include <memory>

class Component;
class Entity;

using ComponentID = std::size_t;
constexpr std::size_t maxComponent = 32;
using ComponentBitSet = std::bitset<maxComponent>;
using ComponentArray = std::array<std::shared_ptr<Component>, maxComponent>;

inline ComponentID getComponentTypeID() {
    static ComponentID lastID = 0;
    return lastID++;
}

template <typename T>
inline ComponentID getComponentTypeID() noexcept {
    static ComponentID typeID = getComponentTypeID();
    return typeID;
}

class Component {
public:
    Entity* entity;

    virtual void init(){

    };
    virtual void update(){
      // printf("Component update()\n");
    };
    virtual void draw(){

    };

    virtual ~Component(){

    };
};

class Entity {
private:
    bool isActive = true;
    std::vector<std::shared_ptr<Component>> components;

    ComponentArray componentArray;
    ComponentBitSet componentBitSet;

public:
    void update() {
        for (auto& c : this->components) {
            c->update();
        }
    }

    void draw() {
        for (auto& c : this->components) {
            c->draw();
        }
    }

    bool getIsActive() const { return this->isActive; }
    void destroy() { this->isActive = false; }

    template <typename T>
    bool hasComponent() const {
        return this->componentBitSet[getComponentTypeID<T>()];
    }

    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs) {
        std::shared_ptr<T> c = std::make_shared<T>(std::forward<TArgs>(mArgs)...);
        c->entity = this;

        this->components.push_back(c);

        this->componentArray[getComponentTypeID<T>()] = c;
        this->componentBitSet[getComponentTypeID<T>()] = true;

        c->init();
        return *c;
    }

    template <typename T>
    T& getComponent() const {
        auto pointer = componentArray[getComponentTypeID<T>()];
        return *std::static_pointer_cast<T>(pointer);
    }
};

class Manager {
private:
    std::vector<std::shared_ptr<Entity>> entities;

public:
    void update() {
        for (auto& e : this->entities) {
            e->update();
        }
    }

    void draw() {
        for (auto& e : this->entities) {
            e->draw();
        }
    }

    void refresh() {
        this->entities.erase(std::remove_if(this->entities.begin(), this->entities.end(),
                                            [](const std::shared_ptr<Entity>& entity) {
                                                return !entity->getIsActive();
                                            }),
                             this->entities.end());
    }

    Entity& addEntity() {
        std::shared_ptr<Entity> e = std::make_shared<Entity>();
        this->entities.push_back(e);

        return *e;
    }
};

#endif
