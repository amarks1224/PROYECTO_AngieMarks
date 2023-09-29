#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include "Card.h"
#include "TrashDeck.h"
#include "DeckCard.h"
#include "Player.h"
#ifndef Game_H
#define Game_H

class Game {
private:
    std::vector<Player> players;
    Player currentPlayer;

    const std::vector<Player>& getPlayers() const {
       return players;
    }

    int positionPlayer = 0;
    int rotation = 1;
    bool blockingEffect = false;

public:
    Game();

    int nextTurn();
    int nextTurn2();
    bool throwValidate(TrashDeck& trashDeck, DeckCard& deckCard, int position, Player& auxPlayer);
    void playerVSConsole(Player& playerConsole, DeckCard& deckCard, TrashDeck& trashDeck, Player& player);
    void playerVSPlayer(TrashDeck& trashDeck, DeckCard& deckCard, int position, Player& auxPlayer);
};

#endif