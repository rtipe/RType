//
// Created by youba on 04/11/2023.
//

#include "WaveSpawn.hpp"
#include "API.hpp"
#include "Core.hpp"
#include "Object.hpp"
#include "PluginCreator.hpp"

WaveSpawn::WaveSpawn(Uniti::Object &object) : _object(object) {}

Uniti::Object &WaveSpawn::getObject() { return this->_object; }

void WaveSpawn::awake(const Json::Value &value) {
  for (const auto &enemy : value["enemies"]) {
    this->_enemies.push_back(Uniti::Object::openJsonFile(enemy.asString()));
  }
  this->_spawnTime = value.get("spawnTime", 0).asFloat();
}

void WaveSpawn::preStart() {}

void WaveSpawn::start() {}

void WaveSpawn::postStart() {}

void WaveSpawn::preUpdate() {}

void WaveSpawn::update() {
  if (this->_clock.getSeconds() < this->_spawnTime)
    return;
  this->_clock.restart();
  for (auto &enemy : this->_enemies) {
    if (std::rand() % 100 > enemy.get("random", 5).asInt())
      continue;
    auto object =
        std::make_unique<Uniti::Object>(enemy, this->_object.getScene());
    object->getTransform().getPosition().getX() = 2000;
    if (enemy.isMember("spawn")) {
      object->getTransform().getPosition() = Uniti::Vector2f(enemy["spawn"]);
    } else
      object->getTransform().getPosition().getY() = std::rand() % 950;
    this->_object.getScene().getObjects().add(std::move(object));
  }
}

void WaveSpawn::postUpdate() {}

void WaveSpawn::preEnd() {}

void WaveSpawn::end() {}

void WaveSpawn::postEnd() {}

const Uniti::Clock &WaveSpawn::getClock() const { return this->_clock; }

Uniti::Clock &WaveSpawn::getClock() { return this->_clock; }

const Uniti::Event &WaveSpawn::getEvent() const { return this->_event; }

Uniti::Event &WaveSpawn::getEvent() { return this->_event; }

extern "C" {
void *getCreator(void) {
  return new Uniti::PluginCreator<Uniti::IObjectPlugin, WaveSpawn,
                                  Uniti::Object>();
}

void deleteCreator(void *creator) {
  delete static_cast<
      Uniti::PluginCreator<Uniti::IObjectPlugin, WaveSpawn, Uniti::Object> *>(
      creator);
}
}
