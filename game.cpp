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

Card Game::getCard(Player_hands whichPlayer, int index) const
{
    return table->getPlayerHand(whichPlayer).getCard(index);
}

Card Game::opponentPlayFirst(Player_hands opponent)
{
    Card card = table->getPlayerHand(opponent).throwCardFirst();
    table->addCardToTable(card);
    return card;
}

int Game::numCardsLeft(Player_hands player)
{
    return table->getPlayerHand(player).getSize();
}
