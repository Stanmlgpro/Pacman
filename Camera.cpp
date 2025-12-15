//
// Created by stan1 on 06/11/2025.
//

#include "Camera.h"
#include "entities/Entity.h"
#include <iostream>

Camera::Camera(float Screenwidth, float Screenheight) {
    hudTop = 0.f;
    hudBottom = 0.f;
    screenwidth = Screenwidth;
    screenheight = Screenheight;
    usableHeight = Screenheight - hudTop - hudBottom;
}

Position Camera::getSpritePixelSize() const {
    if (mapwidth <= 0 || mapheight <= 0)
        return {0, 0};
    float tilePixel =
        std::min(screenwidth / static_cast<float>(mapwidth), usableHeight / static_cast<float>(mapheight));
    return {tilePixel, tilePixel};
}

Position Camera::worldToPixel(float normX, float normY) const {

    // clamp norm just in case
    if (normX < -1.f)
        normX = -1.f;
    if (normX > 1.f)
        normX = 1.f;
    if (normY < -1.f)
        normY = -1.f;
    if (normY > 1.f)
        normY = 1.f;

    Position tileSize = getSpritePixelSize();
    float tilePixel = tileSize.x; // square
    if (tilePixel <= 0.f)
        return {0.f, 0.f};

    float mapPixelW = tilePixel * static_cast<float>(mapwidth);
    float mapPixelH = tilePixel * static_cast<float>(mapheight);

    float offsetX = (screenwidth - mapPixelW) / 2.f;
    float offsetY = (usableHeight - mapPixelH) / 2.f;

    float px = offsetX + ((normX + 1.f) * 0.5f) * mapPixelW;
    float py = offsetY + ((normY + 1.f) * 0.5f) * mapPixelH;

    return {px, py};
}

void Camera::setMapSize(int MapWidth, int MapHeight) {
    mapwidth = MapWidth;
    mapheight = MapHeight;
}

void Camera::setScreenSize(float Screenwidth, float Screenheight) {
    screenwidth = Screenwidth;
    usableHeight = Screenheight - hudTop - hudBottom;
}