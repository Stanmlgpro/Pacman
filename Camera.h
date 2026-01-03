//
// Created by stan1 on 06/11/2025.
//

#ifndef CAMERA_H
#define CAMERA_H
/**
 * @file Camera.h
 * @brief Camera Class
 */
struct Position;
/**
 * @class Camera
 * @brief Clss responsible for coordinate translation
 *
 * class to swap between screen coordinates and world coordinates
 */
class Camera {
public:
    /**
 * @brief Creates a Camera object.
 */
    Camera() = default;
    /**
     * @brief Calculates the screen coordinates from world coordinates
     *
     * @param normX X value of the world coordinate
     * @param normY Y value of the world coordinate
     * @return returns the screen coordinates
     */
    Position worldToPixel(float normX, float normY) const;
    /**
     * @brief Sets MapSize
     * @param MapWidth, MapHeight
     */
    void setMapSize(int MapWidth, int MapHeight);
    /**
    * @brief Sets ScreenSize
    * @param Screenwidth, Screenheight
    */
    void setScreenSize(float Screenwidth, float Screenheight);
    /**
     * @brief Returns a square size the sprites need to have
     *
     * uses that map/screen size to calculate the size of the sprites
     *
     * @return pixel size
     */
    Position getSpritePixelSize() const;

    ~Camera() = default;

private:
    float screenwidth;
    float screenheight;
    float mapwidth;
    float mapheight;
    /** used to create a gap on the bottom for our scoring and lives */
    float usableHeight;
};

#endif // CAMERA_H
