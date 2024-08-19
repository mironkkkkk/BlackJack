#include <iostream>
#define random(a,b) (a + rand() % (b + 1 - a))
using namespace std;

int** generateCardsSet() {
    int** set = new int* [52];
    for (int index = 0, value = 2; value < 15; value++) {
        for (int suit = 3; suit < 7; suit++) {
            set[index++] = new int[2] {value, suit};
        }
    }
    return set;
}

void shuffleSet(int** set) {
    for (int i = 0; i < 52; i++) {
        int randomIndex = random(0, 51);
        int* temp = set[i];
        set[i] = set[randomIndex];
        set[randomIndex] = temp;
    }
}

void showCards(int** set, int countCards) {
    for (int i = 0; i < countCards; i++) {
        switch (set[i][0]) {
        case 11:
            cout << "J";
            break;
        case 12:
            cout << "Q";
            break;
        case 13:
            cout << "K";
            break;
        case 14:
            cout << "A";
            break;
        default:
            cout << set[i][0];
        }
        cout << char(set[i][1]) << " ";
    }
    cout << endl;
}

void showHands(int** playerCard, int playerCardCount, int** dealerCard, int dealerCardCount) {
    cout << "Ваши игрока: ";
    showCards(playerCard, playerCardCount);

    cout << "Карты дилера: ";
    showCards(dealerCard, dealerCardCount);
}


void cardsUserAndDealer(int** set, int& cardIndex, int** playerCard, int** dealerCard, int& playerCardCount, int& dealerCardCount) {
    playerCard[playerCardCount++] = set[cardIndex++];
    dealerCard[dealerCardCount++] = set[cardIndex++];
    playerCard[playerCardCount++] = set[cardIndex++];
    dealerCard[dealerCardCount++] = set[cardIndex++];
}

void showMenu() {
    cout << "Добро пожаловать в игру 21!" << endl << "Для того что бы начать игру нажмите 1" << endl << "Для завершения игры нажмите 2" << endl;
}

int main() {
    setlocale(LC_ALL, "ru");
    int** set = generateCardsSet(); // главная колода
    shuffleSet(set);
    showMenu();
    int choise;
    cin >> choise;
    switch (choise)
    {
    case 1:
        int cardIndex = 0;
        int playerCardCount = 0;
        int dealerCardCount = 0;
        int* playerCard[8];
        int* dealerCard[8];

        cardsUserAndDealer(set, cardIndex, playerCard, dealerCard, playerCardCount, dealerCardCount);
        showHands(playerCard, playerCardCount, dealerCard, dealerCardCount);
        break;
    case 2:
        cout << "Вы успешно завершили игру!";
        break;
    default:
        break;
    }
}


//  suit - ♥3 : ♦4 : ♣5 : ♠6
