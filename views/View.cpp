//
// Created by stan1 on 06/11/2025.
//

#include "View.h"
namespace views {
    View::View(std::weak_ptr<entities::Entity> entity, std::shared_ptr<Camera> camera) {
        this->entity = entity;
        this->camera = camera;
    }
}