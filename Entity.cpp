//
// Created by stan1 on 13/10/2025.
//

#include "Entity.h"

void Entity::Update(float dt) {
    position.x += direction[0]*dt;
    position.y += direction[1]*dt;
}
