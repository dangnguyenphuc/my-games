#ifndef ECS_HPP
#define ECS_HPP
#pragma once

#include <algorithm>
#include <bitset>
#include <array>
#include <vector>
#include <memory>
#include <map>

class Manager;
class Component;
class Entity;

using Group = std::size_t;
using ComponentID = std::size_t;
constexpr std::size_t maxComponent = 32;
constexpr std::size_t maxGroup = 32;
using ComponentBitSet = std::bitset<maxComponent>;
using GroupBitSet = std::bitset<maxGroup>;
using ComponentArray = std::array<std::shared_ptr<Component>, maxComponent>;

inline ComponentID getComponentTypeID() {
    static ComponentID lastID = 0u;
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
        Manager& manager;
        bool isActive = true;
        std::vector<std::shared_ptr<Component>> components;

        ComponentArray componentArray;
        ComponentBitSet componentBitSet;
        GroupBitSet groupBitSet;

    public:

        Entity(Manager& manager):manager(manager){

        }

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

        bool hasGroup(Group group){
            return this->groupBitSet[group];
        }

        void addGroup(Group group);

        void removeGroup(Group group){
            this->groupBitSet[group] = false;
        }

        Manager& getManager() const {
            return manager;
        }




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
    std::array<std::vector<Entity*>, maxGroup> groupedEntities;

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
        for(auto i(0u); i < maxGroup; i+=1)
        {
            auto& v = this->groupedEntities[i];
            v.erase(
                std::remove_if(v.begin(), v.end(),
                [i](Entity* entity){
                    return !entity->getIsActive() || !entity->hasGroup(i);
                }),
                v.end()
            );
        }


        this->entities.erase(std::remove_if(this->entities.begin(), this->entities.end(),
                                            [](const std::shared_ptr<Entity>& entity) {
                                                return !entity->getIsActive();
                                            }),
                             this->entities.end());
    }

    Entity& addEntity() {
        std::shared_ptr<Entity> e = std::make_shared<Entity>(*this);
        this->entities.push_back(e);

        return *e;
    }

    void addToGroup(Entity* entity, Group group){
        this->groupedEntities[group].emplace_back(entity);
    }

    std::vector<Entity*>& getGroup(Group group){
        return this->groupedEntities[group];
    }
};

#endif
