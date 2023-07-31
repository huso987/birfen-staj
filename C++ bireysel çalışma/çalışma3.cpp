#include <iostream>
#include <string>
using namespace std;

int main() {

  const int diziboyutu = 5;
    int sayilar[diziboyutu];

    std::cout << "5 adet sayi girin:\n";
    for (int i = 0; i < diziboyutu; i++) {
        std::cout << i + 1 << ". sayiyi girin: ";
        std::cin >> sayilar[i];
    }

    int enBuyuk = sayilar[0];
    int enKucuk = sayilar[0];
    int toplam = 0;

    for (int i = 0; i < diziboyutu; i++) {
        if (sayilar[i] > enBuyuk) {
            enBuyuk = sayilar[i];
        }

        if (sayilar[i] < enKucuk) {
            enKucuk = sayilar[i];
        }

        toplam += sayilar[i];
    }

    double ortalama = static_cast<double>(toplam) / diziboyutu;

    std::cout << "En buyuk sayi: " << enBuyuk << std::endl;
    std::cout << "En kucuk sayi: " << enKucuk << std::endl;
    std::cout << "Sayilarin toplami: " << toplam << std::endl;
    std::cout << "Sayilarin ortalamasi: " << ortalama << std::endl;
  return 0;
} 