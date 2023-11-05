//
// Created by youba on 03/11/2023.
//

#include "EntitiesHandler.hpp"
#include "API.hpp"
#include "Core.hpp"
#include "Object.hpp"
#include "PluginCreator.hpp"
#include "Scene.hpp"
#include "json/json.h"

EntitiesHandler::EntitiesHandler(Uniti::Object &object) : _object(object) {
  this->_event.addEvent("Entities", [&](const Json::Value &value) {
    for (const auto &nameVessel : value["data"].getMemberNames()) {
      auto data = value["data"][nameVessel];
      std::string vesselName;

      auto check = std::find(this->_deleteEntities.begin(),
                             this->_deleteEntities.end(), nameVessel);
      if (check != this->_deleteEntities.end())
        return;
      auto it =
          std::find_if(this->_entities.begin(), this->_entities.end(),
                       [&](std::pair<const std::string, Json::Value> type) {
                         return nameVessel.starts_with(type.first);
                       });
      if (it != this->_entities.end())
        vesselName = it->first;
      else
        vesselName = this->_entities.begin()->first;

      auto vessel = Uniti::Object::find(nameVessel, this->_object.getScene());

      if (!vessel) {
        auto newVessel = std::make_unique<Uniti::Object>(
            this->_entities[vesselName], this->_object.getScene());
        newVessel->setName(nameVessel);
        newVessel->getTransform().getPosition() =
            Uniti::Vector2f(data["position"]);
        this->_object.getScene().getObjects().add(std::move(newVessel));
      } else {
        vessel.value().get().getTransform().getPosition() =
            Uniti::Vector2f(data["position"]);
      }
    }
  });
  this->_event.addEvent("DestroyEntity", [&](const Json::Value &value) {
    for (const auto &nameVessel : value["data"].getMemberNames()) {
      this->_object.getScene().getObjects().remove(nameVessel);
      this->_deleteEntities.push_back(nameVessel);
      if (this->_deleteEntities.size() >= 200)
        this->_deleteEntities.erase(this->_deleteEntities.begin());
      auto it =
          std::find_if(this->_noExplosion.begin(), this->_noExplosion.end(),
                       [&](const std::string &type) {
                         return nameVessel.starts_with(type);
                       });
      if (it != this->_noExplosion.end())
        continue;
      auto vessel = Uniti::Object::find(nameVessel, this->_object.getScene());
      auto explosion = std::make_unique<Uniti::Object>(
          this->_explosion, this->_object.getScene());
      explosion->setName(nameVessel + "_explosion");
      explosion->getTransform().getPosition() =
          vessel.value().get().getTransform().getPosition();
      this->_object.getScene().getObjects().add(std::move(explosion));
    }
  });
}

Uniti::Object &EntitiesHandler::getObject() { return this->_object; }

void EntitiesHandler::awake(const Json::Value &value) {
  for (const auto &entity : value["entities"].getMemberNames())
    this->_entities[entity] =
        Uniti::Object::openJsonFile(value["entities"][entity].asString());
  for (const auto &entity : value["noExplosion"])
    this->_noExplosion.push_back(entity.asString());
  this->_explosion = Uniti::Object::openJsonFile(value["explosion"].asString());
}

void EntitiesHandler::preStart() {}

void EntitiesHandler::start() {}

void EntitiesHandler::postStart() {}

void EntitiesHandler::preUpdate() {}

void EntitiesHandler::update() {}

void EntitiesHandler::postUpdate() {}

void EntitiesHandler::preEnd() {}

void EntitiesHandler::end() {}

void EntitiesHandler::postEnd() {}

const Uniti::Clock &EntitiesHandler::getClock() const { return this->_clock; }

Uniti::Clock &EntitiesHandler::getClock() { return this->_clock; }

const Uniti::Event &EntitiesHandler::getEvent() const { return this->_event; }

Uniti::Event &EntitiesHandler::getEvent() { return this->_event; }

extern "C" {
void *getCreator(void) {
  return new Uniti::PluginCreator<Uniti::IObjectPlugin, EntitiesHandler,
                                  Uniti::Object>();
}

void deleteCreator(void *creator) {
  delete static_cast<Uniti::PluginCreator<Uniti::IObjectPlugin, EntitiesHandler,
                                          Uniti::Object> *>(creator);
}
}
