//
// Created by youba on 04/11/2023.
//

#include "API.hpp"
#include "PluginCreator.hpp"
#include "Entity.hpp"

extern "C" {
void *getCreator(void) {
    return new Uniti::PluginCreator<Uniti::IObjectPlugin, Entity, Uniti::Object>();
}

void deleteCreator(void *creator) {
    delete static_cast<Uniti::PluginCreator<Uniti::IObjectPlugin, Entity, Uniti::Object> *>(creator);
}
}