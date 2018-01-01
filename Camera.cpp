/* Code taken from and altered from:
 * _CSC5210_Unit7_ Lighting
 * (Class Example)
 *
 * Project 4
 * Shaila DiGiovanni & Emma Theberge
 */

#include <time.h>
#include "Camera.h"

Camera::Camera()
{
    assert(false&&"Do not use the default Camera constructor.");
}

Camera::Camera(vec3 pos, float width, float height)
{
    Position=pos;
    ScreenWidth=width;
    ScreenHeight=height;

    setDefaults();
}

void Camera::setDefaults()
{
    FOV=45.0f;
    AspectRatio=(float) ScreenWidth/(float) ScreenHeight;
    nearPlane=0.1f;
    farPlane=500.0f;
    //Yaw: 3.119474
    //Pitch: -0.433827
    Yaw=3.119474;//PI;
    Pitch=-0.433827;//=0.0; // Look directly down the z-axis to start
    MouseSpeed=0.1f;
    Speed=10.f;
    RotationSpeed=0.01f;
}


// This function returns the View matrix, based on the position, up vector,
//   and look-at position.
// Pre:
// Post:

mat4 Camera::getViewMatrix()
{
    glm::vec3 look=Position+getViewVector();
    glm::vec3 up=calculateUpVector();

    return glm::lookAt(Position, look, up);
}

// This function returns the projection matrix, based on the camera's position,
//   and the field of view and aspect ratios, along with distances between
//   near and far planes
// Pre:
// Post:

mat4 Camera::getPerspectiveMatrix()
{
    return glm::perspective(FOV, AspectRatio, nearPlane, farPlane);
}


// This function returns the Projection Matrix of an orthographic projection
// Pre:
// Post:

mat4 Camera::getOrthographicMatrix()
{
	printf("no such thing implemented yet\n");
	return glm::mat4 (1);
}

// This function sets the persepctive parameters for the persepctive camera
// Pre:
// Post:

void Camera::setPerspective(float _fov, float ar, float np, float fp)
{
    FOV=_fov;
    AspectRatio=ar;
    nearPlane=np;
    farPlane=fp;


    
}

// This function sets the position to the argument _pos
// Pre:
// Post:

void Camera::setPosition(vec3 _pos)
{
    Position=_pos;
}

// This function sets the position to the argument _pos
// Pre:
// Post:

void Camera::setPosition(float x, float y, float z)
{
    Position=vec3(x, y, z);
}

// Return the current position of the camera
// Pre:
// Post:

vec3 Camera::getPosition()
{
    return Position;
}

// Return the current mouse speed
// Pre:
// Post:

float Camera::getMouseSpeed()
{
    return MouseSpeed;
}

// This function updates the local deltaTime variable
// Pre:
// Post:

void Camera::setDeltaTime(double dt)
{
    deltaTime=dt;
}

/************************
 ** MOVEMENT FUNCTIONS **
 ***********************/

// This function moves the camera based on the current mouse position, based on
//   dX and dY which are movements in the mouse position
// Pre:
// Post:

void Camera::setViewByMouse(float dX, float dY)
{
    Yaw+=MouseSpeed*deltaTime * dX;
    Pitch+=MouseSpeed*deltaTime * dY;
}

// This function adjusts the camera position by dX and dY
// Pre:
// Post:

void Camera::moveCamera(float dX, float dY)
{
    Position+=glm::vec3(dX*deltaTime * Speed, dY*deltaTime * Speed, 0);
}

// This function zooms the camera based on the number of mouse wheel clicks that
//   have been moved.
// Pre:
// Post:

void Camera::zoomCamera(float delta)
{
    Position+=vec3(0, 0, delta*deltaTime*RotationSpeed);
}


// This function calculates and returns the view direction
// Pre:
// Post:

glm::vec3 Camera::getViewVector()
{
    glm::vec3 direction(
			cos(Pitch)*sin(Yaw),
			sin(Pitch),
			cos(Pitch)*cos(Yaw)
			);

    direction=glm::normalize(direction);
    return direction;
}

// This function returns the vector looking directly to the right of the camera
//   Since we're not changing the vertical component when moving
//   (we're not ever rotating the 'roll' component), Y is 0
// Pre:
// Post:

glm::vec3 Camera::getRightVector()
{
    glm::vec3 right=glm::vec3(
			      sin(Yaw-PI/2.0f),
			      0,
			      cos(Yaw-PI/2.0f)
			      );
    right=glm::normalize(right);
    return right;
}

void Camera::printOutYawandPitch()
{
    printf("Yaw: %f\n",Yaw);
    printf("Pitch: %f\n",Pitch);
}


// This function calculates the current 'up' vector based on the front and
//   right vectors
// Pre: front and right are correct
// Post:

glm::vec3 Camera::calculateUpVector()
{
    return glm::normalize(glm::cross(getRightVector(), getViewVector()));
}
