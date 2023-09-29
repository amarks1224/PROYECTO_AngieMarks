#include "TrashDeck.h" 

void TrashDeck::addCard(Card card) {
    Deck.push_back(card);
}

Card TrashDeck::showLastCard() {
    if (!Deck.empty()) {
        return Deck.back();
    }
    else {
        Card emptyCard;
        emptyCard.idType = 0; 
        return emptyCard;
    }
}

int TrashDeck::quantityDeck() {
    return Deck.size();
}
