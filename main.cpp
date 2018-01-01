/*
 * File:   main.cpp
 * Author: Suzuka/Emma Theberge, Shaila DiGiovanni
 *
 * Date: October 30, 2017, 8:05 PM
 *
 * some code copied from:
 *	    https://github.com/SonarSystems/OpenGL-
 *	    Tutorials/blob/master/GLFW%20Mouse%20Input
 *	    /main.cpp
 *
 * Some code taken from and altered from:
 * _CSC5210_Unit4_PerspectiveCameraCode
 * SOme code also taken and repurposed from Unit 7 Lighting
 * Example class
 * 
 * face of cards textures retrieved from:
 * https://opengameart.org/content/playing-cards-1
 * 
 * for images that were not already PNGs I used
 * converted to PNG using: https://www.online-convert.com/result/b3ee3611-0731-44a4-aa2127105e9b7e9c
 * 
 * to convert them to be pngs
 * 
 * http://winnersedgetrading.com/wp-content/uploads/2013/03/fractal.jpg
 * converted as a png "fractal.png");
 * 
 * https://i.pinimg.com/736x/5c/d8/0f/5cd80fc19b4e40d3cbf5fcea8a4281c6--vintage-playing-cards-vintage-cards.jpg
 * back of the playing cards texture
 */

#include <GL/glew.h>

// User Includes
#define GLM_FORCE_RADIANS       // Necessary because GLM reasons
#include <cstdio>
#include <math.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "light/DirectionalLight.hpp"
#include "light/AmbientLight.hpp"
#include "Rectangular_Prisim2.h"
#include "light/PointLight.h"
#include "GLFWApplication.h"
#include "DeckofCards.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "Cards01.h"
#include "Camera.h"
#include "Quad1.h"

using std::endl;
using std::cerr;

// The current mouse position
double deltaX, deltaY;
bool lButtonDown;
vec2 mousePos;

float inverseX, inverseY, inverseZ;
float regularX, regularY, regularZ;

//serch paths for the thingys
string searchPath="/Volumes/NO NAME/College_2017-2018/CSC 5210 Computer Graphics/Projects/Project 4/v 02 Project 4 WAR…?/v 02 Project 4 WAR…?/";


glm::mat4 flipDiscardDeck;

glm::mat4 idenity; //will hold the idenity matrix

GLFWApplication newApplication;

// Window information
GLuint winHeight=800;
GLuint winWidth=1100;


bool testing=false;

//Shaders
Shader* mainShader;

// Lights!!!!
Light* ambLight;
Light* pLight;
//CAMERA!!!!
Camera* camera;

//TEXTURES!!!!
Texture* tableTexture;

//colors
vec3 white=vec3(1, 1, 1);
vec3 black=vec3(0, 0, 0);

//MediumWood found on: https://www.opengl.org/discussion_boards/showthread.php/132502-Color-tables
vec3 mediumWood=vec3(0.65, 0.50f, 0.39);
vec3 darkWood=vec3(0.52, 0.37, 0.26);

//3D models identifiers
Rectangular_Prisim2* testingTabletableTop;

Cards01* cardRemoved; //moves teh cards from one deck to another from the main deck/testing deck

DeckofCards* deckTesting;

//these are the decks the players take cards from
DeckofCards* p1_activeDeck;
DeckofCards* p2_activeDeck;

//cards that have been played recently
DeckofCards* p1_discardDeck;
DeckofCards* p2_discardDeck;

//the cards that are placed as part of the loop
DeckofCards* lootDeck;

//these are the cards that have a face face face off against eachother
Cards01* p1_activeCard; //vec3(30.25, 0, -27.75)
Cards01* p2_activeCard; //vec3(43.25, 0, -27.75)

int m=0;


//variables in in relation to game mechanics, in war? currently in war etc?
int phase=0;
int war=0;
bool ongoingWar=false;
bool winConditionMet=false;
bool first_turn=true;
int p1Val;
int p2Val;

/**
 * init
 * Initalizes:
 * Textures, Shapes/Geometry models, Camera, Shaders, and glEnable(something),
 * also what should be drawn to the screen
 */
