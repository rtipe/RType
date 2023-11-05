//
// Created by youba on 04/11/2023.
//

#pragma once

#include "IObjectPlugin.hpp"
#include "Vector2f.hpp"

class Entity : public Uniti::IObjectPlugin {
public:
    enum EntityType {
        ALLY,
        ENEMY
    };
    struct Attack {
        Attack(const Json::Value &attack);
        Uniti::Clock clock;
        float cooldown;
        float damage;
        Json::Value projectileObject;
    };
    Entity(Uniti::Object &object);

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

    EntityType getType() const;
    float &getHP();

private:
    static int _id;
    Uniti::Object &_object;
    Uniti::Clock _clock;
    Uniti::Event _event;
    float _speed;
    float _hp;
    float _destroyDamage;
    EntityType _type;
    bool _ai;
    bool _player;
    std::vector<Attack> _attacks;
    Uniti::Vector2f _spawnProjectile;
};