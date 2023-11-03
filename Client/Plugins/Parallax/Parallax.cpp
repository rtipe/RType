//
// Created by youba on 03/11/2023.
//

#include "Parallax.hpp"
#include "Object.hpp"
#include "PluginCreator.hpp"
#include "API.hpp"
#include "Core.hpp"

Parallax::Parallax(Uniti::Object &object): _object(object) {}

Uniti::Object &Parallax::getObject() {
    return this->_object;
}

void Parallax::awake(const Json::Value &value) {
    this->_speed = value.get("speed", 0).asFloat();
    this->_width = value.get("width", 0).asFloat();
    this->_end = value.get("end", 0).asFloat();
}

void Parallax::preStart() {

}

void Parallax::start() {

}

void Parallax::postStart() {

}

void Parallax::preUpdate() {

}

void Parallax::update() {

}

void Parallax::postUpdate() {
    float deltaTime = this->_clock.getSeconds();
    for (auto &object : this->_object.getChildren().getObjects()) {
        Json::Value value;

        value["speed"] = this->_speed;
        value["deltaTime"] = deltaTime;
        //object->getTransform().getPosition().getX() -= this->_speed * deltaTime;
        object->emitEvent("moveLeft", value);
        if (object->getTransform().getPosition().getX() < this->_end - this->_width) {
            float exceeded = (this->_end - this->_width) - object->getTransform().getPosition().getX();
            object->getTransform().getPosition().getX() = this->_width + (this->_end - exceeded - 2);
        }
    }
    this->_clock.restart();
}

void Parallax::preEnd() {

}

void Parallax::end() {

}

void Parallax::postEnd() {

}

const Uniti::Clock &Parallax::getClock() const {
    return this->_clock;
}

Uniti::Clock &Parallax::getClock() {
    return this->_clock;
}

const Uniti::Event &Parallax::getEvent() const {
    return this->_event;
}

Uniti::Event &Parallax::getEvent() {
    return this->_event;
}

extern "C" {
void *getCreator(void) {
    return new Uniti::PluginCreator<Uniti::IObjectPlugin, Parallax, Uniti::Object>();
}

void deleteCreator(void *creator) {
    delete static_cast<Uniti::PluginCreator<Uniti::IObjectPlugin, Parallax, Uniti::Object> *>(creator);
}
}
