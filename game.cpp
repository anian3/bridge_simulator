//
// Created by Ania on 06.06.2023.
//

#include "game.h"

Game::Game() {
    table = new Table(Hand(), Hand(), Hand(), Hand());
}

Game::~Game(){
    delete table;
}
