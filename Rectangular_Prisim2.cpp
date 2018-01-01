/* 
 * File:   Rectangular_Prisim2.cpp
 * Suzuka/Emma
 * Created on October 4, 2017
 * code reulsed and repurposed from unit 7 ligthing using Cube
 * by stuetzlec's cube class by StuetzleC
 * Project 4
 * Shaila DiGiovanni & Emma Theberge
 */
#include "Rectangular_Prisim2.h"

Rectangular_Prisim2::Rectangular_Prisim2()
{
    assert(false&&"Do not use default Rectangular_Prisim2 constructor.");
}

//where _f is the bottom left cornner

Rectangular_Prisim2::Rectangular_Prisim2(vec3 _f, double _length, double _width, double _depth, vec3 fC, vec3 bC, Texture* tex)
{
    fillColor=fC;
    borderColor=bC;
    length=_length;
    width=_width;
    depth=_depth;
    texture=tex;
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
    ein=new Quad1(vertices[3], vertices[0], vertices[4], vertices[7], tex); //good this face faces you it's a face face off!

    zwei=new Quad1(vertices[7], vertices[4], vertices[5], vertices[6], tex); //good

    drei=new Quad1(vertices[6], vertices[5], vertices[1], vertices[2], tex); //good

    vier=new Quad1(vertices[2], vertices[1], vertices[0], vertices[3], tex); //good

    fuenf=new Quad1(vertices[2], vertices[3], vertices[7], vertices[6], tex); //top of the rectangular prisim,

    sechs=new Quad1(vertices[0], vertices[4], vertices[5], vertices[1], tex);

    float calcCenX=0;
    float calcCentY=0;
    float calcCentZ=0;
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

// Copy constructor is UNDER CONSTRUCTION (get it?!)

Rectangular_Prisim2::Rectangular_Prisim2(const Rectangular_Prisim2& orig)
{
    //still no not really ~ Suzuka
}

Rectangular_Prisim2::~Rectangular_Prisim2()
{
    // Delete triangles
    // Delete vertices
    delete ein;
    delete zwei;
    delete drei;
    delete vier;
    delete fuenf;
    delete sechs;
    delete texture;

}

// The drawing function
// Pre: None
// Post: The Rectangular_Prisim2 is drawn to the screen

void Rectangular_Prisim2::draw(Shader* s)
{
    ein->draw(s, true);
    zwei->draw(s, true);
    drei->draw(s, true);
    vier->draw(s, true);
    fuenf->draw(s, true);
    sechs->draw(s, true);
    /*
    printf("DRAWING RECTANGULAR PRISIM\n");
    // Draw each Quad1
    printf("\t\tein\n");
    ein->draw(s,true);
    printf("\t\tzwei\n");
    zwei->draw(s,true);
    printf("\t\tdrei\n");
    drei->draw(s,true);
    printf("\t\tvier\n");
    vier->draw(s,true);
    printf("\t\tfuenf\n");
    fuenf->draw(s,true);
    printf("\t\tsechs\n");
    sechs->draw(s,true);
    printf("ENDING DRAWING RECTANGULAR PRISIM\n\n");
     */
}

/*
vec3 rect_pris2_VertexArrayObject::getEyeDirection( Camera* c, int vertNum )
{
    assert( vertNum < 8 && vertNum >= 0 );
    return glm::normalize(c->getPosition() - vertices[vertNum]->getPos());
}
 * */
