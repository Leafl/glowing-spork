/*
 * File:   PointLight.h
 * Shaila DiGiovanni
 *
 * code reulsed and repurposed from unit 7 ligthing

 * Project 4
 * Shaila DiGiovanni & Emma Theberge
 */
#pragma once
#include "Light.hpp"
class PointLight :
	public Light
{
public:
	PointLight(vec3 col, vec3 pos, GLfloat st, GLfloat sh);
	~PointLight();
	void connectLightToShader(Shader * s);

	void moveLight(vec3 offset);
	
private:
	vec3 position;

	GLfloat shininess;
	GLfloat strength;
};

