//
// Created by stan1 on 06/11/2025.
//

#include "EntityFactory.h"

namespace factory {
    // simple getter
std::shared_ptr<Camera> EntityFactory::getCamera() { return camera; }
} // namespace factory