#include "cardsStruct.cpp"
#include "iostream"
#include <ctime>
#include <time.h>
#include <array>

void printCard(const Card &card)
{
	switch (card.rank)
	{
	case RANK_2:		std::cout << '2'; break;
	case RANK_3:		std::cout << '3'; break;
	case RANK_4:		std::cout << '4'; break;
	case RANK_5:		std::cout << '5'; break;
	case RANK_6:		std::cout << '6'; break;
	case RANK_7:		std::cout << '7'; break;
	case RANK_8:		std::cout << '8'; break;
	case RANK_9:		std::cout << '9'; break;
	case RANK_10:		std::cout << 'T'; break;
	case RANK_JACK:		std::cout << 'J'; break;
	case RANK_QUEEN:	std::cout << 'Q'; break;
	case RANK_KING:		std::cout << 'K'; break;
	case RANK_ACE:		std::cout << 'A'; break;
	}

	switch (card.suit)
	{
	case SUIT_CLUB:		std::cout << 'C'; break;
	case SUIT_DIAMOND:	std::cout << 'D'; break;
	case SUIT_HEART:	std::cout << 'H'; break;
	case SUIT_SPADE:	std::cout << 'S'; break;
	}
}
void printDeck(std::array<Card, 52> &deck){
	for (Card card : deck){
		printCard(card);
		std::cout << ' ';
	}
}
void swapCards(Card &card1, Card &card2){
	Card temp = card1;
	card1 = card2;
	card2 = temp;
}
int getRandomNumber(int min, int max)
{
	/*std::srand(static_cast<unsigned int>(std::time(nullptr)));*/
	/*std::srand(time(NULL));*/
	srand((unsigned)time(0)+rand());
	static const double fraction = 1.0 / (RAND_MAX + 1.0);
	return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}
