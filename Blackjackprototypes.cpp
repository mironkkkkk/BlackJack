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

void shuffleDeck(int** set) {
    for (int i = 0; i < 52; i++) {
        int randomIndex = random(0, 51);
        int* temp = set[i];
        set[i] = set[randomIndex];
        set[randomIndex] = temp;
    }
}

void showCards(int** array) {
    int countCards = _msize(array) / sizeof(array[0]);
    for (int i = 0; i < countCards; i++) {
        switch (array[i][0]) {
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
            cout << array[i][0];
        }
        cout << char(array[i][1]) << " ";
    }
}


int main() {
    int** set = generateCardsSet();
    shuffleDeck(set);
    showCards(set);
}


//  suit - ♥3 : ♦4 : ♣5 : ♠6
