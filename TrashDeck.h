#pragma once
#include <vector>
#include "Card.h" 
#ifndef TRASHDECK_H
#define TRASHDECK_H


class TrashDeck {
private:
    std::vector<Card> Deck;

public:
    void addCard(Card card);

    Card showLastCard();

    int quantityDeck();
};

#endif