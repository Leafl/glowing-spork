
/* 
 * File:   AmbientLight.h
 * Author: stuetzlec
 *
 * Created on October 27, 2017, 1:30 PM

 * code reulsed and repurposed from unit 7 ligthing
 * Project 4
 * Shaila DiGiovanni & Emma Theberge
 */

#ifndef AMBIENTLIGHT_H
#define AMBIENTLIGHT_H

#include <glm/glm.hpp>
#include "Light.hpp"

using glm::vec3;
using std::min;
using std::max;

class AmbientLight: public Light
{
public:
    AmbientLight(vec3);
    AmbientLight(const AmbientLight& orig);
    virtual ~AmbientLight();

    void connectLightToShader(Shader*);

    void raiseWeight()
    {
	weight = std::min (weight + 0.1, 1.0);
    }

    void lowerWeight()
    {
	weight = std::max (weight - 0.1, 1.0);
    }
private:
    double weight = 0.2;
};

#endif /* AMBIENTLIGHT_H */

