/*
 * File:   DeckofCards.cpp
 * Author: Suzuka/Emma Theberge
 *
 * Date: November 8, 2017, 3:44 PM
 * 
 * Project 4
 * Shaila DiGiovanni & Emma Theberge
 */

#include "DeckofCards.hpp"

DeckofCards::DeckofCards()
{
    assert(false&&"Do not use default DECK OF CARDS constructor.");
}

/**
 *
 * @param botLefbck takes in a vec3 for the
 *	  the position of where the bottom
 *	  left conner of the deck should be
 *	  placed
 *
 * @param main is this the main deck? (the deck
 *	  that initalizes all 52 cards in the deck)
 */
DeckofCards::DeckofCards(vec3 botLefbck, bool main)
{
    vec3 white=vec3(1, 1, 1);
    bottomLeftBack=botLefbck;
    isMainDeck=main;
    whereFirstCardWouldBe[0]=vec3(bottomLeftBack);

    //e
    whereFirstCardWouldBe[1]=vec3(bottomLeftBack+vec3(length, 0.0, 0.0));

    //g
    whereFirstCardWouldBe[2]=vec3(bottomLeftBack+vec3(length, cardDepth, 0.0));
    //h
    whereFirstCardWouldBe[3]=vec3(bottomLeftBack+vec3(0.0, cardDepth, 0.0));

    //b
    whereFirstCardWouldBe[4]=vec3(bottomLeftBack+vec3(0.0, 0.0, width));

    //c
    whereFirstCardWouldBe[5]=vec3(bottomLeftBack+vec3(length, 0.0, width));

    //d
    whereFirstCardWouldBe[6]=vec3(bottomLeftBack+vec3(length, cardDepth, width));

    //a
    whereFirstCardWouldBe[7]=vec3(bottomLeftBack+vec3(0.0, cardDepth, width));

    vec3 sum=vec3(0, 0, 0);
    for(int wo=0; wo<8; wo++)
    {
	sum+=whereFirstCardWouldBe[wo];
    }
    center=vec3(sum.x/8, sum.y/8, sum.z/8);

    if(main==true)
    {
	string cardSearchPath="/Volumes/NO NAME/College_2017-2018/CSC"
		" 5210 Computer Graphics/Projects/Project 4/v 02 Project"
		" 4 WAR…?/v 02 Project 4 WAR…?/Cards/";
	Texture*cardTextures[54];
	for(int i=0; i<54; i++)//for textures
	{
	    switch(i)
	    {
		case 52:
		{//side of the card
		    cardTextures[i]=new Texture(cardSearchPath+
					    "fractal.png");
		    printf("side: %d\n", glIsTexture(cardTextures[i]->getTexID()));
		}
		    break;
		case 53:
		{//back of the card
		    cardTextures[i]=new Texture(cardSearchPath+
					    "5cd80fc19b4e40d3cbf5fcea8a4281c6--vintage-playing-.png");
		}
		    break;
		default:
		{
		    cardTextures[i]=new Texture(cardSearchPath+std::to_string(i+1)+".png");
		}
		    break;
	    }

	}
	//now initializing the cards
	Cards01* cardPtr;
	numCards_inDeck=52;
	int cardCount=0;
	double yVal=0;
	string crest="";
	for(int s=0; s<4; s++)
	{
	    //suit 0 spades
	    //suit 1 clubs
	    //suit 2 diamonds
	    //suit 3 hearts
	    switch(s)
	    {
		case 0:
		{
		    crest="Spades";
		    //printf("Spades\n");
		}
		    break;
		case 1:
		{
		    crest="Clubs";
		    //printf("Clubs\n");
		}
		    break;
		case 2:
		{
		    crest="Diamonds";
		    //printf("Diamonds\n");
		}
		    break;
		case 3:
		{
		    crest="Hearts";
		    //printf("Hearts\n");
		}
		    break;
	    }
	    for(int v=2; v<15; v++)
	    {
		//cardTexture[52] side
		//cardTexture[53] back
		//Cards01(vec3 _f,int val, string crest,vec3 fill, Texture* back, Texture* front, Texture* sides);
		//front being the face of the card
		cardPtr=new Cards01(vec3(bottomLeftBack.x, yVal, bottomLeftBack.z), v, crest, white,cardTextures[cardCount], cardTextures[53], cardTextures[52]);

		pileofCards[cardCount]=cardPtr;
		//printf("\n");
		yVal+=0.25;
		cardCount++;
	    }
	}
	topCard=pileofCards[51];
	shuffle();
	shuffle();
    }
    else
    {
	numCards_inDeck=0;
    }
}

