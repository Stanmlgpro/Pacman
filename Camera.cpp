//
// Created by stan1 on 06/11/2025.
//

#include "Camera.h"
#include "Entity.h"
#include <iostream>

Camera::Camera(float Screenheight, float Screenwidth) {
    screenheight = Screenheight;
    screenwidth = Screenwidth;
}

Position Camera::worldToPixel(float normX, float normY) const {
    float pixelX = (normX + 1.f) * 0.5f * screenwidth;
    float pixelY = (1.f - (-normY + 1.f) * 0.5f) * screenheight;
    return { pixelX, pixelY };
}

Position Camera::getSpritePixelSize() const {
    float pixelsPerWorldX = screenwidth / 2.f;
    float pixelsPerWorldY = screenheight / 2.f;
    float tileWorldWidth  = 2.f / mapwidth;
    float tileWorldHeight = 2.f / mapheight;
    return { tileWorldWidth * pixelsPerWorldX, tileWorldHeight * pixelsPerWorldY };
}

void Camera::setMapSize(int MapWidth, int MapHeight) {
    mapwidth = MapWidth;
    mapheight = MapHeight;
}
