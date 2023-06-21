//
// Created by Ania on 06.06.2023.
//

#ifndef BRIDGE_SIMULATOR_GAME_H
#define BRIDGE_SIMULATOR_GAME_H

#include <vector>
#include "hand.h"
#include "table.h"

class Game {
public:
    Game();
    ~Game();

    void color_chosen(bool isTrumpGame, Color trump);
    void contractLevel_chosen(int contractLevel);

    bool isTrump() const;
    Color getTrump() const;

    Card getCard(Player_hands whichPlayer, int index) const;

    std::vector<int> getCardIndexesOfColor(Player_hands whichPlayer, Color color);

    Card opponentPlay();

    Card playerPlay(int whichCard);

    int numCardsLeft(Player_hands player);

    Color getRoundColor() const;

    int howManyOnTable() const;

    Hand getPlayerHand(Player_hands whichHand) const;

    Player_hands endOfRound();

private:
    //
    bool isTrumpGame;
    Color trump;
    int contractLevel;
    int takenNum = 0;
    int untakenNum = 0;
    Table *table;
};


#endif //BRIDGE_SIMULATOR_GAME_H