/**
 * USED FOR TESTING
 * @param botLefbck takes in a vec3 for the
 *	  the position of where the bottom
 *	  left conner of the deck should be
 *	  placed
 *
 * @param main is this the main deck? (the deck
 *	  that initalizes all 52 cards in the deck)
 */
DeckofCards::DeckofCards(vec3 botLefbck, bool main, int num)
{
    vec3 white=vec3(1, 1, 1);
    bottomLeftBack=botLefbck;
    isMainDeck=main;
    numCards_inDeck=num;
    if(main==true)
    {
	string cardSearchPath="/Volumes/NO NAME/College_2017-2018/CSC 5210 Computer Graphics/Projects/Project 4/v 02 Project 4 WAR…?/v 02 Project 4 WAR…?/Cards/";
	Texture*cardTextures[54];
	for(int i=0; i<54; i++)//for textures
	{
	    switch(i)
	    {
		case 52:
		{//side of the card
		    cardTextures[i]=new Texture(cardSearchPath+
					    "fractal.png");
		    printf("side: %d\n", glIsTexture(cardTextures[i]->getTexID()));
		}
		    break;
		case 53:
		{//back of the card
		    cardTextures[i]=new Texture(cardSearchPath+
					    "5cd80fc19b4e40d3cbf5fcea8a4281c6--vintage-playing-.png");
		}
		    break;
		default:
		{
		    cardTextures[i]=new Texture(cardSearchPath+std::to_string(i)+".png");
		}
		    break;
	    }

	}
	//now initializing the cards
	Cards01* cardPtr;
	int cardCount=0;
	double yVal=0;
	string crest="";
	for(int s=0; s<4&&cardCount<numCards_inDeck; s++)
	{
	    //suit 0 spades
	    //suit 1 clubs
	    //suit 2 diamonds
	    //suit 3 hearts
	    switch(s)
	    {
		case 0:
		{
		    crest="Spades";
		}
		    break;
		case 1:
		{
		    crest="Clubs";
		}
		    break;
		case 2:
		{
		    crest="Diamonds";
		}
		    break;
		case 3:
		{
		    crest="Hearts";
		}
		    break;
	    }
	    for(int v=2; v<15&&cardCount<numCards_inDeck; v++)
	    {
		//cardTexture[52] side
		//cardTexture[53] back
		//Cards01(vec3 _f,int val, string crest,vec3 fill, Texture* back, Texture* front, Texture* sides);
		//front being the face of the card
		cardPtr=new Cards01(vec3(bottomLeftBack.x, yVal, bottomLeftBack.z), v, crest, white, cardTextures[53], cardTextures[cardCount], cardTextures[52]);

		pileofCards[cardCount]=cardPtr;
		//printf("\n");
		yVal+=0.25;
		cardCount++;
	    }
	}
	for(int i=cardCount; i<52; i++)
	{
	    pileofCards[i]=NULL;
	}
	/*
	printf("bottom card coords: \n"
	"\tX: %f\n"
	"\tY: %f\n"
	"\tZ: %f\n", pileofCards[0]->getCenter().x, pileofCards[0]->getCenter().y, pileofCards[0]->getCenter().z);
	topCard=pileofCards[numCards_inDeck-1];
	*/
	shuffle();
    }
    else
    {
	numCards_inDeck=0;
    }
}

/**
 * 
 * @return
 *	    true if getSize ==0
 *	    false if getSize > 0
 */
bool DeckofCards::isEmpty()
{
    if(numCards_inDeck==0)
    {
	return true;
    }
    else
	return false;
}

/**
 * prints out the value and suit of the cards in the
 * deck
 */
void DeckofCards::printDeck()
{
    if(isEmpty()==true)
    {
	printf("This deck is currently empty\n");
    }
    else
    {
    /*
	printf("Printing Deck of cards:\n");
	for(int i=0; i<numCards_inDeck; i++)
	{
	    printf("[%d]\t\tcard: %d of %s\n",
	    i, pileofCards[i]->getValue(),
	    pileofCards[i]->getSuit().c_str());
	}
	*/
    }
}

