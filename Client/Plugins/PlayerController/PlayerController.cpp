//
// Created by youba on 03/11/2023.
//

#include "PlayerController.hpp"
#include "API.hpp"
#include "Core.hpp"
#include "Object.hpp"
#include "PluginCreator.hpp"

PlayerController::PlayerController(Uniti::Object &object) : _object(object) {
  this->_event.addEvent("KEY_0_PRESSED", [&](const Json::Value &value) {
    Json::Value send;

    send["serverName"] = "game";
    send["name"] = "pressA";
    send["value"] = {};
    this->_object.getCore().getPluginManager().emitEvent("sendEvent", send);
  });
  this->_event.addEvent("KEY_25_PRESSED", [&](const Json::Value &value) {
    Json::Value send;

    send["serverName"] = "game";
    send["name"] = "pressZ";
    send["value"] = {};
    this->_object.getCore().getPluginManager().emitEvent("sendEvent", send);
  });
  this->_event.addEvent("KEY_4_PRESSED", [&](const Json::Value &value) {
    Json::Value send;

    send["serverName"] = "game";
    send["name"] = "pressZ";
    send["value"] = {};
    this->_object.getCore().getPluginManager().emitEvent("sendEvent", send);
  });
  this->_event.addEvent("KEY_17_PRESSED", [&](const Json::Value &value) {
    Json::Value send;

    send["serverName"] = "game";
    send["name"] = "pressR";
    send["value"] = {};
    this->_object.getCore().getPluginManager().emitEvent("sendEvent", send);
  });
  this->_event.addEvent("KEY_71_PRESSED", [&](const Json::Value &value) {
    this->_normal = {-1, 0};
    this->_isPressed = true;
  });
  this->_event.addEvent("KEY_72_PRESSED", [&](const Json::Value &value) {
    this->_normal = {1, 0};
    this->_isPressed = true;
  });
  this->_event.addEvent("KEY_73_PRESSED", [&](const Json::Value &value) {
    this->_normal = {0, -1};
    this->_isPressed = true;
  });
  this->_event.addEvent("KEY_74_PRESSED", [&](const Json::Value &value) {
    this->_normal = {0, 1};
    this->_isPressed = true;
  });
  this->_event.addEvent("KEY_71_RELEASED", [&](const Json::Value &value) {
    this->_normal = {0, 0};
    this->_isPressed = false;
  });
  this->_event.addEvent("KEY_72_RELEASED", [&](const Json::Value &value) {
    this->_normal = {0, 0};
    this->_isPressed = false;
  });
  this->_event.addEvent("KEY_73_RELEASED", [&](const Json::Value &value) {
    this->_normal = {0, 0};
    this->_isPressed = false;
  });
  this->_event.addEvent("KEY_74_RELEASED", [&](const Json::Value &value) {
    this->_normal = {0, 0};
    this->_isPressed = false;
  });
}

Uniti::Object &PlayerController::getObject() { return this->_object; }

void PlayerController::awake(const Json::Value &value) {
  this->_ip = value.get("ip", "").asString();
  this->_port = value.get("port", 0).asInt();
  this->_character = value.get("character", "").asString();
}

void PlayerController::preStart() {
  Json::Value server;
  server["name"] = "game";
  server["ip"] = this->_ip;
  server["port"] = this->_port;
  this->_object.getCore().getPluginManager().emitEvent("addServer", server);
}

void PlayerController::start() {}

void PlayerController::postStart() {
  Json::Value send;

  send["serverName"] = "game";
  send["name"] = "createPlayer";
  send["value"] = this->_character;
  this->_object.getCore().getPluginManager().emitEvent("sendEvent", send);
}

void PlayerController::preUpdate() {}

void PlayerController::update() {
  Json::Value send;

  send["serverName"] = "game";
  send["name"] = "playerMovement";
  send["value"]["x"] = this->_normal.getX();
  send["value"]["y"] = this->_normal.getY();
  this->_object.getCore().getPluginManager().emitEvent("sendEvent", send);
}

void PlayerController::postUpdate() {}

void PlayerController::preEnd() {}

void PlayerController::end() {}

void PlayerController::postEnd() {}

const Uniti::Clock &PlayerController::getClock() const { return this->_clock; }

Uniti::Clock &PlayerController::getClock() { return this->_clock; }

const Uniti::Event &PlayerController::getEvent() const { return this->_event; }

Uniti::Event &PlayerController::getEvent() { return this->_event; }

extern "C" {
void *getCreator(void) {
  return new Uniti::PluginCreator<Uniti::IObjectPlugin, PlayerController,
                                  Uniti::Object>();
}

void deleteCreator(void *creator) {
  delete static_cast<Uniti::PluginCreator<Uniti::IObjectPlugin,
                                          PlayerController, Uniti::Object> *>(
      creator);
}
}
