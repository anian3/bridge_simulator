//
// Created by Ania on 04.06.2023.
//
#include <algorithm>
#include <cstdlib>
#include <utility>
#include "hand.h"

bool Card::compare(const Card& card1, const Card& card2){
    if (card1.color != card2.color) {
        return static_cast<int>(card1.color) < static_cast<int>(card2.color);
    }
    return card1.value > card2.value;
}

Hand::Hand(std::vector<Card> givenCards) {
    numClubs_ = numSpades_ = numHearts_ = numDiamonds_ = 0;
    getCards(std::move(givenCards));
}

Hand::Hand() {
    numClubs_ = numSpades_ = numHearts_ = numDiamonds_ = 0;
}

void Hand::getCards(std::vector<Card> givenCards) {
    cards = std::move(givenCards);
    std::sort(cards.begin(), cards.end(), Card::compare);
    for (const Card &card: cards) {
        switch (card.color) {
            case Color::SPADES:
                ++numSpades_;
                break;
            case Color::HEARTS:
                ++numHearts_;
                break;
            case Color::DIAMONDS:
                ++numDiamonds_;
                break;
            case Color::CLUBS:
                ++numClubs_;
                break;
            default:
                break;
        }
    }
}

Card Hand::getCard(int index) const
{
    return cards[index];
}

int Hand::getSize() const
{
    return cards.size();
}

std::vector<int> Hand::getIndexesOfColor(Color color)
{
    std::vector<int> indexes;
    int startIndex = 0;
    switch(color) {
    case SPADES:
        for (int i = 0; i < numSpades(); ++i)
            indexes.push_back(i);
        break;
    case HEARTS:
        startIndex += numSpades();
        for (int i = 0; i < numHearts(); ++i)
            indexes.push_back(startIndex + i);
        break;
    case CLUBS:
        startIndex += numSpades() + numHearts();
        for (int i = 0; i < numClubs(); ++i)
            indexes.push_back(startIndex + i);
        break;
    case DIAMONDS:
        startIndex += numSpades() + numHearts() + numClubs();
        for (int i = 0; i < numDiamonds(); ++i)
            indexes.push_back(startIndex + i);
        break;
    }

    return indexes;
}

int Hand::numSpades() const {
    return numSpades_;
}

int Hand::numHearts() const {
    return numHearts_;
}

int Hand::numDiamonds() const {
    return numDiamonds_;
}

int Hand::numClubs() const {
    return numClubs_;
}

const std::vector<Card> &Hand::getCards() const {
    return cards;
}

void Hand::decreaseColorNum(Color color) {
    switch(color){
        case SPADES:
            numSpades_--;
            break;
        case HEARTS:
            numHearts_--;
            break;
        case CLUBS:
            numClubs_--;
            break;
        case DIAMONDS:
            numDiamonds_--;
            break;
    }
}

std::optional<Card> Hand::removeLowestOfColor(Color color) {
    std::optional<Card> toThrow;
    switch (color) {
        case Color::SPADES:
            if (numSpades() > 0) {
                toThrow = cards[numSpades() - 1];
                cards.erase(cards.begin() + numSpades() - 1);
            }
            break;
        case Color::HEARTS:
            if (numHearts() > 0) {
                toThrow = cards[numSpades() + numHearts() - 1];
                cards.erase(cards.begin() + numSpades() + numHearts() - 1);
            }
            break;
        case Color::CLUBS:
            if (numClubs() > 0) {
                toThrow = cards[numSpades() + numHearts() + numSpades() - 1];
                cards.erase(cards.begin() + numSpades() + numHearts() + numClubs() - 1);
            }
            break;
        case Color::DIAMONDS:
            if (numDiamonds() > 0) {
                toThrow = cards[numSpades() + numHearts() + numSpades() + numDiamonds() - 1];
                cards.erase(cards.begin() + numSpades() + numHearts() + numClubs() + numDiamonds() - 1);
            }
            break;
    }
    if (toThrow != std::nullopt){
        decreaseColorNum(toThrow->color);
    }
    return toThrow;
}


