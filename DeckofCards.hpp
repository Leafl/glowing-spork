/*
 * File:   DeckofCards.hpp
 * Author: Suzuka
 *
 * Date: November 8, 2017, 3:44 PM
 * 
 * 
 * Project 4
 * Shaila DiGiovanni & Emma Theberge
 */

#ifndef DeckofCards_hpp
#define DeckofCards_hpp

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <cmath>

#include "DrawableObject.h"
#include "Texture.hpp"
#include "Shader.hpp"
#include "Cards01.h"
#include "Quad1.h"

class DeckofCards//: public DrawableObject
{
public:
    DeckofCards(vec3 botLback, bool main);
    DeckofCards(vec3 botLback, bool main, int numCards);
    DeckofCards();

    ~DeckofCards() { }

    void addToPile(Cards01* c);//adds the card @param to the pile

    Cards01* removeFromPile();//returns the card that's been removed

    void shuffle();
    unsigned int getSize();
    bool isEmpty();
    void printDeck();
    Cards01* getCardatindex(int i);

    void stackNeatly();

private:
    double length = 6.5;
    double width = 4.5;
    double cardDepth = 0.25;

    bool isMainDeck;
    unsigned int numCards_inDeck;
    vec3 whereFirstCardWouldBe [8];
    vec3 center;
    vec3 bottomLeftBack;
    Cards01* topCard;//points to the card on the deck
    Cards01* pileofCards[52];
};
#endif /* DeckofCards_hpp */
