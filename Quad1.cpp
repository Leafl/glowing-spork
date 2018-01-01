/*
 * File:   Quad1.cpp
 * Project FINAL
 * some code may be copied and altered from
 * Triangle
 *
 * Quad1 -- uses triangle fan (such that point a is the
 * centeral point and all other verticies have one edge
 * steming from vertex a
 *
 * code repurposed from unit 7 ligthing using Triangle by
 * StuetzleC
 * Project 4
 * Shaila DiGiovanni & Emma Theberge
 */

#include "Quad1.h"

Quad1::Quad1(Vertex* _a, Vertex* _b, Vertex* _c, Vertex* _d, Texture* tex, vec3 normal)
{
    //printf("using: Quad1::Quad1(Vertex* _a, Vertex* _b, Vertex* _c, Vertex* _d, Texture* tex)\n\n");
    a=_a;
    b=_b;
    c=_c;
    d=_d;

    texture=tex;

    a->setTexCoord(vec2(0.0f, 0.0f));
    b->setTexCoord(vec2(0.0f, 1.0f));
    c->setTexCoord(vec2(1.0f, 1.0f));
    d->setTexCoord(vec2(1.0f, 0.0f));

    dreiangles[0]=new Triangle(a, b, c);
    a->addTriangle(dreiangles[0]);
    b->addTriangle(dreiangles[0]);
    c->addTriangle(dreiangles[0]);

    dreiangles[1]=new Triangle(a, c, d);
    a->addTriangle(dreiangles[1]);
    c->addTriangle(dreiangles[1]);
    d->addTriangle(dreiangles[1]);

    for(int i=0; i<2; i++)
    {
	dreiangles[i]->calculateNormal();
    }
    calculateNormals();
/*
    GLfloat verts[12]; //4 verticies * 3 attribus
    GLfloat colors[12];
    GLfloat normals[12];
    GLfloat texCoords[8]; //4 verticies * 2 attribus
 */

    //verts!
    verts[0]=a->getPos().x;
    verts[1]=a->getPos().y;
    verts[2]=a->getPos().z;

    verts[3]=b->getPos().x;
    verts[4]=b->getPos().y;
    verts[5]=b->getPos().z;

    verts[6]=c->getPos().x;
    verts[7]=c->getPos().y;
    verts[8]=c->getPos().z;

    verts[9]=d->getPos().x;
    verts[10]=d->getPos().y;
    verts[11]=d->getPos().z;

    //colors!
    colors[0]=a->getColor().r;
    colors[1]=a->getColor().g;
    colors[2]=a->getColor().b;

    colors[3]=b->getColor().r;
    colors[4]=b->getColor().g;
    colors[5]=b->getColor().b;

    colors[6]=c->getColor().r;
    colors[7]=c->getColor().g;
    colors[8]=c->getColor().b;

    colors[9]=d->getColor().r;
    colors[10]=d->getColor().g;
    colors[11]=d->getColor().b;

    int i = 0;
    while(i < 12)
    {
	normals[i++] = normal.x;
	normals[i++] = normal.y;
	normals[i++] = normal.z;
    }


    //texCoords!
    texCoords[0]=0.000000;
    texCoords[1]=0.000000;
    texCoords[2]=0.000000;
    texCoords[3]=1.000000;
    texCoords[4]=1.000000;
    texCoords[5]=1.000000;
    texCoords[6]=1.000000;
    texCoords[7]=0.000000;

    
    //quad1_VertexBufferObject
    //set up the vertex array obj and vertex buff
    glGenVertexArrays(1, &quad1_VertexArrayObject);
    glGenBuffers(1, &quad1_VertexBufferObject);

    glBindVertexArray(quad1_VertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, quad1_VertexBufferObject);

    // Populate with the data
    glBufferData(GL_ARRAY_BUFFER,
		 sizeof(verts)+sizeof(colors)+sizeof(normals)+sizeof(texCoords), NULL, GL_STATIC_DRAW);

    //verts
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);

    //colors
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(verts), sizeof(colors), colors);

    //normals
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(verts)+sizeof(colors),
		    sizeof(normals), normals);

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(verts)+sizeof(colors)+sizeof(normals),
		    sizeof(texCoords), texCoords);


    // Set up the attribute array with two attributes, which will point to respectively where each sub buffer data is stored
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //verts

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) sizeof(verts)); //colors
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*) (sizeof(verts)+sizeof(colors))); //normals

    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (void*) (sizeof(verts)+sizeof(colors)+sizeof(normals))); //tex coords

    //enable the vertex attrib arrays
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
}

