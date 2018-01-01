/* 
 * File:   DrawableObject.h
 * Author: stuetzlec
 *
 * Created on October 10, 2017, 3:37 PM
 */

#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include <glm/glm.hpp>
#include "Shader.hpp"
#include "Camera.h"

class DrawableObject
{
public:

    DrawableObject()
    {
	model = glm::mat4 (1.0f);
    }

    virtual void draw(Shader*) = 0;
    //virtual vec3 getEyeDirection(vec3) = 0;

    glm::mat4 getModelMatrix()
    {
	return model;
    }

    void applyTransformation(glm::mat4 t)
    {
	model = t * model;
    }

    //added by emma

    void setModelMatrix(glm::mat4 _model)
    {
	model = _model;
    }

    //added by emma

    glm::vec3 getCenter()
    {
	return center;
    }
private:
    vec3 center;//aded by emma
protected:
    glm::mat4 model;

};

#endif /* DRAWABLEOBJECT_H */

