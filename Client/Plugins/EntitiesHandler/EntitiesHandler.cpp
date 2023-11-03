//
// Created by youba on 03/11/2023.
//

#include "EntitiesHandler.hpp"
#include "Vector2f.hpp"
#include "Object.hpp"
#include "Scene.hpp"
#include "PluginCreator.hpp"
#include "API.hpp"

EntitiesHandler::EntitiesHandler(Uniti::Object &object): _object(object) {
    std::vector<std::string> vesselType =
            {"BasicEnemy", "Kamikaze", "Sniper", "Tank", "Boss", "VesselHeal", "VesselWeapon"};
    std::vector<std::string> noExplosion = {"VesselHeal", "VesselWeapon"};

    this->_event.addEvent("Entities", [&](const Json::Value &value) {
        for (const auto &nameVessel : value["data"].getMemberNames()) {
            auto data = value["data"][nameVessel];
            auto id = data["id"].asString();
            std::string vesselName = "BasicVessel";

            auto it = std::find_if(vesselType.begin(), vesselType.end(), [&](const std::string &type) {
                return id.starts_with(type);
            });
            if (it != vesselType.end())
                vesselName = *it;
            auto copy   = Uniti::Object::find(vesselName, this->_object.getScene());
            auto vessel = Uniti::Object::find(id, this->_object.getScene());

            if (!copy) return;
            if (!vessel) {
                auto newVessel = std::make_unique<Uniti::Object>(copy.value());
                newVessel->setName(id);
                this->_object.getScene().getObjects().add(std::move(newVessel));
            } else {
                vessel.value().get().emitEvent("moveTo", data);
            }
        }
    });
    this->_event.addEvent("destroyEntity", [&](const Json::Value &value) {
       for (const auto &name : value["data"]) {
           this->_object.getScene().getObjects().remove(name.asString());
       }
    });
}

Uniti::Object &EntitiesHandler::getObject() {
    return this->_object;
}

void EntitiesHandler::awake(const Json::Value &value) {

}

void EntitiesHandler::preStart() {

}

void EntitiesHandler::start() {

}

void EntitiesHandler::postStart() {

}

void EntitiesHandler::preUpdate() {

}

void EntitiesHandler::update() {

}

void EntitiesHandler::postUpdate() {

}

void EntitiesHandler::preEnd() {

}

void EntitiesHandler::end() {

}

void EntitiesHandler::postEnd() {

}

const Uniti::Clock &EntitiesHandler::getClock() const {
    return this->_clock;
}

Uniti::Clock &EntitiesHandler::getClock() {
    return this->_clock;
}

const Uniti::Event &EntitiesHandler::getEvent() const {
    return this->_event;
}

Uniti::Event &EntitiesHandler::getEvent() {
    return this->_event;
}

extern "C" {
void *getCreator(void) {
    return new Uniti::PluginCreator<Uniti::IObjectPlugin, EntitiesHandler, Uniti::Object>();
}

void deleteCreator(void *creator) {
    delete static_cast<Uniti::PluginCreator<Uniti::IObjectPlugin, EntitiesHandler, Uniti::Object> *>(creator);
}
}
