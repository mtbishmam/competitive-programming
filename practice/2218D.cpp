#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    vector<int> n(t);
    int maxN = 0;

    for (int &x : n) {
        cin >> x;
        maxN = max(maxN, x);
    }

    vector<long long> primes;

    for (long long x = 2; (int)primes.size() < maxN + 1; x++) {
        bool isPrime = true;

        for (long long p : primes) {
            if (p * p > x) break;
            if (x % p == 0) {
                isPrime = false;
                break;
            }
        }

        if (isPrime) primes.push_back(x);
    }

    for (int len : n) {
        for (int i = 0; i < len; i++) {
            if (i) cout << ' ';
            cout << primes[i] * primes[i + 1];
        }
        cout << '\n';
    }

    return 0;
}
