//
// Created by stan on 10/15/25.
//

#include "Orb.h"

Orb::Orb(int x, int y, bool big) {
    position.x = x;
    position.y = y;
    this->big = big;
}

bool Orb::isBig() const {
    return big;
}