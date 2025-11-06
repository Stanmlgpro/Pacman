//
// Created by stan1 on 06/11/2025.
//

#include "View.h"

View::View(std::weak_ptr<Entity> entity) {
    this->entity = entity;
}

