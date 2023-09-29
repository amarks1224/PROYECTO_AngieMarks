#pragma once
#include <iostream>
#include <random>
#include <vector>
#include "Card.h"
#include "TrashDeck.h"
#include "Player.h"
#ifndef DECKCARD_H
#define DECKCARD_H

class DeckCard {
private:
    std::vector<Card> Deck;
    std::mt19937 random; 

public:
    DeckCard();

    void giveCard(int quantity, Player& auxPlayer);
    void takeFirstCard(TrashDeck& trash);
    void createDeck();
    void addNormalWildCard();
    void addSpecialWildCard();
    void shuffleDeck();
    void printDeck();
    int quantityDeck();
};

#endif