//
// Created by youba on 04/11/2023.
//

#include "Entity.hpp"
#include "Core.hpp"
#include "Object.hpp"
#include "PluginCreator.hpp"
#include "json/json.h"

int Entity::_id = 0;

Entity::Entity(Uniti::Object &object): _object(object) {
    this->_event.addEvent("moveEntity", [&] (const Json::Value &value) {
        Json::Value data;
        data["speed"] = this->_speed;
        data["position"] = value;
        data["deltaTime"] = this->_clock.getSeconds();
        this->_object.emitEvent("move", data);
        this->_clock.restart();
    });
    this->_event.addEvent("basicAttack", [&] (const Json::Value &value) {
        if (this->_attacks[0].clock.getSeconds() < this->_attacks[0].cooldown) return;
        this->_attacks[0].clock.restart();
        auto projectile = std::make_unique<Uniti::Object>(this->_attacks[0].projectileObject, this->_object.getScene());
        projectile.get()->getTransform().getPosition() = this->_object.getTransform().getPosition() + this->_spawnProjectile;
        this->_object.getScene().getObjects().add(std::move(projectile));
    });
    this->_event.addEvent("directionalAttack", [&] (const Json::Value &value) {
        if (this->_attacks[1].clock.getSeconds() < this->_attacks[1].cooldown) return;
        this->_attacks[1].clock.restart();
        auto projectile = std::make_unique<Uniti::Object>(this->_attacks[1].projectileObject, this->_object.getScene());
        projectile.get()->getTransform().getPosition() = this->_object.getTransform().getPosition() + this->_spawnProjectile;
        this->_object.getScene().getObjects().add(std::move(projectile));
    });
    this->_event.addEvent("boostSpeed", [&] (const Json::Value &value) {

    });
    this->_event.addEvent("specialAttack", [&] (const Json::Value &value) {
        if (this->_attacks[2].clock.getSeconds() < this->_attacks[2].cooldown) return;
        this->_attacks[2].clock.restart();
        auto projectile = std::make_unique<Uniti::Object>(this->_attacks[2].projectileObject, this->_object.getScene());
        projectile.get()->getTransform().getPosition() = this->_object.getTransform().getPosition() + this->_spawnProjectile;
        this->_object.getScene().getObjects().add(std::move(projectile));
    });
    this->_event.addEvent("overlapped", [&] (const Json::Value &value) {
        if (this->_player) return;
        auto object = Uniti::Object::find(value.asString(), this->_object.getCore());
        if (!object.value().get().getPluginManager().has("Entity")) return;
        Entity &entity = object.value().get().get<Entity &>("Entity");
        if (entity.getType() == this->_type) return;
        entity.getHP() -= this->_destroyDamage;
        Json::Value data;
        data["name"] = "DestroyEntity";
        data["value"] = this->_object.getName();
        data["id"] = this->_object.getName();
        this->_object.getCore().getPluginManager().emitEvent("sendAll", data);
        this->_object.getScene().getObjects().remove(this->_object.getName());
    });
}

Uniti::Object &Entity::getObject() {
    return this->_object;
}

void Entity::awake(const Json::Value &value) {
    this->_speed = value.get("speed", 0).asFloat();
    this->_hp = value.get("hp", 0).asFloat();
    this->_type = (value.get("type", "enemy").asString() == "ally") ? ALLY : ENEMY;
    this->_ai = value.get("ai", false).asBool();
    this->_player = value.get("isPlayer", false).asBool();
    this->_spawnProjectile = value["spawnProjectile"];
    this->_destroyDamage = value.get("destroyDamage", 20).asFloat();
    for (const auto &attack : value["attacks"])
        this->_attacks.push_back(attack);
    if (!this->_player) {
        this->_object.getName() = this->_object.getName() + "_" + std::to_string(Entity::_id);
        Entity::_id++;
    }
}

void Entity::preStart() {

}

void Entity::start() {

}

void Entity::postStart() {
    if (this->_ai) return;
    if (this->_player) return;
}

void Entity::preUpdate() {

}

void Entity::update() {
    if (this->_player) return;
    Json::Value value;

    value["speed"] = this->_speed;
    value["deltaTime"] = this->_clock.getSeconds();
    if (!this->_ai) {
        this->_object.emitEvent("moveLeft", value);
    } else {
        value["position"]["x"] = -1;
        value["position"]["y"] = (std::rand() % 200 + (-100)) / 100;
        this->_object.emitEvent("move", value);
    }
    for (auto &attack : this->_attacks) {
        if (attack.clock.getSeconds() < attack.cooldown) continue;
        attack.clock.restart();
        auto projectile = std::make_unique<Uniti::Object>(attack.projectileObject, this->_object.getScene());
        projectile.get()->getTransform().getPosition() = this->_object.getTransform().getPosition() + this->_spawnProjectile;
        this->_object.getScene().getObjects().add(std::move(projectile));
        break;
    }
    this->_clock.restart();
}

void Entity::postUpdate() {
    Json::Value value;
    value["name"] = "Entities";
    value["value"]["position"]["x"] = this->_object.getTransform().getPosition().getX();
    value["value"]["position"]["y"] = this->_object.getTransform().getPosition().getY();
    value["value"]["life"] = this->_hp;
    value["id"] = this->_object.getName();
    this->_object.getCore().getPluginManager().emitEvent("sendAll", value);
    if ((!this->_player && this->_object.getTransform().getPosition().getX() < -100) || this->_hp <= 0) {
        Json::Value data;
        data["name"] = "DestroyEntity";
        data["value"] = this->_object.getName();
        data["id"] = this->_object.getName();
        this->_object.getCore().getPluginManager().emitEvent("sendAll", data);
        this->_object.getScene().getObjects().remove(this->_object.getName());
    }
}

void Entity::preEnd() {

}

void Entity::end() {

}

void Entity::postEnd() {

}

const Uniti::Clock &Entity::getClock() const {
    return this->_clock;
}

Uniti::Clock &Entity::getClock() {
    return this->_clock;
}

const Uniti::Event &Entity::getEvent() const {
    return this->_event;
}

Uniti::Event &Entity::getEvent() {
    return this->_event;
}

Entity::EntityType Entity::getType() const {
    return this->_type;
}

float &Entity::getHP() {
    return this->_hp;
}

Entity::Attack::Attack(const Json::Value &attack) {
    this->damage = attack.get("damage", 0).asFloat();
    this->cooldown = attack.get("cooldown", 2).asFloat();
    this->projectileObject = Uniti::Object::openJsonFile(attack.get("projectile", "").asString());
}


