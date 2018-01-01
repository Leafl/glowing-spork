#ifndef VERTEX_HPP
#define VERTEX_HPP
/*
 * code repurposed from unit 7 ligthing using Cube
 * Project 4
 * Shaila DiGiovanni & Emma Theberge
 */


#include <vector>
#include <glm/glm.hpp>
#include "Triangle.hpp"
#include <iostream>

using std::vector;
using glm::vec3;
using glm::vec2;
using std::cerr;
using std::endl;

class Triangle;

class Vertex
{
public:
    Vertex(vec3 pos, vec3 col);
    Vertex(vec3 pos, vec3 col, vec2 tc);//added by suzuka

    // Add a triangle to the list
    void addTriangle(Triangle*);
    void calculateNormal();

    // Getters, Setters

    vec3 getPos()
    {
	return position;
    }

    vec3 getColor()
    {
	return color;
    }

    vec3 getNormal()
    {
	return normal;
    }

    vec2 getTexCoord()
    {
	return tex_coord;
    }//added by Suzuka

    void setNormal(vec3 n)
    {
	normal = n;
    }

    void setTexCoord(vec2 tc)
    {
	tex_coord = tc;
    }

private:
    vector<Triangle*> triangles;

    vec3 position;
    vec3 color;
    vec3 normal;
    vec2 tex_coord;
};



#endif
