//
// Created by stan1 on 06/11/2025.
//

#include "Camera.h"
#include "entities/Entity.h"
#include <iostream>

Position Camera::getSpritePixelSize() const {
    // check for illegal map sizes
    if (mapwidth <= 0 || mapheight <= 0)
        return {0, 0};
    // calculate the side of the square from the minimum of the 2
    float tilePixel =
        std::min(screenwidth / static_cast<float>(mapwidth), usableHeight / static_cast<float>(mapheight));
    return {tilePixel, tilePixel}; // return the square
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

    // get the tilesize
    Position tileSize = getSpritePixelSize();
    float tilePixel = tileSize.x; // square
    if (tilePixel <= 0.f) // check for illegal sizes
        return {0.f, 0.f};

    // calculate the pixel width of the map
    float mapPixelW = tilePixel * static_cast<float>(mapwidth);
    float mapPixelH = tilePixel * static_cast<float>(mapheight);

    // calculate the offset that our world pixel has from the origin of the map
    float offsetX = (screenwidth - mapPixelW) / 2.f;
    float offsetY = (usableHeight - mapPixelH) / 2.f;

    // use this offset to compute the correct screen coordinates
    float px = offsetX + ((normX + 1.f) * 0.5f) * mapPixelW;
    float py = offsetY + ((normY + 1.f) * 0.5f) * mapPixelH;

    return {px, py}; // return the screen coords
}

// simple setters
void Camera::setMapSize(int MapWidth, int MapHeight) {
    mapwidth = MapWidth;
    mapheight = MapHeight;
}
void Camera::setScreenSize(float Screenwidth, float Screenheight) {
    screenwidth = Screenwidth;
    usableHeight = Screenheight - 100.f;
}