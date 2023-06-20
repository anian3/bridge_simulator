#ifndef HAND_H
#define HAND_H

#include <vector>
#include <optional>


enum Color {
    SPADES,
    HEARTS,
    CLUBS,
    DIAMONDS
};

struct Card {
    int value; // 2-14
    Color color;

    int getValue() const {return value;}
    Color getColor() const {return color;}
    static bool compare(const Card& card1, const Card& card2);
};

class Hand {
public:
    explicit Hand(std::vector<Card> givenCards);
    Hand();

    void getCards(std::vector<Card> givenCards);

    Card getCard(int index) const;

    int getSize() const;

    Card throwCardFirst(); // wistuje

    Card throwCardSecond(Card firstCard, Color trump, bool isTrumpGame); // rzuca jako drugi

    Card throwCardLast(Color color, Color trump, bool isHigherNeeded, int highestOnTable, bool isHighestTrump, bool isTrumpGame); // rzuca jako trzeci lub czwarty

    Card throwCard(int whichCard);

    [[nodiscard]] int numSpades() const;

    [[nodiscard]] int numHearts() const;

    [[nodiscard]] int numDiamonds() const;

    [[nodiscard]] int numClubs() const;

    [[nodiscard]] const std::vector<Card>& getCards() const;

private:
    //
    std::vector<Card> cards;
    int numSpades_, numHearts_, numDiamonds_, numClubs_;

    // methods:
    void decreaseColorNum(Color color);
    std::optional<Card> removeLowestOfColor(Color color); // usuwa i zwraca najnizsza karte w danym kolorze, jezeli jest w nim jakakolwiek
    Card removeLowestOfAll(); //usuwa i zwraca najnizsza karte ze wszystkich
    std::optional<Card> removeHigher(Color color, int highestCard); // usuwa i zwraca mozliwie najnizsza karte wyzsza od tych na stole, jezeli taka istnieje
    std::optional<Card> lowestHigher(int startIndex, int endIndex, int highestOnTable); // zwraca najnizsza wyzsza od najwyzszej na stole, znajdujaca sie miedzy zadanymi indeksami
};


#endif // HAND_H
