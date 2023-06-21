//
// Created by Ania on 04.06.2023.
//

#include <algorithm>
#include <random>
#include <stdexcept>
#include <iostream>
#include <utility>
#include "table.h"

std::vector<Card> Table::createDeck() {
    std::vector<Card> deck;
    for (int value = 2; value <= 14; ++value) {
        for (int color = 0; color < 4; ++color) {
            deck.push_back({ value, static_cast<Color>(color) });
        }
    }
    return deck;
}

std::array<std::vector<Card>, 4> Table::dealHands() {
    std::vector<Card> deck = createDeck();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(deck.begin(), deck.end(), gen);
    std::array<std::vector<Card>, 4> hands;
    std::array<int, 4> handSums = {0, 0, 0, 0};
    for (int i = 0; i < 52; ++i) {
        int handIndex = i % 4;
        hands[handIndex].push_back(deck[i]);
        handSums[handIndex] += deck[i].value;
    }
    int highestSumIndex = 0;
    for (int i = 1; i < 4; ++i) {
        if (handSums[i] > handSums[highestSumIndex]) {
            highestSumIndex = i;
        }
    }
    // "najlepsze" karty beda na indeksie 0 i trafia do rozgrywajacego
    if (highestSumIndex != 0) {
        std::swap(hands[0], hands[highestSumIndex]);
    }
    return hands;
}

Table::Table(Hand player, Hand LHO, Hand dummy, Hand RHO) {
    std::array<std::vector<Card>, 4> hands = dealHands();
    this->player = std::move(player);
    this->LHO = std::move(LHO);
    this->RHO = std::move(RHO);
    this->dummy = std::move(dummy);
    this->player.getCards(hands[0]);
    this->LHO.getCards(hands[1]);
    this->dummy.getCards(hands[2]);
    this->RHO.getCards(hands[3]);
}

int Table::whoTakes(bool isTrumpGame, Color trump){
    int highestIndex = 0;
    Color color = cardsOnTable[0].color;
    bool isHighestTrump = color == trump;
    for (int i=1; i<cardsOnTable.size(); i++){
        if (!isHighestTrump && cardsOnTable[i].color == color && cardsOnTable[i].value > cardsOnTable[highestIndex].value){
            highestIndex = i;
        }
        else if (cardsOnTable[i].color == trump && (!isHighestTrump || cardsOnTable[i].value > cardsOnTable[highestIndex].value)){
            highestIndex = i;
            isHighestTrump = true;
        }
    }
    return highestIndex;
}

Hand Table::getPlayerHand(Player_hands whichHand) const
{
    switch(whichHand){
    case Player_hand:
        return player;
    case LHO_hand:
        return LHO;
    case Dummy_hand:
        return dummy;
    case RHO_hand:
        return RHO;
    }
}

int Table::getCurrentlyPlaying() const
{
    return currentlyPlaying;
}

void Table::setCurrentlyPlaying(int who)
{
    currentlyPlaying = who;
}

std::vector<Card> Table::getCardsOnTable() const
{
    return cardsOnTable;
}

void Table::addCardToTable(Card card)
{
    cardsOnTable.push_back(card);
}

Card Table::NPC_play(Color trump, bool isTrumpGame)
{
    Hand playingHand;
    Card returnCard;
    try {
        if (currentlyPlaying == 1) {
            playingHand = LHO;
        }
        else if (currentlyPlaying == 3) {
            playingHand = RHO;
        }
        else {
            throw std::runtime_error("Invalid player position!");
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return Card();
    }
    if(numPlayedThisRound == 0){
        returnCard = playingHand.throwCardFirst();
    }
    else if(numPlayedThisRound == 1){
        returnCard = playingHand.throwCardSecond(cardsOnTable[0], trump, isTrumpGame);
    }
    else {
        int whoTook = whoTakes(isTrumpGame, trump);
        bool isHigherNeeded = (numPlayedThisRound == 2 && whoTook == 1) || (numPlayedThisRound == 3 && whoTook != 1);
        bool isHighestTrump = cardsOnTable[whoTook].color == trump;
        returnCard = playingHand.throwCardLast(cardsOnTable[0].color, trump, isHigherNeeded, cardsOnTable[whoTook].value, isHighestTrump, isTrumpGame);
    }
    addCardToTable(returnCard);
    numPlayedThisRound++;
    currentlyPlaying = (currentlyPlaying + 1) % 4;
    return returnCard;

}

Card Table::player_play(int whichCard)
{
    Hand playingHand;
    try {
        if (currentlyPlaying == 0) {
            playingHand = player;
        }
        else if (currentlyPlaying == 2) {
            playingHand = dummy;
        }
        else {
            throw std::runtime_error("Invalid player position!"); // Throw an exception
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << " " << currentlyPlaying << std::endl;
        return Card();
    }
    numPlayedThisRound++;
    currentlyPlaying = (currentlyPlaying + 1) % 4;
    Card returnCard = playingHand.throwCard(whichCard);
    addCardToTable(returnCard);
    return returnCard;
}

void Table::endOfRound(bool isTrumpGame, Color trump)
{
    int whoTook = whoTakes(isTrumpGame, trump);
    currentlyPlaying = ((currentlyPlaying + 1) % 4 + whoTook) % 4;
    numPlayedThisRound = 0;
    cardsOnTable.clear();
}

