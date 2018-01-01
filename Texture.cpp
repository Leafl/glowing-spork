#include "Texture.hpp"

Texture::Texture(string filename)
{
    string fileExtension=filename.substr(filename.find_last_of(".")+1);

    std::vector<unsigned char> image; //the raw pixels
    unsigned width, height;
    if(fileExtension=="png")
    {
	//decode
	unsigned error=lodepng::decode(image, width, height, filename);

	//if there's an error, display it
	if(error) cerr<<"decoder error "<<error<<": "<<lodepng_error_text(error)<<endl;

	imageWidth=(int) width;
	imageHeight=(int) height;
	imagedata=new GLubyte[ (int) image.size() ];
	for(int i=0; i<image.size(); i++)
	{
	    imagedata[i]=image[i];
	}

	// Create and bind the texture.
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imagedata);
	// Only 1 image, so set these texture parameters to avoid issues with levels
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    }
}

// Getters

GLsizei Texture::getImageHeight()
{
    return imageHeight;
}

GLsizei Texture::getImageWidth()
{
    return imageWidth;
}

GLubyte* Texture::getData()
{
    return imagedata;
}

GLuint Texture::getTexID()
{
    return texID;
}
