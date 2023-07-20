#include <iostream>
#include <string>
using namespace std;

int *topla(int *a, int *b) {
    int *c = new int;
    *c = *a + *b;
    return c;
};

int main() {
    int a, b, *c;
    cout << "ilk sayiyi gir:";
    cin >> a;
    cout << "ikinci sayiyi gir:";
    cin >> b;
    c = topla(&a, &b);
    cout << "Sonuc: " << *c << endl;
    
    // Don't forget to deallocate the memory
    delete c;

    return 0;
}
