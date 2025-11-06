//
// Created by stan1 on 06/11/2025.
//

#ifndef CAMERA_H
#define CAMERA_H

struct Position;
class Camera {
public:
    Camera(float Screenheight, float Screenwidth);

    Position worldToPixel(float normX, float normY) const;

    void setMapSize(int MapWidth, int MapHeight);

    Position getSpritePixelSize() const;
private:
    float screenheight;
    float screenwidth;
    float mapwidth;
    float mapheight;
};



#endif //CAMERA_H
