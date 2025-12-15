//
// Created by stan1 on 06/11/2025.
//

#ifndef CAMERA_H
#define CAMERA_H

struct Position;
class Camera {
public:
  Camera(float Screenwidth, float Screenheight);

  Position worldToPixel(float normX, float normY) const;

  void setMapSize(int MapWidth, int MapHeight);
  void setScreenSize(float Screenwidth, float Screenheight);

  Position getSpritePixelSize() const;

private:
  float screenwidth;
  float screenheight;
  float mapwidth;
  float mapheight;
  float hudTop;
  float hudBottom;
  float usableHeight;
};

#endif // CAMERA_H
