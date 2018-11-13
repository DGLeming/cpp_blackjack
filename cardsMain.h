#include "cardsStruct.cpp"
#include <array>
void printCard(const Card &card);
void printDeck(std::array<Card, 52> &deck);
void swapCards(Card &card1, Card &card2);
int getRandomNumber(int min, int max);
void shuffleDeck(std::array<Card, 52> &deck);
int getCardValue(const Card &card);
Card getRandomCard();
std::array<Card, 52> getShuffledDeck();
int getHandLength(std::array<Card, 11> hand);
void drawCard(std::array<Card, 11> &deck, std::array<Card, 52> &cards, Card *deckPtr);
int getDeckValue(const std::array<Card, 11> &deck);
int getMove();
void doHit(std::array<Card, 11> &deck, std::array<Card, 11> &dealer, std::array<Card, 52> &cardDeck, Card *deckPtr);
void playerWon(std::array<Card, 11> &deck, std::array<Card, 11> &dealer);
void playerLost(std::array<Card, 11> &deck, std::array<Card, 11> &dealer);
void startGame();
void nowDealer(std::array<Card, 11> &deck, std::array<Card, 11> &dealer, std::array<Card, 52> &cardDeck, Card *deckPtr);
void gameTie(std::array<Card, 11> &deck, std::array<Card, 11> &dealer);
