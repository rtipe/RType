//
// Created by youba on 04/11/2023.
//

#pragma once

#include "IObjectPlugin.hpp"
#include "Vector.hpp"
#include "../Entity/Entity.hpp"

class Projectile : public Uniti::IObjectPlugin {
public:
    Projectile(Uniti::Object &object);

    Uniti::Object &getObject() override;

    void awake(const Json::Value &value) override;

    void preStart() override;

    void start() override;

    void postStart() override;

    void preUpdate() override;

    void update() override;

    void postUpdate() override;

    void preEnd() override;

    void end() override;

    void postEnd() override;

    const Uniti::Clock &getClock() const override;

    Uniti::Clock &getClock() override;

    const Uniti::Event &getEvent() const override;

    Uniti::Event &getEvent() override;

private:
    static int _id;
    Uniti::Object &_object;
    Uniti::Clock _clock;
    Uniti::Event _event;
    float _damage;
    bool _directional;
    Uniti::Vector2f _normal;
    float _speed;
    Entity::EntityType _type;
};