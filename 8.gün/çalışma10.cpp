// An attendance record for a student can be represented as a string 
// where each character signifies whether the student was absent, late, or
// present on that day. The record only contains the following three characters:
// 'A': Absent.
// 'L': Late.
// 'P': Present.
// Any student is eligible for an attendance award if they meet both of the following criteria:

// The student was absent ('A') for strictly fewer than 2 days total.
// The student was never late ('L') for 3 or more consecutive days.
// Given an integer n, return the number of possible attendance records of length n that 
// make a student eligible for an attendance award. The answer may be very large, so return 
// it modulo 109 + 7.

#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
int kayitKontrol(int n) {
    const int modu = 1000000007;
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(3, 0)));
    dp[0][0][0] = 1; 


    for (int i = 1; i <= n; ++i) {
        for (int a = 0; a <= 1; ++a) {
            for (int l = 0; l <= 2; ++l) {
                dp[i][a][0] = (dp[i][a][0] + dp[i - 1][a][l]) % modu;
                if (a > 0) {
                    dp[i][1][0] = (dp[i][1][0] + dp[i - 1][a][l]) % modu;
                }
                if (l > 0) {
                    dp[i][a][l] = (dp[i][a][l] + dp[i - 1][a][l - 1]) % modu;
                }
            }
        }
    }
    int cevap = 0;
    for (int a = 0; a <= 1; ++a) {
        for (int l = 0; l <= 2; ++l) {
            cevap = (cevap + dp[n][a][l]) % modu;
        }
    }

    return cevap;
}

int main() {
    int a = 2;
    int sonuç = kayitKontrol(a);
    cout << "kayit sayisi: " << sonuç << "\n";

    return 0;
}