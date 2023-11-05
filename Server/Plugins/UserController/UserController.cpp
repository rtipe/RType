//
// Created by youba on 04/11/2023.
//

#include "UserController.hpp"
#include "API.hpp"
#include "Core.hpp"
#include "Object.hpp"
#include "PluginCreator.hpp"
#include "json/json.h"

UserController::UserController(Uniti::Object &object) : _object(object) {
  this->_event.addEvent("playerMovement", [&](const Json::Value &value) {
    const std::string &user = value["idUser"].asString();
    auto object = Uniti::Object::find_if(
        this->_object.getCore(), [&](const Uniti::Object &compare) {
          return compare.getName().ends_with(user);
        });

    if (object)
      object.value().get().emitEvent("moveEntity", value["data"]);
  });
  this->_event.addEvent("createPlayer", [&](const Json::Value &value) {
    const std::string &user = value["idUser"].asString();
    const std::string &type = value["data"].asString();

    if (!this->_pathCharacter.contains(type))
      return;
    auto object = std::make_unique<Uniti::Object>(this->_pathCharacter[type],
                                                  this->_object.getScene());
    object->getName() = object->getName() + "_" + user;
    object->getTransform().getPosition().getX() = 100;
    object->getTransform().getPosition().getY() = std::rand() % 950;
    this->_object.getScene().getObjects().add(std::move(object));
  });
  this->_event.addEvent("disconnectUser", [&](const Json::Value &value) {
    const std::string &user = value.asString();
    auto object = Uniti::Object::find_if(
        this->_object.getCore(), [&](const Uniti::Object &compare) {
          return compare.getName().ends_with(user);
        });

    if (!object)
      return;
    Json::Value data;
    data["name"] = "DestroyEntity";
    data["value"] = object.value().get().getName();
    data["id"] = object.value().get().getName();
    this->_object.getCore().getPluginManager().emitEvent("sendAll", data);
    this->_object.getScene().getObjects().remove(
        object.value().get().getName());
  });
  this->_event.addEvent("pressA", [&](const Json::Value &value) {
    const std::string &user = value["idUser"].asString();
    auto object = Uniti::Object::find_if(
        this->_object.getCore(), [&](const Uniti::Object &compare) {
          return compare.getName().ends_with(user);
        });

    if (object)
      object.value().get().emitEvent("basicAttack", value["data"]);
  });
  this->_event.addEvent("pressZ", [&](const Json::Value &value) {
    const std::string &user = value["idUser"].asString();
    auto object = Uniti::Object::find_if(
        this->_object.getCore(), [&](const Uniti::Object &compare) {
          return compare.getName().ends_with(user);
        });

    if (object)
      object.value().get().emitEvent("directionalAttack", value["data"]);
  });
  this->_event.addEvent("pressE", [&](const Json::Value &value) {
    const std::string &user = value["idUser"].asString();
    auto object = Uniti::Object::find_if(
        this->_object.getCore(), [&](const Uniti::Object &compare) {
          return compare.getName().ends_with(user);
        });

    if (object)
      object.value().get().emitEvent("boostSpeed", value["data"]);
  });
  this->_event.addEvent("pressR", [&](const Json::Value &value) {
    const std::string &user = value["idUser"].asString();
    auto object = Uniti::Object::find_if(
        this->_object.getCore(), [&](const Uniti::Object &compare) {
          return compare.getName().ends_with(user);
        });

    if (object)
      object.value().get().emitEvent("specialAttack", value["data"]);
  });
}

Uniti::Object &UserController::getObject() { return this->_object; }

void UserController::awake(const Json::Value &value) {
  for (const auto &character : value["characters"].getMemberNames())
    this->_pathCharacter[character] =
        Uniti::Object::openJsonFile(value["characters"][character].asString());
}

void UserController::preStart() {}

void UserController::start() {}

void UserController::postStart() {}

void UserController::preUpdate() {}

void UserController::update() {}

void UserController::postUpdate() {}

void UserController::preEnd() {}

void UserController::end() {}

void UserController::postEnd() {}

const Uniti::Clock &UserController::getClock() const { return this->_clock; }

Uniti::Clock &UserController::getClock() { return this->_clock; }

const Uniti::Event &UserController::getEvent() const { return this->_event; }

Uniti::Event &UserController::getEvent() { return this->_event; }

extern "C" {
void *getCreator(void) {
  return new Uniti::PluginCreator<Uniti::IObjectPlugin, UserController,
                                  Uniti::Object>();
}

void deleteCreator(void *creator) {
  delete static_cast<Uniti::PluginCreator<Uniti::IObjectPlugin, UserController,
                                          Uniti::Object> *>(creator);
}
}
