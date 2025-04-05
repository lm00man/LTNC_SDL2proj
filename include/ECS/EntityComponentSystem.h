#ifndef COMPONENTENTITYSYSTEM_H
#define COMPONENTENTITYSYSTEM_H

#include <algorithm>
#include<iostream>
#include<memory>
#include<bitset>
#include<vector>
#include<array>

class Component;
class Entity;

using ComponentID = std::size_t;
using EntityID = std::size_t;

template<typename T> inline ComponentID getComponentTypeID() noexcept{
    static ComponentID lastID = 0;
    static ComponentID typeID = lastID++;
    return typeID;
}

constexpr std::size_t Max_Components = 32;
constexpr std::size_t Max_Entities = 100000;

using ComponentsBitset = std::bitset<Max_Components>;
using ComponentsArray = std::array<Component*, Max_Components>;

class Component {
public:
    virtual void init(){};

    virtual void update(){};

    virtual void render(){};

    virtual ~Component(){};

public:
    Entity *entity;
};

class Entity {
private:
    bool active = true;
    ComponentsArray componentsArray;
    ComponentsBitset componentsBitset;
    std::vector<std::unique_ptr<Component> > components;

public:
    void update() {
        for(auto &c : components) {c -> update();}
        for(auto &c : components) {c -> render();}
    }
    void render() {
    };
    bool const isActive() { return active; };
    void destroy() { active = false; };

    template<typename T> auto hasComponent() const{
        return componentsBitset[getComponentTypeID<T>()];
    }

    template<typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs) {
        T* c = new T(std::forward<TArgs>(mArgs)...);
        c -> entity = this;
        std::unique_ptr<Component> uPtr{ c };
        components.emplace_back(std::move(uPtr));
        componentsArray[getComponentTypeID<T>()] = c;
        componentsBitset[getComponentTypeID<T>()] = true;


        c -> init();
        return *c;
    }
    template<typename T>
    T& getComponent() const {
        auto ptr(componentsArray[getComponentTypeID<T>()]);
        return *static_cast<T *>(ptr);
    }
};
class Manager {
private:
    std::vector<std::unique_ptr<Entity> > entities;

public:
    void update()
    {
        for(auto &e : entities) {e ->update();};
    }
    void render()
    {
        for(auto &e : entities) {e -> render();};
    }
    void refresh()
    {
        entities.erase(std::remove_if(std::begin(entities), std::end(entities),
            [] (const std::unique_ptr<Entity> &mEntity) {return !mEntity->isActive();}),
            std::end(entities));
    }
    Entity& addEntity() {
        auto e = new Entity();
        std::unique_ptr<Entity> uPtr{ e };
        entities.emplace_back(std::move(uPtr));
        return *e;
    }
};


#endif //COMPONENTENTITYSYSTEM_H
