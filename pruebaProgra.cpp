#include "Game.h"
#include "DeckCard.h"
#include "TrashDeck.h"
#include "Player.h"
#include "Card.h"
#include "SecondCard.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <iostream>

int main() {
    Game unoGame;
    int option;

    do {
        std::cout << "Menú UNO" << std::endl;
        std::cout << "1. Modo Jugador vs Jugador" << std::endl;
        std::cout << "2. Modo Jugador vs Consola" << std::endl;
        std::cout << "3. Salir" << std::endl;
        std::cout << "Elija una opción: ";
        std::cin >> option;

        if (option == 1) {
          
            TrashDeck trashDeck;
            DeckCard deckCard;
            int position;
            Player auxPlayer;
            unoGame.playerVSPlayer(trashDeck, deckCard, position, auxPlayer);
        }
        else if (option == 2) {
            
            Player playerConsole;
            TrashDeck trashDeck;
            DeckCard deckCard;
            unoGame.playerVSConsole(playerConsole, deckCard, trashDeck, playerConsole);
        }
        else if (option == 3) {
            std::cout << "Saliendo del juego. ¡Hasta luego!" << std::endl;
            break;
        }
        else {
            std::cout << "Opción inválida. Por favor, elija una opción válida." << std::endl;
        }

    } while (option != 3);

    return 0;
}


