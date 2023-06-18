//
// Created by Ania on 04.06.2023.
//

#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <array>
#include "hand.h"

class Table {
public:
    Table(Hand player, Hand LHO, Hand dummy, Hand RHO);

    Card NPC_play(Color trump, bool isTrumpGame);

    Card player_play(int whichCard);

    void endOfRound(bool isTrumpGame, Color trump); // patrzy, kto wziął lewę, ustawia currentlyPlaying

    int whoTakes(bool isTrumpGame, Color trump);


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