void init()
{
    lootDeck=new DeckofCards(vec3(36.75, 0, -40), false);

    //vec3(36.75, 0, -27.75)
    deckTesting=new DeckofCards(vec3(36.75, 0, -27.75), true);
    printf("\n\n\n");

    p1_activeDeck=new DeckofCards(vec3(10.75, 0, -36.75), false);
    p2_activeDeck=new DeckofCards(vec3(62.75, 0, -36.75), false);

    p1_discardDeck=new DeckofCards(vec3(10.75, 0, -18), false);
    p2_discardDeck=new DeckofCards(vec3(62.75, 0, -18), false);

    //for images that were not already PNGs I used
    //converted to PNG using: https://www.online-convert.com/result/b3ee3611-0731-44a4-aa21-27105e9b7e9c
    //to convert them to be pngs

    //source https://burst.shopifycdn.com/photos/wooden-table-texture_4460x4460.jpg
    tableTexture=new Texture("/Volumes/NO NAME/College_2017-2018/CSC 5210 Computer Graphics/Projects/Project 4/v 02 Project 4 WAR…?/v 02 Project 4 WAR…?/wooden-table-texture_4460x4460.png");

    printf("table: %d\n", glIsTexture(tableTexture->getTexID()));
    testingTabletableTop=new Rectangular_Prisim2(
						 vec3(0, -30, -50), 80, 50, 30, mediumWood, darkWood, tableTexture);

    //Shader stuff
    string shaders[]=
    {
        searchPath+"verticespoint3.vert", searchPath+"fragmentspoint3.frag"
    };

    mainShader=new Shader(shaders, true);
    GLint conAttenID, linAttenID, quadAttenID;
    conAttenID = mainShader->GetVariable("ConstantAttenuation");
	linAttenID = mainShader->GetVariable("LinearAttenuation");
	quadAttenID = mainShader->GetVariable("QuadraticAttenuation");
	mainShader->SetFloat(conAttenID, 1.0);
	mainShader->SetFloat(linAttenID, 0.0014);
	mainShader->SetFloat(quadAttenID, 0.000007);
    /*
    GLint conAttenID, linAttenID, quadAttenID;
    conAttenID = mainShader->GetVariable("ConstantAttenuation");
    linAttenID = mainShader->GetVariable("LinearAttenuation");
    quadAttenID = mainShader->GetVariable("QuadraticAttenuation");
    mainShader->SetFloat(conAttenID, 1.0);
    mainShader->SetFloat(linAttenID, 0.0014);
    mainShader->SetFloat(quadAttenID, 0.000007);
    */


    //42.305695
    // Set up the camera, taken from class example
    vec3 pos(39.989990, 20, 20.000000);
    GLfloat FOV=45.0f;
    GLfloat nearPlane=0.1f;
    GLfloat farPlane=1000.0f;
    camera=new Camera(pos, winWidth, winHeight);
    camera -> setPerspective(FOV, (GLfloat) winWidth/(GLfloat) winHeight, nearPlane, farPlane);

    // Finally, tell the application object about the drawable objects
    newApplication.addDrawableObject(testingTabletableTop);
    
    for(int c=0; c<52; c++)
    {
	newApplication.addDrawableObject(deckTesting->getCardatindex(c));
    }
    
    for(int i=0; i<26; i++)
    {
	p1_activeDeck->addToPile(deckTesting->removeFromPile());
    }
    for(int i=26; i<52; i++)
    {
	p2_activeDeck->addToPile(deckTesting->removeFromPile());
    }

    // Set up the lights
    ambLight=new AmbientLight(vec3(0.9, 0.9, 1.0));
    //ambLight -> enable();

    //pointLight(vec3 col, vec3 pos, GLfloat st, GLfloat sh);
    pLight = new PointLight(vec3(0.9, 0.9, 0.7), vec3(40.0, 25.0, -25.0), 2.0, 1.0);
   //pLight = new PointLight(vec3(0.9, 0.9, 0.7),vec3(40.0, 50.0, -25.0),2.0,1.0);
    //pLight->enable();
    newApplication.addLight(ambLight);
    newApplication.addLight(pLight);
    ambLight -> toggle();


}//init end


//flip the active card over, determine who is the winner of the round


/**
 * @pre: both active cards has already been placed in the playing area
 * 
 * @post: cards flip over showing the face, and p1Val and p2Val get
 *		assigned appropriately
 */