void shuffleDeck(std::array<Card, 52> &deck){
	for (int i = 0; i < 52; i++){
		int random = getRandomNumber(0, 51);
		swapCards(deck[i], deck[random]);
	}
}
int getCardValue(const Card &card)
{
	switch (card.rank)
	{
	case RANK_2:		return 2;
	case RANK_3:		return 3;
	case RANK_4:		return 4;
	case RANK_5:		return 5;
	case RANK_6:		return 6;
	case RANK_7:		return 7;
	case RANK_8:		return 8;
	case RANK_9:		return 9;
	case RANK_10:		return 10;
	case RANK_JACK:		return 10;
	case RANK_QUEEN:	return 10;
	case RANK_KING:		return 10;
	case RANK_ACE:		return 11;
	}

	return 0;
}
Card getRandomCard(){
	Card card;
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	int randomRank = getRandomNumber(0, MAX_RANKS);
	int randomSuit = getRandomNumber(0, MAX_SUITS);
	card.suit = static_cast<CardSuit>(randomSuit);
	card.rank = static_cast<CardRank>(randomRank);
	
	return card;
}
std::array<Card, 52> getShuffledDeck(){
	std::array<Card, 52> deck;
	int cardn = 0;
	for (int i = 0; i < MAX_SUITS; i++){
		for (int j = 0; j < MAX_RANKS; j++){
			deck[cardn].suit = static_cast<CardSuit>(i);
			deck[cardn].rank = static_cast<CardRank>(j);
			++cardn;
		}

	}
	shuffleDeck(deck);
	return deck;
}
int getHandLength(std::array<Card, 11> hand){
	int length = 0;
	for (int i = 0; i < 11; i++){
		if (hand[i].dealed)
			++length;
	}
	return length;
}
void drawCard(std::array<Card, 11> &deck, std::array<Card, 52> &cards, Card &deckPtr){
	int length = getHandLength(deck);
	deck[length] = deckPtr;
	deck[length].dealed = true;
}
int getDeckValue(const std::array<Card, 11> &deck){
	int value = 0;
	for (int i = 0; i < 11; i++){
		if (deck[i].dealed){
			value += getCardValue(deck[i]);
		}
	}
	return value;
}
int getMove(){
	std::cout << "Would you like to hit or to stand? (h/s)" << std::endl;
	char m;
	std::cin >> m;
	std::cin.ignore(32767, '\n');
	switch (m){
	case 's': return 0; break;
	case 'h': return 1; break;
	default: return getMove(); break;
	}
}
void playerWon(std::array<Card, 11> &deck, std::array<Card, 11> &dealer){
	int playerScore = getDeckValue(deck);
	int dealerScore = getDeckValue(dealer);
	std::cout << "Congratulations, you won!" << std::endl;
	std::cout << "You had score of " << playerScore << ", and dealer had score of " << dealerScore << std::endl;
}
void playerLost(std::array<Card, 11> &deck, std::array<Card, 11> &dealer){
	int playerScore = getDeckValue(deck);
	int dealerScore = getDeckValue(dealer);
	std::cout << "Im sorry, but you lost, better luck next time." << std::endl;
	std::cout << "You had score of " << playerScore << ", and dealer had score of " << dealerScore << std::endl;
}
void gameTie(std::array<Card, 11> &deck, std::array<Card, 11> &dealer){
	int playerScore = getDeckValue(deck);
	std::cout << "Both you and the dealer had score of " << playerScore << ". It is a tie!" << std::endl;
}
void nowDealer(std::array<Card, 11> &deck, std::array<Card, 11> &dealer, std::array<Card, 52> &cardDeck, Card *deckPtr){
	short dealerScore = getDeckValue(dealer);
	short playerScore = getDeckValue(deck);
	if (dealerScore >= 17){
		if (dealerScore < 22){
			if (dealerScore > playerScore){
				playerLost(deck, dealer);
			}
			else if (dealerScore < playerScore){
				playerWon(deck, dealer);
			}
			else if (dealerScore == playerScore){
				gameTie(deck, dealer);
			}
		}
	}
	else {
		drawCard(dealer,cardDeck,*deckPtr++);
		std::cout << "Dealer drew a card a now have a score of " << getDeckValue(dealer) << std::endl;
		nowDealer(deck, dealer,cardDeck,deckPtr);
	}
}
void doHit(std::array<Card, 11> &deck, std::array<Card, 11> &dealer, std::array<Card, 52> &cardDeck, Card *deckPtr){
	drawCard(deck,cardDeck,*deckPtr++);
	short deckValue = getDeckValue(deck);
	std::cout << "Now your score is " << deckValue << std::endl;
	if (deckValue < 22){
		if (deckValue == 21){
			playerWon(deck, dealer);
		}
		else {
			short dealerValue = getDeckValue(dealer);
			if (dealerValue < 22){
				if (dealerValue == 21){
					playerLost(deck, dealer);
				}
				else {
					int move = getMove();
					if (move){
						doHit(deck, dealer, cardDeck, deckPtr);
					}
					else {
						nowDealer(deck, dealer, cardDeck, deckPtr);
					}
				}
			}
			else {
				playerWon(deck, dealer);
			}
		}
	}
	else {
		playerLost(deck, dealer);
	}
}
void startGame(){
	std::array<Card, 52> cardDeck = getShuffledDeck();
	Card *cardPtr = &cardDeck[0];
	std::array<Card, 11> dealerCards;
	std::array<Card, 11> myCards;
	drawCard(myCards, cardDeck, *cardPtr++);
	drawCard(dealerCards, cardDeck, *cardPtr++);
	drawCard(myCards, cardDeck, *cardPtr++);
	std::cout << "You have " << getDeckValue(myCards) << ", dealer have " << getDeckValue(dealerCards) << std::endl;
	int move = getMove();
	if (move){
		doHit(myCards,dealerCards, cardDeck, cardPtr);
	}
	else {
		nowDealer(myCards, dealerCards, cardDeck, cardPtr);
	}
}