/**
 * 
 * @param c add Cards01 c* to the top of the deck
 */
void DeckofCards::addToPile(Cards01* c)
{
    vec3 newTopCenter;
    vec3 moveup;
    mat4 yougotaRaise;
    mat4 idenity;
    float diffX, diffZ, diffY;

    if(numCards_inDeck>51)
    {
	//printf("Not quite sure what happened,but the size of the deck\nis currently %d, and adding the card it exceeds the\nmaximum size of the deck of 52.\n", numCards_inDeck);
    }
    //printf(" %d\n", __LINE__);
    if(numCards_inDeck<52)// && numCards_inDeck > -1)
    {
	
	//printf("number of cards in the deck: %d\n", numCards_inDeck);
	//printf("is the deck currently empty?: %d\n", isEmpty());
	if(isEmpty()==false)
	{
	   // printf("index of top of deck: %d\ntitle of top on deck: %d of %s\n", numCards_inDeck-1,pileofCards[numCards_inDeck-1]->getValue(), pileofCards[numCards_inDeck-1]->getSuit().c_str());
	}

	if(numCards_inDeck==0)//there are no cards in the deck
	{
	    newTopCenter=center;
	    //insert card c at the bottom of the deck
	    numCards_inDeck++;
	    pileofCards[0]=c;
	    topCard=pileofCards[0];
	    //printf("Card added to the deck\n");
	}
	else if(numCards_inDeck<52&&numCards_inDeck>0) //the size of
	{
	    newTopCenter=vec3(topCard->getCenter().x,
			    topCard->getCenter().y+cardDepth,
			    topCard->getCenter().z);

	    numCards_inDeck++;
	    pileofCards[numCards_inDeck-1]=c;
	    topCard=pileofCards[numCards_inDeck-1];
	    //printf("Card added to the deck\n");
	}

	if(newTopCenter.x > c->getCenter().x)//this means there's a positive difference between the two
	{
	    diffX=newTopCenter.x - c->getCenter().x;
	    //printf("newTopCenter.x>c->getCenter().x\ndiffX: %f\n", diffX);
	}
	else
	{
	     diffX=newTopCenter.x - c->getCenter().x;
	    //printf("newTopCenter.x <= c->getCenter().x\ndiffX: %f\n", diffX);
	}

	if(newTopCenter.z>c->getCenter().z)//this means there's a positive difference between the two
	{
	    diffZ=newTopCenter.z - c->getCenter().z;
	    //printf("newTopCenter.z > c->getCenter().z\ndiffZ: %f\n", diffZ);
	}
	else
	{
	    diffZ=newTopCenter.z - c->getCenter().z;
	    //printf("newTopCenter.z <= c->getCenter().z\ndiffZ: %f\n", diffZ);
	}

	if(newTopCenter.y > c->getCenter().y)
	{
	    diffY=newTopCenter.y - c->getCenter().y;
	    //printf("newTopCenter.y > c->getCenter().y\ndiffY: %f\n", diffY);
	}
	else
	{
	    diffY=newTopCenter.y - c->getCenter().y;
	    //printf("newTopCenter.y <= c->getCenter().u\ndiffY: %f\n", diffY);
	}

	moveup=vec3(diffX, diffY, diffZ);
	yougotaRaise=glm::translate(idenity, moveup);

	c->applyTransformation(yougotaRaise);
	c->setNewCenter(newTopCenter);

	pileofCards[numCards_inDeck-1]=c;
	topCard=pileofCards[numCards_inDeck-1];

	//printf("index of NEW top of deck: %d\ntitle of top on deck: %d of %s\n", numCards_inDeck, pileofCards[numCards_inDeck-1]->getValue(), pileofCards[numCards_inDeck-1]->getSuit().c_str());

	//printf("index of TOP CARD: %d\ntitle of TOP CARD: %d of %s\n", numCards_inDeck, topCard->getValue(), topCard->getSuit().c_str());
    }
}

/**
 * 
 * @return the card that was removed (the card that was on
 *	   the top of the deck)
 */
