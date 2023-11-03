//
// Created by youba on 03/11/2023.
//

#pragma once

#include "IObjectPlugin.hpp"
#include "Box.hpp"

class Animation : public Uniti::IObjectPlugin {
public:
    struct AnimationFrames {
        AnimationFrames() = default;
        AnimationFrames(const Json::Value &value);
        std::vector<Json::Value> frames;
        float secondRemaining = 0;
    };
    Animation(Uniti::Object &object);

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
    std::map<std::string, AnimationFrames> _animations;
    std::string _actualAnimation = "idle";
    int _iteration = 0;
    int _remaining = -1;
    Uniti::Object &_object;
    Uniti::Clock _clock;
    Uniti::Event _event;
    float _width;
    float _height;
};
