/*
 * File:   PointLight.cpp
 * Shaila DiGiovanni
 *
 * code reulsed and repurposed from unit 7 ligthing
 
 * Project 4
 * Shaila DiGiovanni & Emma Theberge
 */

#include "PointLight.h"

PointLight::PointLight(vec3 col, vec3 pos, GLfloat st, GLfloat sh) :
	Light(col) {
	position = pos;
	strength = st;
	shininess = sh;
}



PointLight::~PointLight() {
}

void PointLight::connectLightToShader(Shader* s)
{
	// Connect to the variables
	GLint pLightid = s->GetVariable("pointLightColor");
	GLint shininessid = s->GetVariable("Shininess");
	GLint strengthid = s->GetVariable("Strength");
	GLint pLightWeight = s->GetVariable("pointWeight");
	GLint lightPosid = s->GetVariable("LightPosition");

	s->SetVector3(pLightid, 1, &color[0]);
	s->SetVector3(lightPosid, 1, &position[0]);
	s->SetFloat(shininessid, shininess);
	s->SetFloat(strengthid, strength);
	if (isEnabled()) {
		s->SetFloat(pLightWeight, 1.0);
	}
	else {
		s->SetFloat(pLightWeight, 0.0);
	}
}

void PointLight::moveLight(vec3 offset)
{
	position.x = position.x + offset.x;
	position.y = position.y + offset.y;
	position.z = position.z + offset.z;
}