void phase1()
{
    vec3 p1cardDisOrigin, p2cardDisOrigin;
    mat4 rotate180onXp1, rotate180onXp2;

    //move to the center
    p1cardDisOrigin=vec3(0, 0, 0)-p1_activeCard->getCenter();
    p1_activeCard->applyTransformation(translate(idenity, p1cardDisOrigin));
    
    p2cardDisOrigin=vec3(0, 0, 0)-p2_activeCard->getCenter();
    p2_activeCard->applyTransformation(translate(idenity, p2cardDisOrigin));
    
    //spin
    rotate180onXp1=glm::rotate(idenity, radians(180.0f), vec3(1.0f, 0.0f, 0.0f));
    p1_activeCard->applyTransformation(rotate180onXp1);
    p1_activeCard->applyTransformation(glm::translate(idenity, vec3(p1cardDisOrigin.x*-1, p1cardDisOrigin.y*-1, p1cardDisOrigin.z*-1)));

    rotate180onXp2=glm::rotate(idenity, radians(180.0f), vec3(1.0f, 0.0f, 0.0f));
    p2_activeCard->applyTransformation(rotate180onXp2);
    p2_activeCard->applyTransformation(glm::translate(idenity, vec3(p2cardDisOrigin.x*-1, p2cardDisOrigin.y*-1, p2cardDisOrigin.z*-1)));

    //flip cards
    p1Val=p1_activeCard->getValue();
    p2Val=p2_activeCard->getValue();
}

//remove a card from the active deck to the active card position, face down


/**
 * @pre: there are no currently active cards in the play area
 * 
 * @post: a card is drawn and placed face down in the play area
 */
void phase0()
{
    vec3 p2ActiveCenter=vec3(47.500000, 0.083333, -26.250000);
    vec3 p1ActiveCenter=vec3(32.500000, 0.083333, -26.250000);
    vec3 differenceP1;
    vec3 differenceP2;
    mat4 p1PlaceCard;
    mat4 p2PlaceCard;
    
    //remove the cards from the deck
    p1_activeCard=p1_activeDeck->removeFromPile();
    differenceP1=p1ActiveCenter-p1_activeCard->getCenter();
    p1PlaceCard=translate(idenity, differenceP1);
    p1_activeCard->applyTransformation(p1PlaceCard);

    p2_activeCard=p2_activeDeck->removeFromPile();
    differenceP2=p2ActiveCenter-p2_activeCard->getCenter();
    p2PlaceCard=translate(idenity, differenceP2);
    p2_activeCard->applyTransformation(p2PlaceCard);

    p1_activeCard->setNewCenter(p1ActiveCenter);
    p2_activeCard->setNewCenter(p2ActiveCenter);
}


/**
 * @pre:p1Val and p2Val have been set appropriately
 * 
 * @description
 *	execute phase1 again to reverse the flipping so the cards
 *	turn face down again. Checks to see if there is an ongoing
 *	war.
 * 
 *	ongoingWar == true: if someone won, then empty all the cards
 *	in the loot deck into the winners pile, adding both of the
 *	players cards to respective players discard deck, or if another
 *	war is initiated, put both of the players cards into the loot deck.
 * 
 *	ongoingWar==false: if someone won, then add the players active cards
 *	to the winners discard deck respectively, if a war initiates, then
 *	place both of the active cards into the loot deck.
 * 
 * @post: set ongoingWar respectively, phase =0, the active cards get placed
 *	   in the appropriate deck.
 *	
 */
