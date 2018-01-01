#ifndef _LIGHT_H_
#define _LIGHT_H_

/*
 * File:   Light.hpp
 * by: CStuetzle?
 *
 * code reulsed and repurposed from unit 7 ligthing

 * Project 4
 * Shaila DiGiovanni & Emma Theberge
 */

#include <glm/glm.hpp>
#include "Shader.hpp"

using glm::vec3;

class Light
{
private:
    bool enabled;

protected:
    Light(vec3);
    vec3 color;
public:
    // Getters, Setters

    vec3 getColor()
    {
	return color;
    }

    // Virtual function to define in subclasses
    virtual void connectLightToShader(Shader*) = 0;

    void enable()
    {
	enabled = true;
    }

    void disable()
    {
	enabled = false;
    }

    void toggle()
    {
	enabled = !enabled;
    }

    bool isEnabled()
    {
	return enabled;
    }
};
#endif
