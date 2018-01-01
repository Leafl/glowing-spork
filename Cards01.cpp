/* 
 * File:   Cards01.cpp
 * Author: Suzuka/ Emma
 * 
 * Created on October 4, 2017
 * code reulsed and repurposed from unit 7 ligthing using Cube
 * by stuetzlec's cube class
 * 
 * Project 4
 * Shaila DiGiovanni & Emma Theberge
 */

#include "Cards01.h"

/**
 * 
 * @param _f	    bottom left conner of the card
 * @param val	    value the card will have (2-14)
 * @param crest	    the suit (diamond, heart, spade, club)
 * @param fC	    the fill color
 * @param top	    The back of the card (the part of the playing
 *		    card that makes them look uniform)
 * @param bottom    The face of the card (the part of the playing
 *		    card that makes it different from the other
 *		    card in the same deck as it)
 * @param sides	    the texture for the sides of the cards. It
 *		    didn't like me leaving the cards sides to the
 *		    fill color by default it seemed to just take
 *		    the "default" texture and assigned it to the
 *		    side, or it took a color from the texture and
 *		    just painted the whole sides that color.
 * 
 * one line answer: it makes it look fancy!
 */
Cards01::Cards01(vec3 _f, int val, string crest, vec3 fC, Texture* top, Texture* bottom, Texture* sides)
{
    f=_f;
    fillColor=fC;
    topTexture=top;
    bottomTexture=bottom;
    side=sides;
    value=val;
    suit=crest;

    //f, e, g, h, b, c, d, a

    //f
    vertices[0]=new Vertex(_f, fC);
    vertices[0] -> setNormal(glm::normalize(vec3(-1, -1, -1)));

    //e
    vertices[1]=new Vertex(_f+vec3(length, 0.0, 0.0), fC);
    vertices[1] -> setNormal(glm::normalize(vec3(1, -1, -1)));

    //g
    vertices[2]=new Vertex(_f+vec3(length, depth, 0.0), fC);
    vertices[2] -> setNormal(glm::normalize(vec3(1, 1, -1)));

    //h
    vertices[3]=new Vertex(_f+vec3(0.0, depth, 0.0), fC);
    vertices[3] -> setNormal(glm::normalize(vec3(-1, 1, -1)));

    //b
    vertices[4]=new Vertex(_f+vec3(0.0, 0.0, width), fC);
    vertices[4] -> setNormal(glm::normalize(vec3(-1, -1, 1)));

    //c
    vertices[5]=new Vertex(_f+vec3(length, 0.0, width), fC);
    vertices[5] -> setNormal(glm::normalize(vec3(1, -1, 1)));

    //d
    vertices[6]=new Vertex(_f+vec3(length, depth, width), fC);
    vertices[6] -> setNormal(glm::normalize(vec3(1, 1, 1)));

    //a
    vertices[7]=new Vertex(_f+vec3(0.0, depth, width), fC);
    vertices[7] -> setNormal(glm::normalize(vec3(-1, 1, 1)));

    //f, e, g, h, b, c, d, a
    //0  1  2  3  4  5  6  7
    ein=new Quad1(vertices[3], vertices[0], vertices[4], vertices[7], side, vec3(-1.0, 0.0, 0.0)); //good

    zwei=new Quad1(vertices[7], vertices[4], vertices[5], vertices[6], side, vec3(0.0, 0.0, 1.0)); //good

    drei=new Quad1(vertices[6], vertices[5], vertices[1], vertices[2], side,vec3(1.0, 0.0, 0.0)); //good

    vier=new Quad1(vertices[2], vertices[1], vertices[0], vertices[3], side, vec3(0.0, 0.0, -1.0)); //good


    fuenf=new Quad1(vertices[2], vertices[3], vertices[7], vertices[6], bottomTexture,vec3(0.0, 1.0, 0.0)); //top of the rectangular prisim,


    sechs=new Quad1(vertices[5], vertices[4], vertices[0], vertices[1],topTexture,vec3(0.0, -1.0, 0.0));

    //calculate whtere teh center of the card is
    for(int v=0; v<6; v++)
    {
	calcCenX+=vertices[v]->getPos().x;
	calcCentY+=vertices[v]->getPos().y;
	calcCentZ+=vertices[v]->getPos().z;
    }
    calcCenX/=6;
    calcCentY/=6;
    calcCentZ/=6;

    center=vec3(calcCenX, calcCentY, calcCentZ);
}

/**
 * prints the cards full title: value of suit
 */
void Cards01::printCardsTitle()
{
    printf("card: %d of %s\n", value, suit.c_str());
}

/**
 * Stuetzle: Copy constructor is UNDER CONSTRUCTION (get it?!)
 * @param orig
 */
Cards01::Cards01(const Cards01& orig)
{
    //still no not really ~ Suzuka/Emma
}

/**
 * the deconstructor
 */
Cards01::~Cards01()
{
    // Delete triangles
    // Delete vertices
    delete ein;
    delete zwei;
    delete drei;
    delete vier;
    delete fuenf;
    delete sechs;
    delete topTexture;
    delete bottomTexture;
    delete side;
}

/**
 * The drawing function
 * 
 * @post: The Card01 is drawn to the screen
 * 
 * @param s	a shader that's passed in
 * 
 */
void Cards01::draw(Shader* s)
{
    // Draw each Quad1
    ein->draw(s, true);
    zwei->draw(s, true);
    drei->draw(s, true);
    vier->draw(s, true);
    fuenf->draw(s, true);
    sechs->draw(s, true);
}

/**
 * print the coordinates of the center 
 */
void Cards01::printCenterCoords()
{
    printf("Center:\n"
	   "\tX: %f\n"
	   "\tY: %f\n"
	   "\tZ: %f\n", center.x, center.y, center.z);
}

void Cards01::flipNormal(bool facUp)
{
    //fuenf->setNormal(vec3(0.0, 1.0, 0.0)); //top of the rectangular prisim


    //sechs->setNormal(vec3(0.0, -1.0, 0.0));
}

/**
 * @pre: value has been initalized (hopefully?)
 * 
 * @return  value
 */
int Cards01::getValue()
{
    return value;
}

/**
 * @pre: suit has been initalized (hopefully)
 * 
 * @return  suit
 */
string Cards01::getSuit()
{
    return suit;
}

void Cards01::setNewCenter(vec3 neu)
{
    center=neu;
}

/*
vec3 cards_VertexArrayObject::getEyeDirection( Camera* c, int vertNum )
{
    assert( vertNum < 8 && vertNum >= 0 );
    return glm::normalize(c->getPosition() - vertices[vertNum]->getPos());
}
 * */
