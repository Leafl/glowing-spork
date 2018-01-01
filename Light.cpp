/*
 * File:   Light.cpp
 * by: CStuetzle?
 *
 * code reulsed and repurposed from unit 7 ligthing

 * Project 4
 * Shaila DiGiovanni & Emma Theberge
 */

#include "Light.hpp"

Light::Light(vec3 col)
{
    enabled=false;
    color=glm::normalize(col);
}
