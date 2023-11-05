//
// Created by youba on 04/11/2023.
//

#include "Projectile.hpp"
#include "API.hpp"
#include "Core.hpp"
#include "Object.hpp"
#include "PluginCreator.hpp"

int Projectile::_id = 0;

Projectile::Projectile(Uniti::Object &object) : _object(object) {
  this->_event.addEvent("overlapped", [&](const Json::Value &value) {
    auto object =
        Uniti::Object::find(value.asString(), this->_object.getCore());
    if (!object.value().get().getPluginManager().has("Entity"))
      return;
    Entity &entity = object.value().get().get<Entity &>("Entity");
    if (entity.getType() == this->_type)
      return;
    entity.getHP() -= this->_damage;
    Json::Value data;
    data["name"] = "DestroyEntity";
    data["value"] = this->_object.getName();
    data["id"] = this->_object.getName();
    this->_object.getCore().getPluginManager().emitEvent("sendAll", data);
    this->_object.getScene().getObjects().remove(this->_object.getName());
  });
}

Uniti::Object &Projectile::getObject() { return this->_object; }

void Projectile::awake(const Json::Value &value) {
  this->_speed = value.get("speed", 0).asFloat();
  this->_type = (value.get("type", "enemy").asString() == "ally")
                    ? Entity::ALLY
                    : Entity::ENEMY;
  this->_damage = value.get("damage", 0).asFloat();
  this->_directional = value.get("directional", false).asBool();
  if (!this->_directional) {
    if (this->_type == Entity::ENEMY) {
      this->_normal = Uniti::Vector2f(-1, 0);
    } else {
      this->_normal = Uniti::Vector2f(1, 0);
    }
  }
  this->_object.getName() =
      this->_object.getName() + "_" + std::to_string(Projectile::_id);
  Projectile::_id++;
}

void Projectile::preStart() {}

void Projectile::start() {}

void Projectile::postStart() {}

void Projectile::preUpdate() {
  if (this->_normal.getX() == 0 && this->_normal.getY() == 0 &&
      this->_directional) {
    std::vector<std::reference_wrapper<Entity>> entities;
    for (auto &object : this->_object.getScene().getObjects().getObjects()) {
      if (!object->getPluginManager().has("Entity"))
        continue;
      Entity &entity = object.get()->get<Entity &>("Entity");
      if (entity.getType() != this->_type)
        entities.push_back(entity);
    }
    if (entities.empty()) {
      if (this->_type == Entity::ENEMY) {
        this->_normal = Uniti::Vector2f(-1, 0);
      } else {
        this->_normal = Uniti::Vector2f(1, 0);
      }
    } else {
      Entity &entity = entities[std::rand() % entities.size()];
      Uniti::Vector2f normal = Uniti::Vector::getNormal(
          this->_object.getTransform().getPosition(),
          entity.getObject().getTransform().getPosition());
      this->_normal = normal;
    }
  }
}

void Projectile::update() {
  Json::Value value;

  value["speed"] = this->_speed;
  value["deltaTime"] = this->_clock.getSeconds();
  value["position"]["x"] = this->_normal.getX();
  value["position"]["y"] = this->_normal.getY();
  this->_object.emitEvent("move", value);
  this->_clock.restart();
}

void Projectile::postUpdate() {
  Json::Value value;
  value["name"] = "Entities";
  value["value"]["position"]["x"] =
      this->_object.getTransform().getPosition().getX();
  value["value"]["position"]["y"] =
      this->_object.getTransform().getPosition().getY();
  value["id"] = this->_object.getName();
  this->_object.getCore().getPluginManager().emitEvent("sendAll", value);
  if (this->_object.getTransform().getPosition().getX() < -100 ||
      this->_object.getTransform().getPosition().getX() > 1920 ||
      this->_object.getTransform().getPosition().getY() < -100 ||
      this->_object.getTransform().getPosition().getY() > 1080) {
    Json::Value data;
    data["name"] = "DestroyEntity";
    data["value"] = this->_object.getName();
    data["id"] = this->_object.getName();
    this->_object.getCore().getPluginManager().emitEvent("sendAll", data);
    this->_object.getScene().getObjects().remove(this->_object.getName());
  }
}

void Projectile::preEnd() {}

void Projectile::end() {}

void Projectile::postEnd() {}

const Uniti::Clock &Projectile::getClock() const { return this->_clock; }

Uniti::Clock &Projectile::getClock() { return this->_clock; }

const Uniti::Event &Projectile::getEvent() const { return this->_event; }

Uniti::Event &Projectile::getEvent() { return this->_event; }

extern "C" {
void *getCreator(void) {
  return new Uniti::PluginCreator<Uniti::IObjectPlugin, Projectile,
                                  Uniti::Object>();
}

void deleteCreator(void *creator) {
  delete static_cast<
      Uniti::PluginCreator<Uniti::IObjectPlugin, Projectile, Uniti::Object> *>(
      creator);
}
}
