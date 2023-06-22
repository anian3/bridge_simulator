//
// Created by Ania on 04.06.2023.
//

#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <array>
#include "hand.h"

enum Player_hands {
    Player_hand,
    LHO_hand,
    Dummy_hand,
    RHO_hand
};

class Table {
public:
    Table(Hand player, Hand LHO, Hand dummy, Hand RHO);

    Hand getPlayerHand(Player_hands whichHand) const;

    int getCurrentlyPlaying() const;

    void setCurrentlyPlaying(int who);

    std::vector<Card> getCardsOnTable() const;

    Card NPC_play(Color trump, bool isTrumpGame);

    Card player_play(int whichCard);

    void endOfRound(bool isTrumpGame, Color trump); // patrzy, kto wziął lewę, ustawia currentlyPlaying

    int whoTakes(bool isTrumpGame, Color trump);

    void addCardToTable(Card card);

    int getNumPlayedThisRound() const;



 private:
    //
    Hand player;
    Hand LHO;
    Hand dummy;
    Hand RHO;
    int currentlyPlaying = 1; // 0-3 kto teraz wyrzuca karte
    int numPlayedThisRound = 0;
    std::vector<Card> cardsOnTable;

    //methods:
    static std::vector<Card> createDeck();
    static std::array<std::vector<Card>, 4> dealHands();
};

#endif //TABLE_H
