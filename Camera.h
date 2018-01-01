/* Code taken from and altered from:
 * _CSC5210_Unit7 Lighting
 * (Class Example)
 *
 * Project 4
 * Shaila DiGiovanni & Emma Theberge
 */

#ifndef _Camera_H
#define _Camera_H

#include <fstream>
#include <iostream>
#include <glm/glm.hpp>// Used for the GLM math library
#include <glm/gtc/matrix_transform.hpp> // Used for the GLM math library
#include <cmath>

using std::cerr;
using std::endl;
using namespace glm;

// A value for PI
const float PI = acos(-1.0);

// This is our Camera class to manage user movement in our 3D scene

class Camera
{
public:

    Camera();
    Camera(vec3, float, float);

    // Functions to get and set the view and projection matrices based on camera
    mat4 getViewMatrix();
    mat4 getPerspectiveMatrix();
    mat4 getOrthographicMatrix();
    void setPerspective(float, float, float, float);

    void printOutYawandPitch();

    // Other getters and setters
    void setPosition(vec3);
    void setPosition(float, float, float);
    vec3 getPosition();
    float getMouseSpeed();
    void setDeltaTime(double);
    void setViewByMouse(float, float);// This function changes the view
    //   based on the delta of the mouse
    //   coordinates
    void moveCamera(float, float);
    void zoomCamera(float);
    glm::vec3 getViewVector();
    glm::vec3 getRightVector();
    glm::vec3 calculateUpVector();


protected:
    mat4 ProjectionMatrix;// The camera's projection matrix
    vec3 Position;// The camera's position
    float FOV;
    float AspectRatio;
    float nearPlane;
    float farPlane;

    // The size of the screen is needed
    float ScreenWidth;
    float ScreenHeight;

    double deltaTime;// The time between frames
    float Speed;// The camera's speed that is used with a time slice
    float RotationSpeed;// The rotation speed for the mouse wheel
    double MouseSpeed;// The speed for the mouse rotations
    float Yaw;// The horizontal rotation angle (in radians), y-axis
    float Pitch;// The vertical rotation angle (in radians, x-axis

    // Added by Chris Stuetzle
    void setDefaults();
};

#endif