Card Hand::removeLowestOfAll() {
    int minValue = 13;
    int index = -1;
    if (numSpades() > 0 && cards[numSpades() - 1].value < minValue) {
        index = numSpades() - 1;
        minValue = cards[index].value;
    }
    if (numHearts() > 0 && cards[numSpades() + numHearts() - 1].value < minValue) {
        index = numSpades() + numHearts() - 1;
        minValue = cards[index].value;
    }
    if (numClubs() > 0 && cards[numSpades() + numHearts() + numClubs() - 1].value < minValue) {
        index = numSpades() + numHearts() + numClubs() - 1;
        minValue = cards[index].value;
    }
    if (numDiamonds() > 0 && cards[numSpades() + numHearts() + numClubs() + numDiamonds() - 1].value < minValue) {
        index = numSpades() + numHearts() + numClubs() + numDiamonds() - 1;
    }
    Card toThrow = cards[index];
    cards.erase(cards.begin() + index);
    decreaseColorNum(toThrow.color);
    return toThrow;
}

/* int Hand::highestValueOnTable(Card* cardsOnTable, int numCards) {
    int highestValue = 1;
    for (int i = 0; i < numCards; ++i) {
        if (cardsOnTable[i].value > highestValue) {
            highestValue = cardsOnTable[i].value;
        }
    }
    return highestValue;
} przeniesc do stolu
 */

std::optional<Card> Hand::lowestHigher(int startIndex, int endIndex, int highestOnTable) {
    std::optional<Card> toThrow;
    int index = -1;
    for (int i = startIndex; i <= endIndex; i++){
        if (cards[i].value < highestOnTable){
            break;
        }
        index = i;
    }
    if (index >- 1){
        toThrow = cards[index];
        cards.erase(cards.begin() + index);
        decreaseColorNum(toThrow->color);
    }
    return toThrow;
}

std::optional<Card> Hand::removeHigher(Color color, int highestOnTable) {
    std::optional<Card> toThrow;
    switch (color) {
        case SPADES:
            toThrow = lowestHigher(0, numSpades()-1, highestOnTable);
            break;
        case HEARTS:
            toThrow = lowestHigher(numSpades(), numSpades() + numHearts() -1, highestOnTable);
            break;
        case CLUBS:
            toThrow = lowestHigher(numSpades() + numHearts(), numSpades() + numHearts() + numClubs() -1, highestOnTable);
            break;
        case DIAMONDS:
            toThrow = lowestHigher(numSpades() + numHearts() + numClubs(), numSpades() + numHearts() + numClubs() +numDiamonds() -1, highestOnTable);
            break;
    }
    return toThrow;
}

Card Hand::throwCardSecond(Card firstCard, Color trump, bool isTrumpGame) {
    std::optional<Card> optionalCard;
    if (firstCard.value > 10){
        optionalCard = removeHigher(firstCard.color, firstCard.value);
        if (optionalCard.has_value()) {
            return optionalCard.value();
        }
    }
    optionalCard = removeLowestOfColor(firstCard.color);
    if (optionalCard.has_value()) {
        return optionalCard.value();
    }
    if (isTrumpGame) {
        optionalCard = removeLowestOfColor(trump);
        if (optionalCard.has_value()) {
            return optionalCard.value();
        }
    }
    return removeLowestOfAll();
}

Card Hand::throwCardLast(Color color, Color trump, bool isHigherNeeded, int highestOnTable, bool isHighestTrump, bool isTrumpGame) {
    std::optional<Card> optionalCard;
    // po prostu rzucamy wyzsza w kolorze
    if (isHigherNeeded && !isHighestTrump){
        optionalCard = removeHigher(color, highestOnTable);
        if (optionalCard.has_value()) {
            return optionalCard.value();
        }
    }
    // dorzucamy do koloru
    optionalCard = removeLowestOfColor(color);
    if (optionalCard.has_value()) {
        return optionalCard.value();
    }
    // nie mamy do koloru, probujemy zagrac wyzsze atu niz bylo wczesniej
    if (isTrumpGame && isHighestTrump) {
        optionalCard = removeHigher(trump, highestOnTable);
    }
    // jesli nie bylo wczesniej grane atu, rzucamy nasze najnizsze
    else if (isTrumpGame){
        optionalCard = removeLowestOfColor(trump);
    }
    if (optionalCard.has_value()) {
        return optionalCard.value();
    }
    // nie mamy do koloru i nie mamy atu, ktorym mozna wziac lewe -> dorzucamy najnizsza
    return removeLowestOfAll();
}

Card Hand::throwCard(int whichCard)
{
    Card toThrow = cards[whichCard];
    cards.erase(cards.begin() + whichCard);
    decreaseColorNum(toThrow.color);
    return toThrow;
}

Card Hand::throwCardFirst() {
    int index = rand() % cards.size();
    Card toThrow = cards[index];
    cards.erase(cards.begin() + index);
    decreaseColorNum(toThrow.color);
    return toThrow;
}








