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

int Game::getTakenNum() const
{
    return takenNum;
}

int Game::getUntakenNum() const
{
    return untakenNum;
}

int Game::getContractLevel() const
{
    return contractLevel;
}

Card Game::getCard(Player_hands whichPlayer, int index) const
{
    return table->getPlayerHand(whichPlayer).getCard(index);
}

std::vector<int> Game::getCardIndexesOfColor(Player_hands whichPlayer, Color color)
{
    Hand hand = table->getPlayerHand(whichPlayer);
    return hand.getIndexesOfColor(color);
}

Card Game::opponentPlay()
{
    return table->NPC_play(trump, isTrumpGame);
}

Card Game::playerPlay(int whichCard)
{
    return table->player_play(whichCard);
}

int Game::numCardsLeft(Player_hands player)
{
    return table->getPlayerHand(player).getSize();
}


Color Game::getRoundColor() const
{
    return table->getCardsOnTable()[0].color;
}

int Game::howManyOnTable() const
{
    return table->getNumPlayedThisRound();
}

Hand Game::getPlayerHand(Player_hands whichHand) const
{
    return table->getPlayerHand(whichHand);
}

Player_hands Game::endOfRound()
{
    table->endOfRound(isTrumpGame, trump);
    switch(table->getCurrentlyPlaying()){
    case 0:
        takenNum++;
        return Player_hand;
    case 1:
        untakenNum++;
        return LHO_hand;
    case 2:
        takenNum++;
        return Dummy_hand;
    case 3:
        untakenNum++;
        return RHO_hand;
    default:
        return Player_hand;
    }
}
