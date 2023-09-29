#include "DeckCard.h"

DeckCard::DeckCard() {
    
}

void DeckCard::giveCard(int quantity, Player& auxPlayer) {
    std::vector<Card> auxList;
    for (int i = 1; i <= quantity; i++) {
        if (!Deck.empty()) {
            Card auxCard = Deck.back();
            Deck.pop_back();
            auxPlayer.deckPlayer.push_back(auxCard);
        }
        else {
            std::cout << "--El mazo está vacío, no se pueden dar más cartas.--" << std::endl;
            break;
        }
    }
}

void DeckCard::takeFirstCard(TrashDeck& trash) {
    if (!Deck.empty()) {
        Card auxCard = Deck.back();
        Deck.pop_back();
        trash.addCard(auxCard);
    }
    else {
        std::cout << "--El mazo está vacío, no se pueden eliminar más cartas.--" << std::endl;
    }
}

void DeckCard::createDeck() {
    std::string colors[] = { "Red", "Blue", "Green", "Yellow" };

    for (const std::string& color : colors) {
        for (int number = 0; number <= 9; number++) {
            Card card;
            card.idType = 1;
            card.number = std::to_string(number);
            card.color = color;
            Deck.push_back(card);
        }
        for (int number = 1; number <= 9; number++) {
            Card card;
            card.idType = 1;
            card.number = std::to_string(number);
            card.color = color;
            Deck.push_back(card);
        }
    }
}

void DeckCard::addNormalWildCard() {
    std::string colors[] = { "Red", "Blue", "Green", "Yellow" };
    std::string wildCards[] = { "Reversa", "+2", "Bloqueo" };

    for (const std::string& color : colors) {
        for (const std::string& wildCard : wildCards) {
            for (int number = 1; number <= 2; number++) {
                Card card;
                card.idType = -1;
                card.color = color;
                card.wildCard = wildCard;
                Deck.push_back(card);
            }
        }
    }
}

void DeckCard::addSpecialWildCard() {
    std::string wildCards[] = { "+4", "Cambio de color" };

    for (const std::string& wildCard : wildCards) {
        for (int number = 1; number <= 4; number++) {
            Card card;
            card.color = "Negro";
            card.idType = -2;
            card.wildCard = wildCard;
            Deck.push_back(card);
        }
    }
}

void DeckCard::shuffleDeck() {
    int n = Deck.size();
    while (n > 1) {
        n--;
        int k = random() % (n + 1);
        Card value = Deck[k];
        Deck[k] = Deck[n];
        Deck[n] = value;
    }
}

void DeckCard::printDeck() {
    std::cout << "--Todas las cartas del mazo--" << std::endl;
    for (const Card& deckCart : Deck) {
        std::cout << "idCart:" << deckCart.idType << " || num: " << deckCart.number << " || color: " << deckCart.color << " || Comodin: " << deckCart.wildCard << std::endl;
    }
}

int DeckCard::quantityDeck() {
    return Deck.size();
}
