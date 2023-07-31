#include <iostream>
#include <string>
#include <cmath>
using namespace std;
// if else çalışması
// ehliyet alabilirlik kontrolu
int main() {

int age;
int education;
cout << "age: ";
cin >> age ;
cout << "*********************\n";


if (age >= 18)
{
  cout << "ilkokul=0|ortaokul=1|lise=2|üniversite=3|yükseklisans=4|Doktora=5\n";
  cout << "Lütfen 0 ile 5 arasında bir sayi girin:";
  cin >> education;
  cout << "*********************\n";
  if (education >= 2)
  {
    cout << "ehliyet alabilir\n";
  }
  else{
    cout << "en az lise mezunu olmanız lazım\n";
  }
  
}
else{
  cout << "en az 18 yaşında olamanız lazım\n";
}


  return 0;
} 