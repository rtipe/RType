//
// Created by youba on 05/11/2023.
//

#include "Explosion.hpp"
#include "Object.hpp"
#include "Core.hpp"
#include "PluginCreator.hpp"
#include "API.hpp"

Explosion::Explosion(Uniti::Object &object): _object(object) {}

Uniti::Object &Explosion::getObject() {
    return this->_object;
}

void Explosion::awake(const Json::Value &value) {
    this->_timeBeforeExplosion = value.get("timeBeforeExplosion", 0.5).asFloat();
}

void Explosion::preStart() {

}

void Explosion::start() {

}

void Explosion::postStart() {

}

void Explosion::preUpdate() {

}

void Explosion::update() {
    if (this->_clock.getSeconds() < this->_timeBeforeExplosion) return;
    this->_clock.restart();
    this->_object.getScene().getObjects().remove(this->_object.getName());
}

void Explosion::postUpdate() {

}

void Explosion::preEnd() {

}

void Explosion::end() {

}

void Explosion::postEnd() {

}

const Uniti::Clock &Explosion::getClock() const {
    return this->_clock;
}

Uniti::Clock &Explosion::getClock() {
    return this->_clock;
}

const Uniti::Event &Explosion::getEvent() const {
    return this->_event;
}

Uniti::Event &Explosion::getEvent() {
    return this->_event;
}

extern "C" {
void *getCreator(void) {
    return new Uniti::PluginCreator<Uniti::IObjectPlugin, Explosion, Uniti::Object>();
}

void deleteCreator(void *creator) {
    delete static_cast<Uniti::PluginCreator<Uniti::IObjectPlugin, Explosion, Uniti::Object> *>(creator);
}
}