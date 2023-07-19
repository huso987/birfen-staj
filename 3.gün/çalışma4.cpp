#include <iostream>
using namespace std;

int main() {
  int ships[4][4] = {
    { 0, 1, 1, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 0 }
  };

  int hits = 0;
  int numberOfTurns = 0;

  while (hits < 4) {
    int row, column;

    cout << "Kordinat seçimi\n";

    cout << "0 ile 3 arası satır seç: ";
    cin >> row;

    cout << "0 ile 3 arası sütun seç: ";
    cin >> column;

    if (row < 0 || row >= 4 || column < 0 || column >= 4) {
        cout << "geçersiz kordinat!\n\n";
        continue;
    }

    if (ships[row][column] == 1) {
      ships[row][column] = 0;
      hits++;
      cout << "Vurdun " << (4 - hits) << " sol.\n\n";
    } else {
      cout << "Kaybettin\n\n";
    }

    numberOfTurns++;
  }

  cout << "zafer!\n";
  cout << "kaybettin in " << numberOfTurns << " turns";
  
  return 0;
}
