/*
 * File:   GLFWApplication.cpp
 * Author: stuetzlec
 *
 * Suzuka/Emma
 * Created on October 4, 2017
 * code reulsed and repurposed from unit 7 ligthing
 *
 * Project 4
 * Shaila DiGiovanni & Emma Theberge
 */

#include "GLFWApplication.h"

GLFWApplication::GLFWApplication()
{

}

GLFWApplication::GLFWApplication(const GLFWApplication& orig)
{

}

GLFWApplication::~GLFWApplication()
{
}

int GLFWApplication::initializeApplication(int aaValue, // anti-aliasing level
					   int minorVersion, // OpenGL version
					   int majorVersion,
					   string winTitle, // The title of the window
					   int winWidth, // Width and height of the window
					   int winHeight,
					   vec3 cC // The color to clear the screen to
					   )
{
    // Initialize GLFW3
    if(!glfwInit())
    {
        cerr<<"Failed to initialize GLFW\n"<<endl;
        return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, aaValue); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

    // Create the window
    window=glfwCreateWindow(winWidth, winHeight, winTitle.c_str(), NULL, NULL);
    if(window==NULL)
    {
        cerr<<"Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n"<<endl;
        glfwTerminate();
	return -1;
    }
    // Need to make the window the "current context" before we use GLEW
    glfwMakeContextCurrent(window); // Initialize GLEW

    // To be safe, we’re using glew’s experimental stuff.
    glewExperimental=GL_TRUE;
    // Initialize and error check GLEW
    GLenum err=glewInit();
    if(GLEW_OK!=err)
    {
        // If something went wrong, print the error message
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    //found on:
https://www.opengl.org/discussion_boards/showthread.php/132502-Color-tables
    //#declare SkyBlue = color red 0.196078 green 0.6 blue 0.8
    cC=vec3(0.196078, 0.6, 0.8);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0f);
    glClearColor(cC.r, cC.g, cC.b, 1.0);

    // Initialize the time
    glfwSetTime(0.0);
    curTime=glfwGetTime();
    return 1;
}

void GLFWApplication::initiateDrawLoop()
{
    while(!glfwWindowShouldClose(window))
    {
        draw();
    }
}

void GLFWApplication::draw()
{
    // Now, set the "delta time"
    double dt=glfwGetTime()-curTime;
    curTime=glfwGetTime();

    camera -> setDeltaTime(dt);

    // Clears the given framebuffer (in this case, color)
    // Could set color to clear to with glClearColor, default is black
    // Also clears the depth buffer, IMPORTANT because we're now in 3D
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // Update the camera
    //bits and pieces below altered and added by Shaila
    /*
    mat4 projectionMatrix = camera -> getPerspectiveMatrix();
    mat4 viewMatrix = camera -> getViewMatrix();
    mat4 modelMatrix;
    mat4 PVMMatrix;
    mat4 VMMatrix;
    mat4 normalMatrix; // Needed for the normals
    mat4 ViewMatrix;
    GLint viewMid;
    GLint PVMid;
    GLint VMid;
    GLint NMid;
    GLint EyePositionid;
     */
        // Update the camera
    mat4 projectionMatrix = camera -> getPerspectiveMatrix();
    mat4 viewMatrix = camera -> getViewMatrix();
    mat4 modelMatrix;
    mat4 PVMMatrix;
    mat4 VMMatrix; // Needed for the normals
    mat4 normalMatrix; // Needed for the normals
                       //mat4 ViewMatrix;
    GLint viewMid;
    GLint PMid;
    GLint VMid;
    GLint MMid;
    GLint NMid;
    GLint EyePositionid;

    // Setup the lights
    EyePositionid=shader -> GetVariable("EyePosition");
    shader -> SetVector3(EyePositionid, 1, &(camera->getPosition()[0]));
    for(int j=0; j<lights.size(); j++)
    {
        // Connect the light to the shader
        lights[j] -> connectLightToShader(shader);
    }

    // Draw everything
    for(int i=0; i<drawables.size(); i++)
    {
        if(drawables[i])
        {
            modelMatrix = drawables[i]->getModelMatrix();//MMid
			MMid = shader->GetVariable("model");
			shader->SetMatrix4(MMid, 1, false, &modelMatrix[0][0]);
			// Calculate the matrices
			normalMatrix = transpose(inverse(modelMatrix));
			NMid = shader->GetVariable("MNormal");
			shader->SetMatrix3(NMid, 1, false, &normalMatrix[0][0]);
			// Connect the matrices to the shader
			PMid = shader->GetVariable("projection");
			shader->SetMatrix4(PMid, 1, false, &projectionMatrix[0][0]);
			
			viewMid = shader->GetVariable("view");
			shader->SetMatrix4(viewMid, 1, false, &viewMatrix[0][0]);
			
			
			drawables[i]->draw(shader);
            /*
                modelMatrix = drawables[i] -> getModelMatrix();
                // Calculate the matrices
                PVMMatrix = projectionMatrix * viewMatrix * modelMatrix;
                VMMatrix = viewMatrix * modelMatrix;
                normalMatrix = transpose(inverse(VMMatrix));
                // Connect the matrices to the shader
                PVMid = shader -> GetVariable("PVMMatrix");
                VMid = shader -> GetVariable("VMMatrix");//VMMatrix
                NMid = shader->GetVariable("NormalMatrix");//VMMatrix
                viewMid = shader->GetVariable("ViewMatrix");//VMMatrix
                shader->SetMatrix4(viewMid, 1, false, &ViewMatrix[0][0]);
                shader -> SetMatrix4(PVMid, 1, false, &PVMMatrix[0][0]);
                shader -> SetMatrix3(VMid, 1, false, &VMMatrix[0][0]);
                shader->SetMatrix3(NMid, 1, false, &normalMatrix[0][0]);
                drawables[i] -> draw(shader);
            //some code in loop modified by Shalia
             */
        }
    }

    // Force OpenGL commands to begin execution
    glfwSwapBuffers(window);
    glfwPollEvents();
}


// Set up the internal callbacks

void GLFWApplication::initializeCallbacks()
{
    //frame_buffer_size_callback was added by Emma Theberge
    //found it in some code in early class room examples
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    //Setup the 'input mode'
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Set up the callbacks
    glfwSetKeyCallback(window, keyFunc);

    // Mouse input callback would be here:
    glfwSetMouseButtonCallback(window, clickFunc);

    // When the cursor moves
    glfwSetCursorPosCallback(window, mouseMoveFunc);
}

// Add a drawable object to the class

void GLFWApplication::addDrawableObject(DrawableObject* o)
{
    drawables.push_back(o);
}

// Add a Light object to the list of lights

void GLFWApplication::addLight(Light* o)
{
    lights.push_back(o);
}