void phase2()
{
    phase1();
    if(ongoingWar==true)
    {
	Cards01* cardPtr;
	//put the cards into the loot or winners pile
	if(p1Val>p2Val)//player 1 wins this war
	{
	    do
	    {
		cardPtr=lootDeck->removeFromPile();
		p1_discardDeck->addToPile(cardPtr);
	    }
	    while(lootDeck->isEmpty()==false);

	    p1_discardDeck->addToPile(p1_activeCard);
	    p1_discardDeck->addToPile(p2_activeCard);
	    ongoingWar=false;
	    phase=0;
	}
	else if(p1Val<p2Val)//player 2 wins the war
	{
	    do
	    {
		cardPtr=lootDeck->removeFromPile();
		p2_discardDeck->addToPile(cardPtr);
	    }
	    while(lootDeck->isEmpty()==false);

	    p2_discardDeck->addToPile(p1_activeCard);
	    p2_discardDeck->addToPile(p2_activeCard);
	    ongoingWar=false;
	    phase=0;
	}
	else if(p1Val==p2Val)//tie initiate another war
	{
	    lootDeck->addToPile(p1_activeCard);
	    lootDeck->addToPile(p2_activeCard);
	    ongoingWar=true;
	    phase=0;
	}
    }
    else if(ongoingWar==false)
    {
	if(p1Val>p2Val)
	{
	    p1_discardDeck->addToPile(p1_activeCard);
	    p1_discardDeck->addToPile(p2_activeCard);
	    phase=0;
	    ongoingWar=false;
	}
	else if(p1Val<p2Val)
	{
	    printf(" P2 wins this round!\n");
	    p2_discardDeck->addToPile(p1_activeCard);
	    p2_discardDeck->addToPile(p2_activeCard);
	    phase=0;
	    ongoingWar=false;
	}
	else if(p1Val==p2Val)
	{
	    ongoingWar=true;
	    lootDeck->addToPile(p1_activeCard);
	    lootDeck->addToPile(p2_activeCard);
	    phase=0;
	    printf("WAR\n\n");
	}
	war=0;
    }
    phase=0;

}

/**
 *
 * @param window
 * @param key = N
 * @param scancode
 * @param action
 * @param mode
 */
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(action==GLFW_PRESS)
    {
        if(key==GLFW_KEY_Q||key==GLFW_KEY_ESCAPE)
        {
            glfwSetWindowShouldClose(window, true);
        }
    }

    else if(action==GLFW_RELEASE)
    {
	if(key==GLFW_KEY_L)
	{
	    ambLight -> toggle();
	}
	if(key==GLFW_KEY_P)
	{
	    //dirLight -> toggle();
	    pLight->toggle();
	}
	if(key==GLFW_KEY_W)
	{
	    ((PointLight*) pLight)->moveLight(vec3(0.0, 0.0, -20.0));
	}
	if(key==GLFW_KEY_S)
	{
	    ((PointLight*) pLight)->moveLight(vec3(0.0, 0.0, 20.0));
	}
	if(key==GLFW_KEY_A)
	{
	    ((PointLight*) pLight)->moveLight(vec3(-20.0, 0.0, 0.0));
	}
	if(key==GLFW_KEY_D)
	{
	    ((PointLight*) pLight)->moveLight(vec3(20.0, 0.0, 0.0));
	}
	if(key==GLFW_KEY_N)
	{
	    //both players draw a new card from their draw deck
	    //if draw deck for either one of the players is empty shuffle their discard deck,
	    //put discard deck to be draw deck
	    //draw deck is empty

	    //play turn normally

	    if(winConditionMet==false)
	    {
		if(p1_activeDeck->getSize()==0)
		{
		    if(p1_discardDeck->getSize()==0)
		    {
			printf("PLAYER 2 WINS!!!!");
			winConditionMet=true;
		    }
		    else
		    {
			p1_discardDeck->shuffle();
			do
			{
			    p1_activeDeck->addToPile(p1_discardDeck->removeFromPile());
			}
			while(p1_discardDeck->isEmpty()==false);
			p1_activeDeck->shuffle();
		    }
		}
		if(p2_activeDeck->getSize()==0)
		{
		    if(p2_discardDeck->getSize()==0)
		    {
			printf("PLAYER 1 WINS!!!!");
			winConditionMet=true;
		    }
		    else
		    {
			p2_discardDeck->shuffle();
			do
			{
			    p2_activeDeck->addToPile(p2_discardDeck->removeFromPile());
			}
			while(p2_discardDeck->isEmpty()==false);
			p2_activeDeck->shuffle();
		    }
		}
		if(ongoingWar==true)//there's an on going war
		{
		    if(war==0)
		    {
			if(phase==0)
			{
			    phase0();
			    phase=2;
			}
			else if(phase==2)
			{
			    //both cards get added to loot deck
			    lootDeck->addToPile(p1_activeCard);
			    lootDeck->addToPile(p2_activeCard);
			    war++;
			    phase=0;
			}
		    }
		    else if(war==1)
		    {
			if(phase==0)
			{
			    printf("A\n");
			    phase0();
			    phase=2;
			}
			else if(phase==2)
			{
			    //both cards get added to loot deck
			    lootDeck->addToPile(p1_activeCard);
			    lootDeck->addToPile(p2_activeCard);
			    war++;
			    phase=0;
			}
		    }
		    else if(war==2)
		    {
			if(phase==0)
			{
			    printf("R\n");
			    phase0();
			    phase=2;
			}
			else if(phase==2)
			{
			    //both cards get added to loot deck
			    lootDeck->addToPile(p1_activeCard);
			    lootDeck->addToPile(p2_activeCard);
			    war++;
			    phase=0;
			}

		    }
		    else if(war==3)
		    {
			if(phase==0)
			{
			    printf("WAR!!!!\n");
			    phase0();
			    ongoingWar=true;
			    phase=1;
			}
			else if(phase==1)//flip and determine who wins
			{
			    phase1();
			    phase=2;
			}
			else if(phase==2)//who wins the war
			{
			    ongoingWar=true;
			    phase2();
			    war=0;
			    phase=0;
			}
		    }
		}
		    //normal turns
		else if(phase==1)
		{
		    //rotate
		    phase1();
		    phase=2;
		}

		else if(phase==2)//determine who wins
		{
		    phase2();
		    phase=0;
		}
		else if(phase==0&&ongoingWar==false)
		{
		    phase0();
		    phase=1;
		}
	    }
	}

	if(true)
	{
	    switch(key)
	    {

		case GLFW_KEY_I:
		{
		    camera->setPosition(vec3(40, 80, -25.000000));
		}
		    break;
		case GLFW_KEY_PERIOD:
		{
		    camera->moveCamera(-10, 0);
		}
		    break;
		case GLFW_KEY_COMMA:
		{
		    camera->moveCamera(+10, 0);
		}
		    break;

		case GLFW_KEY_UP:
		{//move camera up
		    camera->moveCamera(0, 10);
		}
		    break;
		case GLFW_KEY_DOWN:
		{//move camera down
		    camera->moveCamera(0, -10);
		}
		    break;
		case GLFW_KEY_LEFT:
		{
		    vec3 moreZ=vec3(camera->getPosition().x, camera->getPosition().y, 10+camera->getPosition().z);
		    camera->setPosition(moreZ);
		}
		    break;
		case GLFW_KEY_TAB:
		{
		    camera->printOutYawandPitch();
		}
		    break;
		case GLFW_KEY_RIGHT:
		{
		    vec3 lessz=vec3(camera->getPosition().x, camera->getPosition().y, camera->getPosition().z-10);
		    camera->setPosition(lessz);

		}
		    break;
	    }
	}
    }
}

