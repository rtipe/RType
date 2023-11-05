//
// Created by youba on 03/11/2023.
//

#include "Core.hpp"

int main() {
  try {
    Uniti::Core mainInstance(
        Uniti::Object::openJsonFile("./Json/Server/project.json"));

    mainInstance.start();
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
}