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

void addCard(int** set, int& cardIndex, int** playerHand, int& playerCardCount) {
    playerHand[playerCardCount++] = set[cardIndex++];
}

bool more21(int** hand, int cardCount) {
    return cardSumm(hand, cardCount) > 21;
}

int cardSumm(int** hand, int cardCount) {
    int summ = 0;
    int aceCount = 0;

    for (int i = 0; i < cardCount; i++) {
        int cardValue = hand[i][0];
        if (cardValue > 10 && cardValue < 14) {
            summ += 10;
        }
        else if (cardValue == 14) {
            summ += 11;
            aceCount++;
        }
        else {
            summ += cardValue;
        }
    }

    while (summ > 21 && aceCount > 0) {
        summ -= 10;
        aceCount--;
    }

    return summ;
}

void dealerAddCard(int** set, int& cardIndex, int** dealerHand, int& dealerCardCount) {
    while (cardSumm(dealerHand, dealerCardCount) < 17) {
        addCard(set, cardIndex, dealerHand, dealerCardCount);
    }
}


void showMenu() {
    cout << "Добро пожаловать в игру 21!" << endl << "Для того что бы начать игру нажмите 1" << endl << "Для завершения игры нажмите 2" << endl;
}

int main() {
    setlocale(LC_ALL, "ru");
    int** set = generateCardsSet(); // главная колода
    shuffleSet(set);
    double balanceUser = 1000;

    while (true)
    {
        cout << "Ваш баланс: " << balanceUser << endl;
        showMenu();
        int choise;
        cin >> choise;
        switch (choise)
        {
        case 1:
            int cardIndex = 0;
            int playerCardCount = 0;
            int dealerCardCount = 0;
            int* playerCard[8]; // колода игрока
            int* dealerCard[8]; // колода дилера

            int betUser = 0;
            cout << "Введите вашу ставку: ";
            cin >> betUser;

            if (betUser > balanceUser) {
                cout << "Недостаточно средств для ставки!" << endl;
                continue;
            }

            cardsUserAndDealer(set, cardIndex, playerCard, dealerCard, playerCardCount, dealerCardCount);
            showHands(playerCard, playerCardCount, dealerCard, dealerCardCount);

            if (cardSumm(playerCard, playerCardCount) == 21) {
                cout << endl << "Black Jack!";
                betUser * 1.5;
                continue;
            }

            bool playerMove = true; // переменная которая определяет идет ли сейчас ход игрока

            while (!more21(playerCard, playerCardCount) && playerMove) {
                int choice2 = 0;
                cout << endl << "1 - Взять карту, 2 - Дабл, 3 - Оставить" << endl;
                cin >> choice2;

                switch (choice2)
                {
                case 1:
                    addCard(set, cardIndex, playerCard, playerCardCount);
                    showHands(playerCard, playerCardCount, dealerCard, dealerCardCount);
                    if (more21(playerCard, playerCardCount)) {
                        balanceUser -= betUser;
                        cout << "Перебор! Вы проиграли свою ставку: " << endl;
                        playerMove = false;
                    }
                    break;
                case 2:
                    if (betUser * 2 > balanceUser) {
                        cout << "Недостаточно средств для удвоения ставки!" << endl;
                        continue;
                    }
                    betUser *= 2;

                    addCard(set, cardIndex, playerCard, playerCardCount);
                    showHands(playerCard, playerCardCount, dealerCard, dealerCardCount);
                    if (more21(playerCard, playerCardCount)) {
                        balanceUser -= betUser;
                        cout << "Перебор! Вы проиграли: " << betUser << endl;
                    }
                    else {
                        dealerAddCard(set, cardIndex, dealerCard, dealerCardCount);
                        showHands(playerCard, playerCardCount, dealerCard, dealerCardCount);
                    }
                    playerMove = false;
                    break;
                case 3:
                    dealerAddCard(set, cardIndex, dealerCard, dealerCardCount);
                    showHands(playerCard, playerCardCount, dealerCard, dealerCardCount);
                    playerMove = false;
                    break;
                default:
                    break;
                }
            }

            if (!more21(playerCard, playerCardCount)) {
                int playerSum = cardSumm(playerCard, playerCardCount);
                int dealerSum = cardSumm(dealerCard, dealerCardCount);

                if (dealerSum > 21 || playerSum > dealerSum) {
                    balanceUser += betUser;
                    cout << "Вы выйграли: " << betUser << endl;
                }
                else if (dealerSum == playerSum) {
                    cout << "Ничья! Ваша ставка возвращена: " << betUser << endl;
                }
                else {
                    balanceUser -= betUser;
                    cout << "Дилер выйграл! Вы проиграли свою ставку: " << betUser << endl;
                }
            break;
        case 2:
            cout << "Вы успешно завершили игру!";
            break;
        default:
            break;
        }
    }  
}


//  suit - ♥3 : ♦4 : ♣5 : ♠6