Cards01* DeckofCards::removeFromPile()
{
    //(36.75, -12,-27.75);
    // the center V apparently
    //X: 40.000000
    //Y: -11.916667
    //Z: -26.250000
    //my calculated center: vec3(40, -11.875, q-25.25);
    vec3 destination=vec3(40.000000, -11.916667, -26.250000);
    float diffX, diffZ, diffY;
    mat4 youregoingdown;
    mat4 idenity;
    Cards01 *cardRemoved=topCard;
    if(numCards_inDeck==0)
    {
	printf("No cards can be removed from the deck\n");
	return 0;
    }
    else if(numCards_inDeck==1)//thre's the last card in the deck
    {
	cardRemoved=topCard;

	//destination X coord is HIGHER than cardRemoved X coord
	if(destination.x>cardRemoved->getCenter().x)
	{
	    diffX=destination.x-cardRemoved->getCenter().x;
	}
	else//destination X coord is LESS than cardRemoved X coord
	    diffX=destination.x-cardRemoved->getCenter().x;


	//destination Z coord is HIGHER than cardRemoved Z coord
	if(destination.z>cardRemoved->getCenter().z)//this means there's a positive difference between the two
	{
	    diffZ=destination.z-cardRemoved->getCenter().z;
	}
	else//destination Z coord is LESS than cardRemoved Z coord
	    diffZ=destination.z-cardRemoved->getCenter().z;


	//destination Y coord is HIGHER than cardRemoved Y coord
	if(destination.y>cardRemoved->getCenter().y)
	{
	    diffY=destination.y-cardRemoved->getCenter().y;
	}
	else//destination Y coord is LESS than cardRemoved Y coord
	    diffY=destination.y-cardRemoved->getCenter().y;

	youregoingdown=glm::translate(idenity, vec3(diffX, diffY, diffZ)); //matrix that maoves the card to the destination
	cardRemoved->applyTransformation(youregoingdown);
	cardRemoved->setNewCenter(destination);
	pileofCards[0]->printCardsTitle();
	pileofCards[0]=NULL;
	topCard=pileofCards[0];
	numCards_inDeck--;
	//printf("last card in the deck removed? %d\n", isEmpty());
	/**
	 * taking that the card to be removed is normamally above
	 * the point we want to move to destination
	 * we can do the center of removed card - destination
	 */
	//translate the removed card to vec3(36.75, -12,-27.75)
	return cardRemoved;
    }
    else if(numCards_inDeck>1)
    {
	//printf("num cards in deck: %d\n", numCards_inDeck);
	//printf("index of top card/one to be removed: %d\ntitle: %d of %s\n", numCards_inDeck-1, pileofCards[numCards_inDeck-1]->getValue(), pileofCards[numCards_inDeck-1]->getSuit().c_str());
	cardRemoved=topCard;


	topCard=pileofCards[numCards_inDeck-2];
	//printf("index of NEW top card: %d\ntitle: %d of %s\n", numCards_inDeck-2, pileofCards[numCards_inDeck-2]->getValue(), pileofCards[numCards_inDeck-2]->getSuit().c_str());

	//destination X coord is HIGHER than cardRemoved X coord
	if(destination.x>cardRemoved->getCenter().x)
	{
	    diffX=destination.x-cardRemoved->getCenter().x;
	}
	else//destination X coord is LESS than cardRemoved X coord
	    diffX=destination.x-cardRemoved->getCenter().x;


	//destination Z coord is HIGHER than cardRemoved Z coord
	if(destination.z>cardRemoved->getCenter().z)//this means there's a positive difference between the two
	{
	    diffZ=destination.z-cardRemoved->getCenter().z;
	}
	else//destination Z coord is LESS than cardRemoved Z coord
	    diffZ=destination.z-cardRemoved->getCenter().z;


	//destination Y coord is HIGHER than cardRemoved Y coord
	if(destination.y>cardRemoved->getCenter().y)
	{
	    diffY=destination.y-cardRemoved->getCenter().y;
	}
	else//destination Y coord is LESS than cardRemoved Y coord
	    diffY=destination.y-cardRemoved->getCenter().y;

	youregoingdown=glm::translate(idenity, vec3(diffX, diffY, diffZ));
	cardRemoved->applyTransformation(youregoingdown);
	cardRemoved->setNewCenter(destination);
	numCards_inDeck--;
	return cardRemoved;
    }
    return 0;
}

/**
 * shuffling code got from:
 * http://www.geeksforgeeks.org/shuffle-a-deck-of-cards-3/
 */
