/*
 * Much of this code was taken from opengl-tutorial.com
 * Author of the rest: Christopher Stuetzle (2017)
 */

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <cstdlib>
#include <string>
#include <iostream>
#include <GL/glew.h>

// The image loaders
#include "lodepng.h"

using std::string;
using std::cerr;
using std::endl;

class Texture
{
public:
    // Constructors
    Texture(string);
    Texture(Texture&);

    static const int PNG_FILE = 1;

    GLsizei getImageHeight();
    GLsizei getImageWidth();
    GLubyte* getData();
    GLuint getTexID();

private:
    GLsizei imageHeight;
    GLsizei imageWidth;

    GLubyte* imagedata;//data uploaded into the texture changed the identifier name cause data is not very specific
    GLuint texID;
};



#endif
