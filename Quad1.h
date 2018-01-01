/*
 * File:   Quad1.h
 * Project 4
 * some code may be copied and altered from
 * Triangle example
 * Code taken and altered from Unit6 Texture
 * Example
 *
 * Shaila DiGiovanni & Emma Theberge
 */
#ifndef Quad1_h
#define Quad1_h

/*************************
 *** GRAPHICS INCLUDES ***
 ************************/
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <iomanip>
#include <stdio.h>

#include "DrawableObject.h"
#include "Triangle.hpp"
#include "Texture.hpp"
#include "Vertex.hpp"
#include "Shader.hpp"
#include "Quad1.h"
//#include <glm/gtc/matrix_transform.hpp>


using glm::vec3;
using glm::vec4;
using glm::vec2;

class Quad1//: public DrawableObject
{
public:
    Quad1();
    Quad1(Vertex* _a, Vertex* _b, Vertex* _c, Vertex* _d, Texture* tex);

    Quad1(Vertex* _a, Vertex* _b, Vertex* _c, Vertex* _d, Texture* tex, vec3 normal);//added by Shalia

    Quad1(const Quad1& orig);

    virtual ~Quad1()
    {
	delete a;
	delete b;
	delete c;
	delete d;
	delete texture;
    }

    //the draw function
    void draw(Shader* s, bool texIsThere = false);

    //calculate the normals
    void calculateNormals();

    // Getters and Setters
    //get the normals of the triangles
    
    vec3 getNormal_0()
    {
	return normal0;
    }

    vec3 getNormal_1()
    {
	return normal1;
    }

    //get the triangles
    Triangle* getTriangle0();
    Triangle* getTriangle1();

    //get the verticies
    Vertex* getV_a();// { return a; }
    Vertex* getV_b();// { return b; }
    Vertex* getV_c();// { return c; }
    Vertex* getV_d();// { return d; }

private:
    GLfloat verts[12]; //4 verticies * 3 attribus
    GLfloat colors[12];
    GLfloat normals[12];
    GLfloat texCoords[8]; //4 verticies * 2 attribus

    Texture* texture = NULL;

    GLuint quad1_VertexArrayObject;
    GLuint quad1_VertexBufferObject;

    // Colors
    vec3 fillColor;

    vec3 normal0;//normal of triangle 0
    vec3 normal1;//nomral of triangle 1

    //triangles
    Triangle* dreiangles[2];

    //hold all four verticies of the quad
    Vertex* a;
    Vertex* b;
    Vertex* c;
    Vertex* d;
};
#endif /* Quad1_h */
