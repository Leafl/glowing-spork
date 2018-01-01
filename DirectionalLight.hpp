/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DirectionalLight.hpp
 * Author: stuetzlec
 *
 * Created on October 27, 2017, 1:34 PM
 */

#ifndef DIRECTIONALLIGHT_HPP
#define DIRECTIONALLIGHT_HPP

#include "Light.hpp"
#include <glm/glm.hpp>

using glm::vec3;

class DirectionalLight: public Light
{
public:
    DirectionalLight(vec3, vec3, GLfloat, GLfloat);
    DirectionalLight(const DirectionalLight& orig);
    virtual ~DirectionalLight();

    void connectLightToShader(Shader*);
private:
    vec3 direction;

    GLfloat shininess;
    GLfloat strength;
};

#endif /* DIRECTIONALLIGHT_HPP */

