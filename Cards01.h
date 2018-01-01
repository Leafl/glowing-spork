/* 
 * File:   Cards01.h
 * Author: Suzuka/ Emma
 *
 * Created on October 4, 2017
 *
 * Recycled and revised/editied/repurposed/reversed engineered
 * StuetzleC's Cube
 * Unit 7's lighting example
 * 
 *
 * Project 4
 * Shaila DiGiovanni & Emma Theberge
 */

#ifndef CARDS01_H
#define CARDS01_H

#include <GL/glew.h>


#include <string>
#include <stdio.h>
#include <iostream>
#include <glm/glm.hpp>

#include "DrawableObject.h"
#include "Texture.hpp"
#include "Vertex.hpp"
#include "Shader.hpp"
#include "Quad1.h"


using glm::vec3;
class Quad1;

class Cards01: public DrawableObject
{
public:
    //front being the face of the card

    //same as above but takes in a crest aka suit
    Cards01(vec3 _f, int val, string crest, vec3 fill, Texture* back, Texture* front, Texture* sides);

    vec3 getCenter()
    {
	return center;
    }

    void flipNormal(bool flippedup);//such that the face is facing up

    void printCenterCoords();

    Cards01(const Cards01& orig);
    void setNewCenter(vec3 neu);

    virtual ~Cards01();

    // The draw function
    void draw(Shader*);

    vec3 get_f()
    {
	return f;
    }

    void printCardsTitle();

    int getValue();//returns the value of the card

    string getSuit();//returns the suit of the card

    //vec3 getEyeDirection(Camera*, int vertNum = 0 );

private:
    vec3 f;

    //
    float calcCenX, calcCentY, calcCentZ;
    vec3 center;

    int value;
    string suit;

    Texture* topTexture = NULL;
    Texture* bottomTexture = NULL;
    Texture* side = NULL;

    Quad1* ein;
    Quad1* zwei;
    Quad1* drei;
    Quad1* vier;
    Quad1* fuenf;
    Quad1* sechs;

    Triangle* triangles[12];
    Vertex* vertices[8];


    //2.5" x 3.5"
    double length = 6.5;
    double width = 4.5;
    double depth = 0.25;

    // Colors
    vec3 fillColor;

    // Set up the vertex buffer object and vertex array object
    GLuint cards_VertexArrayObject;
    GLuint cards_VertexBufferObject;
};
#endif /* Cards01_H */