// When a mouse button is clicked, change the state of the "left" and "right"
//   buttons to being held down (when pressed) or not (when released).

void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(button==GLFW_MOUSE_BUTTON_LEFT)
    {
	if(GLFW_PRESS==action)
	    lButtonDown=true;

	else if(GLFW_RELEASE==action)
	    lButtonDown=false;
    }
}

// Update the mouse position (and the change in the position from the
//   previous update) in here.

void mouse_motion_callback(GLFWwindow* window, double mX, double mY)
{
    deltaX=mousePos.x-mX;
    deltaY=mousePos.y-mY;
    mousePos.x=mX;
    mousePos.y=mY;

    if(lButtonDown)
    {
	//printf("left\n");
	camera -> setViewByMouse(deltaX, deltaY);
    }
}

/*
 * glfw: whenever the window size changed (by OS or user resize)
 * this callback function executes
 */

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    /*
     * make sure the viewport matches the new window dimensions;
     * note that width and
     * height will be significantly larger than specified on
     * retina displays.
     */
    glViewport(0, 0, width, height);
}

/**
 * taken from lighting example unit 7
 */
int main()
{
    // Set up the GLFW application
    //anti aliasing level
    //minor version (Opengl)
    //major version (Opengl)
    //window title
    //window width
    //window height
    newApplication.initializeApplication(8, 3, 3,
					 "v 00 Project 4 War?",
					 winWidth, winHeight);

    // Assign your callback functions (the ones you write) to the internal
    //   callbacks of the application class.

    newApplication.setKeyCallback(key_callback);
    newApplication.setMouseClickCallback(mouse_callback);
    newApplication.setMouseMotionCallback(mouse_motion_callback);

    newApplication.initializeCallbacks();
    // Initialize stuff local to the program
    init();
    newApplication.setShader(mainShader);
    newApplication.setCamera(camera);

    // Tell the application to "go"
    newApplication.initiateDrawLoop();

    return 0;
}