Quad1::Quad1(Vertex* _a, Vertex* _b, Vertex* _c, Vertex* _d, Texture* tex)
{
    a=_a;
    b=_b;
    c=_c;
    d=_d;

    texture=tex;

    a->setTexCoord(vec2(0.0f, 0.0f));
    b->setTexCoord(vec2(0.0f, 1.0f));
    c->setTexCoord(vec2(1.0f, 1.0f));
    d->setTexCoord(vec2(1.0f, 0.0f));

    dreiangles[0]=new Triangle(a, b, c);
    a->addTriangle(dreiangles[0]);
    b->addTriangle(dreiangles[0]);
    c->addTriangle(dreiangles[0]);

    dreiangles[1]=new Triangle(a, c, d);
    a->addTriangle(dreiangles[1]);
    c->addTriangle(dreiangles[1]);
    d->addTriangle(dreiangles[1]);

    for(int i=0; i<2; i++)
    {
	dreiangles[i]->calculateNormal();
    }
    calculateNormals();

    GLfloat verts[12]; //4 verticies * 3 attribus
    GLfloat colors[12];
    GLfloat normals[12];
    GLfloat texCoords[8]; //4 verticies * 2 attribus

    //verts!
    verts[0]=a->getPos().x;
    verts[1]=a->getPos().y;
    verts[2]=a->getPos().z;

    verts[3]=b->getPos().x;
    verts[4]=b->getPos().y;
    verts[5]=b->getPos().z;

    verts[6]=c->getPos().x;
    verts[7]=c->getPos().y;
    verts[8]=c->getPos().z;

    verts[9]=d->getPos().x;
    verts[10]=d->getPos().y;
    verts[11]=d->getPos().z;

    //colors!
    colors[0]=a->getColor().r;
    colors[1]=a->getColor().g;
    colors[2]=a->getColor().b;

    colors[3]=b->getColor().r;
    colors[4]=b->getColor().g;
    colors[5]=b->getColor().b;

    colors[6]=c->getColor().r;
    colors[7]=c->getColor().g;
    colors[8]=c->getColor().b;

    colors[9]=d->getColor().r;
    colors[10]=d->getColor().g;
    colors[11]=d->getColor().b;

    //normals!
    normals[0]=a->getNormal().x;
    normals[1]=a->getNormal().y;
    normals[2]=a->getNormal().z;

    normals[3]=b->getNormal().x;
    normals[4]=b->getNormal().y;
    normals[5]=b->getNormal().z;

    normals[6]=c->getNormal().x;
    normals[7]=c->getNormal().y;
    normals[8]=c->getNormal().z;

    normals[9]=d->getNormal().x;
    normals[10]=d->getNormal().y;
    normals[11]=d->getNormal().z;


    //texCoords!
    texCoords[0]=0.000000;
    texCoords[1]=0.000000;
    texCoords[2]=0.000000;
    texCoords[3]=1.000000;
    texCoords[4]=1.000000;
    texCoords[5]=1.000000;
    texCoords[6]=1.000000;
    texCoords[7]=0.000000;

    //quad1_VertexBufferObject
    //set up the vertex array obj and vertex buff
    glGenVertexArrays(1, &quad1_VertexArrayObject);
    glGenBuffers(1, &quad1_VertexBufferObject);

    glBindVertexArray(quad1_VertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, quad1_VertexBufferObject);

    // Populate with the data
    glBufferData(GL_ARRAY_BUFFER,
		 sizeof(verts)+sizeof(colors)+sizeof(normals)+sizeof(texCoords), NULL, GL_STATIC_DRAW);

    //verts
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);

    //colors
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(verts), sizeof(colors), colors);

    //normals
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(verts)+sizeof(colors),
		    sizeof(normals), normals);

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(verts)+sizeof(colors)+sizeof(normals),
		    sizeof(texCoords), texCoords);


    // Set up the attribute array with two attributes, which will point to respectively where each sub buffer data is stored
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //verts

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) sizeof(verts)); //colors
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*) (sizeof(verts)+sizeof(colors))); //normals

    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (void*) (sizeof(verts)+sizeof(colors)+sizeof(normals))); //tex coords

    //enable the vertex attrib arrays
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
}

void Quad1::draw(Shader *s, bool hasTexture)
{
    glBindVertexArray(quad1_VertexArrayObject);
    s->useProgram();
    if(texture==NULL)
    {
	hasTexture=false;
    }

    GLint c=s -> GetVariable("color");
    if(hasTexture)
    {
	glBindTexture(GL_TEXTURE_2D, texture->getTexID());
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }
    else
    {
	s->useProgram();
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }
    glBindVertexArray(0);
}

void Quad1::calculateNormals()
{
    dreiangles[0]->calculateNormal();
    normal0=dreiangles[0]->getNormal();
    dreiangles[1]->calculateNormal();
    normal1=dreiangles[1]->getNormal();
}

Triangle* Quad1::getTriangle0()
{
    return dreiangles[0];
}

Triangle* Quad1::getTriangle1()
{
    return dreiangles[1];
}

Vertex* Quad1::getV_a()
{
    return a;
}

Vertex* Quad1::getV_b()
{
    return b;
}

Vertex* Quad1::getV_c()
{
    return c;
}

Vertex* Quad1::getV_d()
{
    return d;
}

