#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <string>
#include <set>
#include <cstdio>
#include <sstream>
#include <cmath>
#include <list>

using namespace std;

const int digits[] = { 2,3,4,5,6,7,8,9 };

long long tenp[20];

const long long MOD = 2520;
long long dp[20][MOD][1 << 8];

inline int updMask(int mask, int dig) {
    if (dig < 2) return mask;
    else return mask | (1 << (dig - 2));
}

long long count(long long n) {
    if (n <= 10) return n;
    string s = to_string(n);
    long long mod = 0;
    long long res = -1;
    int mask = 0;
    for (size_t i = 0; i < s.length(); ++i) {
        int rest = s.length() - i - 1;
        for (char c = '0'; c < s[i]; ++c) {
            res += dp[rest][mod][updMask(mask, c - '0')];
            mod = (mod + tenp[rest]) % MOD;
        }
        mask = updMask(mask, s[i] - '0');
    }
    res += dp[0][mod][mask];
    return res;
}

int main() {
    cout << fixed;
    cout.precision(16);

    tenp[0] = 1;
    for (int i = 1; i < 20; ++i) {
        tenp[i] = (tenp[i - 1] * 10) % MOD;
    }

    for (int len = 0; len < 20; ++len) for (int mod = 0; mod < MOD; ++mod) for (int mask = 0; mask < 1 << 8; ++mask) {
        if (len == 0) {
            long long res = 1;
            for (int i = 0; i < 8; ++i) if (mask & (1 << i)) {
                if (mod % digits[i] != 0) {
                    res = 0;
                    break;
                }
            }
            dp[len][mod][mask] = res;
        }
        else {
            long long res = 0;
            for (int dig = 0; dig <= 9; ++dig) {
                int newMod = (mod + dig * tenp[len - 1]) % MOD;
                int newMask = updMask(mask, dig);
                res += dp[len - 1][newMod][newMask];
            }
            dp[len][mod][mask] = res;
        }
    }

    int t;
    cin >> t;
    while (t--) {
        long long l, r;
        cin >> l >> r;
        long long cl = count(l - 1);
        long long cr = count(r);
        cout << cr - cl << "\n";
    }

    return 0;
}