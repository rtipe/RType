//
// Created by youba on 03/11/2023.
//

#include "Animation.hpp"
#include "API.hpp"
#include "Core.hpp"
#include "Object.hpp"
#include "PluginCreator.hpp"

Animation::Animation(Uniti::Object &object) : _object(object) {
  this->_event.addEvent("animation", [&](const Json::Value &value) {
    const std::string &animationName = value.get("name", "idle").asString();
    bool loop = value.get("loop", false).asBool();
    int iteration = value.get("iteration", 1).asInt();

    if (!this->_animations.contains(animationName))
      return;
    this->_actualAnimation = animationName;
    this->_remaining = iteration;
    if (loop)
      this->_remaining = -1;
    this->_iteration = 0;
  });
}

Uniti::Object &Animation::getObject() { return this->_object; }

void Animation::awake(const Json::Value &value) {
  const Json::Value &animations = value["animations"];

  for (const auto &animation : animations) {
    const std::string &name = animation["name"].asString();
    this->_animations.emplace(name, AnimationFrames(animation));
  }
}

void Animation::preStart() {}

void Animation::start() {}

void Animation::postStart() {}

void Animation::preUpdate() {
  if (!this->_animations.contains(this->_actualAnimation))
    return;
  if (this->_clock.getSeconds() <
      this->_animations[this->_actualAnimation].secondRemaining)
    return;

  this->_iteration++;
  if (this->_iteration >=
      this->_animations[this->_actualAnimation].frames.size()) {
    if (this->_remaining == 0) {
      this->_actualAnimation = "idle";
      this->_remaining = -1;
    } else if (this->_remaining > 0) {
      this->_remaining--;
    }
    this->_iteration = 0;
  }
  this->_object.emitEvent(
      "changeTextureRect",
      this->_animations[this->_actualAnimation].frames[this->_iteration]);
  this->_clock.restart();
}

void Animation::update() {}

void Animation::postUpdate() {}

void Animation::preEnd() {}

void Animation::end() {}

void Animation::postEnd() {}

const Uniti::Clock &Animation::getClock() const { return this->_clock; }

Uniti::Clock &Animation::getClock() { return this->_clock; }

const Uniti::Event &Animation::getEvent() const { return this->_event; }

Uniti::Event &Animation::getEvent() { return this->_event; }

Animation::AnimationFrames::AnimationFrames(const Json::Value &value) {
  for (const auto &frame : value["frames"])
    this->frames.push_back(frame);
  this->secondRemaining = value.get("time", 0).asFloat();
}

extern "C" {
void *getCreator(void) {
  return new Uniti::PluginCreator<Uniti::IObjectPlugin, Animation,
                                  Uniti::Object>();
}

void deleteCreator(void *creator) {
  delete static_cast<
      Uniti::PluginCreator<Uniti::IObjectPlugin, Animation, Uniti::Object> *>(
      creator);
}
}
