#include <iostream>
using namespace std;

int main() {
  int ships[4][4] = {
    { 0, 1, 1, 0 },
    { 1, 0, 0, 0 },
    { 0, 0, 1, 0 },
    { 1, 0, 1, 0 }
  };

  int hits = 0;
  int numberOfTurns = 0;

  while (hits < 4) {
    int satir, sütun;

    cout << "Kordinat seçimi\n";

    cout << "0 ile 3 arası satır seç: ";
    cin >> satir;

    cout << "0 ile 3 arası sütun seç: ";
    cin >> sütun;

    if (satir < 0 || satir >= 4 || sütun < 0 || sütun >= 4) {
        cout << "geçersiz kordinat!\n\n";
        continue;
    }

    if (ships[satir][sütun] == 1) {
      ships[satir][sütun] = 0;
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
