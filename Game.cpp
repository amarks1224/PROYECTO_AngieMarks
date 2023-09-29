
#include "Game.h"

Game::Game() {

    DeckCard deckCard;
    TrashDeck trashDeck;

    deckCard.createDeck();
    deckCard.addNormalWildCard();
    deckCard.addSpecialWildCard();
    deckCard.shuffleDeck();
    deckCard.takeFirstCard(trashDeck);

    bool next = false;

    do {
        currentPlayer = players[positionPlayer];
        bool comerOrNot = false;

        do {
            blockingEffect = false;
            std::cout << "-------------------------------------------" << std::endl;
            std::cout << "sentido " << rotation << std::endl;
            std::cout << "Turno de " << currentPlayer.name << std::endl;

            std::cout << "Mazo Cantidad Agarre: " << deckCard.quantityDeck() << std::endl;
            std::cout << "Mazo Cantidad Basura: " << trashDeck.quantityDeck() << std::endl;

            std::cout << "Carta en la basura: " << trashDeck.showLastCard().number << " || " << trashDeck.showLastCard().color << " || " << trashDeck.showLastCard().wildCard << std::endl;

            std::cout << "Mis Cartas" << std::endl;
            currentPlayer.showCard();
            bool Info1 = true;
            std::cout << "-------------------------------------------" << std::endl;

            while (Info1) {
                std::cout << "Info: Digite la posicion de la carta para botar, si no, escriba (-1) para comer" << std::endl;
                int position;
                std::cin >> position;

                if (position <= currentPlayer.deckPlayer.size()) {
                    if (position == -1) {
                        comerOrNot = true;
                        deckCard.giveCard(1, currentPlayer);
                        Info1 = false;
                    }
                    else {
                        if (throwValidate(trashDeck, deckCard, position, currentPlayer)) {
                            Info1 = false;
                            currentPlayer.throwCard(trashDeck, position);
                        }
                        else {
                            Info1 = true;
                            std::cout << "    XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << std::endl;
                            std::cout << "    X  ERROR: No se pudo botar esa carta  X" << std::endl;
                            std::cout << "    XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << std::endl;
                        }
                        comerOrNot = false;
                    }
                }
                else {
                    Info1 = true;
                    std::cout << "    XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << std::endl;
                    std::cout << "    X  ERROR: NO existe esa carta en la lista  X" << std::endl;
                    std::cout << "    XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << std::endl;
                }
            }
        } while (comerOrNot);

        if (currentPlayer.deckPlayer.empty()) {
            std::cout << " ---> El jugador '" << currentPlayer.name << "' ha Ganado <--- " << std::endl;
            next = false;
        }
        else {
            if (!blockingEffect) {
                positionPlayer = nextTurn();
            }
            else {
                // ...
            }
            next = true;
        }
    } while (next);
}

int Game::nextTurn() {
    int positionAux = 0;

    if (positionPlayer == 0 && rotation == -1) {
        positionAux = players.size() - 1;
    }
    else if (positionPlayer == players.size() - 1 && rotation == 1) {
        positionAux = 0;
    }
    else if (positionPlayer >= 0 && positionPlayer < players.size()) {
        positionAux = positionPlayer + rotation;
    }

    return positionAux;
}

int Game::nextTurn2() {
    int positionAux = 0;

    if (positionPlayer == 0 && rotation == -1) {
        positionAux = players.size() - 2;
    }
    else if (positionPlayer == players.size() - 1 && rotation == 1) {
        positionAux = 1;
    }
    else if (positionPlayer >= 0 && positionPlayer < players.size()) {
        positionAux = positionPlayer + (rotation * 2);
        if (positionAux == -1) {
            positionAux = players.size();
        }
        if (positionAux == players.size() + 1) {
            positionAux = 0;
        }
    }

    return positionAux;
}


bool Game::throwValidate(TrashDeck& trashDeck, DeckCard& deckCard, int position, Player& auxPlayer) {
    Card auxCard = auxPlayer.deckPlayer[position - 1];
    if (auxCard.idType == 1) {
        if (auxCard.color == trashDeck.showLastCard().color || auxCard.number == trashDeck.showLastCard().number) {
            return true;
        }
    }
    else if (auxCard.idType == -1) {
        if (auxCard.color == trashDeck.showLastCard().color || auxCard.wildCard == trashDeck.showLastCard().wildCard) {
            if (auxCard.wildCard == "Reversa") {
                if (rotation == 1) {
                    rotation = -1;
                }
                else if (rotation == -1) {
                    rotation = 1;
                }
                return true;
            }
            if (auxCard.wildCard == "Bloqueo") {
                positionPlayer = nextTurn2();
                blockingEffect = true;
                return true;
            }
            if (auxCard.wildCard == "+2") {
                deckCard.giveCard(2, players[nextTurn()]);
                return true;
            }
        }
    }
    else if (auxCard.idType == -2) {
        if (auxCard.wildCard == "Cambio de color") {
            std::cout << "Cual color desea cambiar?" << std::endl;
            std::cout << "Red, Blue, Green, Yellow" << std::endl;
            std::cin >> auxCard.color;
            return true;
        }
        if (auxCard.wildCard == "+4") {
            deckCard.giveCard(4, players[nextTurn()]);
            std::cout << "Cual color desea cambiar?" << std::endl;
            std::cout << "Red, Blue, Green, Yellow" << std::endl;
            std::cin >> auxCard.color;
            return true;
        }
    }
    return false;
}

