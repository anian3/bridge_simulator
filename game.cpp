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

void Game::color_chosen(bool isTrumpGame, Color trump)
{
    this->isTrumpGame = isTrumpGame;
    this->trump = trump;
}

void Game::contractLevel_chosen(int contractLevel)
{
    this->contractLevel = contractLevel;
}

bool Game::isTrump() const
{
    return isTrumpGame;
}

Color Game::getTrump() const
{
    return trump;
}
