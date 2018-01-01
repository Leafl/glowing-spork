/*
 * File:   AmbientLight.cpp
 * Author: stuetzlec
 * 
 * Created on October 27, 2017, 1:30 PM
 * code reulsed and repurposed from unit 7 ligthing
 * Project 4
 * Shaila DiGiovanni & Emma Theberge
 */

#include "AmbientLight.hpp"

AmbientLight::AmbientLight(vec3 col) : Light(col)
{

}

AmbientLight::AmbientLight(const AmbientLight& orig) : Light(orig)
{

}

AmbientLight::~AmbientLight()
{
}

void AmbientLight::connectLightToShader(Shader* s)
{
    GLuint aL=s->GetVariable("ambientColor");
    s->SetVector3(aL, 1, &color[0]);

    GLint weight=s->GetVariable("ambientWeight");
    if(isEnabled())
	s->SetFloat(weight, 0.2);
    else
	s->SetFloat(weight, 0.0);
}