void DeckofCards::shuffle()
{
    mat4 idenity;
    mat4 translateUp;
    mat4 translateDown;
    vec3 differenceOf_i_r_centers;
    vec3 centerI;
    vec3 centerR;
    srand(time(0));
    if(numCards_inDeck>1 && numCards_inDeck>0)//don't debate with  me on trying to shuffle a 1 card deck
    {
	for(int i=0; i<numCards_inDeck; i++)
	{
	    // Random for remaining positions.
	    int r=i+(rand()%(numCards_inDeck-i)); //
	    //line above has been slightly modified from original source
	    centerI=pileofCards[i]->getCenter();
	    centerR=pileofCards[r]->getCenter();
	    //printf("\n\n\n");
	    //printf("Card at %d: %d of %s\n", i, pileofCards[i]->getValue(),pileofCards[i]->getSuit().c_str());
	    //pileofCards[i]->printCenterCoords();
	    //printf("\n");
	    //printf("Card at %d: %d of %s\n", r,pileofCards[r]->getValue(),pileofCards[r]->getSuit().c_str());
	    //pileofCards[r]->printCenterCoords();

	    if(pileofCards[i]->getCenter().y>pileofCards[r]->
	    getCenter().y)
		//card i is above card r
	    {
		differenceOf_i_r_centers=pileofCards[i]->getCenter()-pileofCards[r]->getCenter();
		//printf("\ndifference of the distances between the center of i and center of r\n\tY: %f\n",differenceOf_i_r_centers.y);
		//translate card i DOWN by differenceOf_i_r_centers.y
		translateDown=glm::translate(idenity, vec3(0, -1*differenceOf_i_r_centers.y, 0));

		//translate card r UP by differenceOf_i_r_centers.y
		translateUp=glm::translate(idenity, vec3(0, differenceOf_i_r_centers.y, 0));

		pileofCards[i]->applyTransformation(translateDown);
		pileofCards[r]->applyTransformation(translateUp);
	    }
	    else if(pileofCards[i]->getCenter().y<pileofCards[r]->
		    getCenter().y)
		//card r is above card i
	    {
		differenceOf_i_r_centers=pileofCards[r]->getCenter()-pileofCards[i]->getCenter();
		//printf("\ndifference of the distances between the center of r and center of i\n\tY: %f\n",differenceOf_i_r_centers.y);
		//translate card r DOWN by differenceOf_i_r_centers.y
		translateDown=glm::translate(idenity, vec3(0, -1*differenceOf_i_r_centers.y, 0));

		//translate card i UP by differenceOf_i_r_centers.y
		translateUp=glm::translate(idenity, vec3(0, differenceOf_i_r_centers.y, 0));

		pileofCards[r]->applyTransformation(translateDown);
		pileofCards[i]->applyTransformation(translateUp);
	    }
	    pileofCards[r]->setNewCenter(centerI);
	    pileofCards[i]->setNewCenter(centerR);
	    std::swap(pileofCards[i], pileofCards[r]); //this line taken and moved

	    //printf("\n\n\n");
	}
	topCard=pileofCards[numCards_inDeck-1];
    }

}

Cards01* DeckofCards::getCardatindex(int i)
{
    if(i<numCards_inDeck)
    {
	return pileofCards[i];
    }
    else
    {
	printf("INVALID INDEX!!!!");
	return 0;
    }
}

void DeckofCards::stackNeatly()
{
    if (numCards_inDeck==0)
    {
	printf("no cards in the deck no reason to stack them neatly\n\n");
    }
    else
    {
	mat4 idenity;
	mat4 move;
	vec3 differenceOf_i_r_centers;
	vec3 cardCenter;
	float yVal=0;
	for (int i=0; i<numCards_inDeck; i++)
	{
	    cardCenter = pileofCards[i]->getCenter();
	    differenceOf_i_r_centers=vec3(center.x, yVal, center.z)-cardCenter;
	    move=glm::translate(pileofCards[i]->getModelMatrix(), differenceOf_i_r_centers);
	    pileofCards[i]->applyTransformation(move);
	    pileofCards[i]->setNewCenter(vec3(center.x, yVal, center.z));
	    yVal+=cardDepth;
	}
    }
}

/**
 * 
 * @return numCards_inDeck;
 */
unsigned int DeckofCards::getSize()
{
    return numCards_inDeck;
}
