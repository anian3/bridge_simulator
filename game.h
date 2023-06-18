//
// Created by Ania on 06.06.2023.
//

#ifndef BRIDGE_SIMULATOR_GAME_H
#define BRIDGE_SIMULATOR_GAME_H

#include "hand.h"
#include "table.h"

class Game {
public:
    Game();
    ~Game();

    void color_chosen(bool isTrumpGame, Color trump);
    void contractLevel_chosen(int contractLevel);



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