void Game::playerVSConsole(Player& playerConsole, DeckCard& deckCard, TrashDeck& trashDeck, Player& player) {
    
    Player console;
    console.name = "Consola";
    deckCard.giveCard(8, console);
    players.push_back(console);

    std::cout << "Modo Jugador vs Consola iniciado." << std::endl;

    int turn = 0;
    bool activeGame = true;

    while (activeGame) {
        currentPlayer = players[turn];
        std::cout << "-------------------------------------------" << std::endl;
        std::cout << "Turno de " << currentPlayer.name << std::endl;

        std::cout << "Carta en la basura: " << trashDeck.showLastCard().number << " || " << trashDeck.showLastCard().color << " || " << trashDeck.showLastCard().wildCard << std::endl;
        std::cout << "Mis Cartas:" << std::endl;
        currentPlayer.showCard();

        bool turnEnded = false;

        while (!turnEnded) {
            std::cout << "Elija una acción:" << std::endl;
            std::cout << "1. Botar una carta" << std::endl;
            std::cout << "2. Comer una carta (-1)" << std::endl;

            int option;
            std::cin >> option;

            if (option == 1) {
                std::cout << "Seleccione la posición de la carta que desea botar: ";
                int position;
                std::cin >> position;

                if (position >= 1 && position <= currentPlayer.deckPlayer.size()) {
                    if (throwValidate(trashDeck, deckCard, position, currentPlayer)) {
                        currentPlayer.throwCard(trashDeck, position);
                        turnEnded = true;
                    }
                    else {
                        std::cout << "No se pudo botar esa carta. Intente de nuevo." << std::endl;
                    }
                }
                else {
                    std::cout << "Posición inválida. Intente de nuevo." << std::endl;
                }
            }
            else if (option == 2) {
                deckCard.giveCard(1, currentPlayer);
                turnEnded = true;
            }
            else {
                std::cout << "Opción inválida. Intente de nuevo." << std::endl;
            }
        }

        if (currentPlayer.deckPlayer.empty()) {
            std::cout << " ---> El jugador '" << currentPlayer.name << "' ha Ganado <--- " << std::endl;
            activeGame = false;
        }

        turn = (turn + 1) % players.size();
    }
}

void Game::playerVSPlayer(TrashDeck& trashDeck, DeckCard& deckCard, int position, Player& auxPlayer) {
    
    bool next = true;

    while (next) {
        currentPlayer = players[positionPlayer];
        bool comerOrNot = false;

        do {
            blockingEffect = false;
            std::cout << "-------------------------------------------" << std::endl;
            std::cout << "sentido " << rotation << std::endl;
            std::cout << "Turno de " << currentPlayer.name << std::endl;

            std::cout << "Mazo Cantidad Agarre: " << deckCard.quantityDeck() << std::endl;
            std::cout << "Mazo Cantidad Basura: " << trashDeck.quantityDeck() << std::endl;

            std::cout << "Carta en la basura: " << trashDeck.showLastCard().number << " || " << trashDeck.showLastCard().color << " || " << trashDeck.showLastCard().wildCard << std::endl;

            std::cout << "Mis Cartas" << std::endl;
            currentPlayer.showCard();
            bool Info1 = true;
            std::cout << "-------------------------------------------" << std::endl;

            while (Info1) {
                std::cout << "Info: Digite la posición de la carta para botar, si no, escriba (-1) para comer" << std::endl;
                int position;
                std::cin >> position;

                if (position <= currentPlayer.deckPlayer.size()) {
                    if (position == -1) {
                        comerOrNot = true;
                        deckCard.giveCard(1, currentPlayer);
                        Info1 = false;
                    }
                    else {
                        if (throwValidate(trashDeck, deckCard, position, currentPlayer)) {
                            Info1 = false;
                            currentPlayer.throwCard(trashDeck, position);
                        }
                        else {
                            Info1 = true;
                            std::cout << "    XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << std::endl;
                            std::cout << "    X  ERROR: No se pudo botar esa carta  X" << std::endl;
                            std::cout << "    XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << std::endl;
                        }
                        comerOrNot = false;
                    }
                }
                else {
                    Info1 = true;
                    std::cout << "    XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << std::endl;
                    std::cout << "    X  ERROR: NO existe esa carta en la lista  X" << std::endl;
                    std::cout << "    XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << std::endl;
                }
            }
        } while (comerOrNot);

        if (currentPlayer.deckPlayer.empty()) {
            std::cout << " ---> El jugador '" << currentPlayer.name << "' ha Ganado <--- " << std::endl;
            next = false;
        }
        else {
            if (!blockingEffect) {
                positionPlayer = nextTurn();
            }
            else {
                // ...
            }
            next = true;
        }
    }
}
