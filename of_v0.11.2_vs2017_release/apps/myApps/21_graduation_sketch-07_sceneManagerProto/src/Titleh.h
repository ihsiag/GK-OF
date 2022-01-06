#pragma once

#include"Scene.hpp"

class Title : public Scene {
public:
    Title(CommonData* const commonData) :
        Scene(commonData)
    {
        //...
    }
    ~Title() {
        //...
    }
    virtual Scene* update() override {
        //...
        return this;
    }
    virtual void draw() const override {
        //...
    }
};
template<>
Scene* Scene::makeScene<Title>() {
    return new Title();
}

