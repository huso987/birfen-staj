#include <iostream>
#include <string>
using namespace std;

int hesaplama(int a,int b,int *kalan){
    
  int divided=a/b;
  *kalan=a%b;
  
  return divided;
};


int main() {
  
  int a,b,yeni_kalan;
  cout << "ilk sayiyi gir:";
  cin >> a;
  cout << "ikinci sayiyi gir:";
  cin >> b;
  int bolum=hesaplama(a,b,&yeni_kalan);
  cout << "bölüm:"<< bolum << "\nkalan:" << yeni_kalan;
 


  return 0;
} 