#include "bits/stdc++.h"
using namespace std;

#ifndef DeBuG
#define dbg(...)
#define TT template <typename T
#endif

// #define int int64_t
#define endl '\n'
#define sz(x) (int) (x).size()
#define all(x) begin(x), end(x)
#define rep(i,a,b) for(int i=a; i<(b); ++i)
TT> using V = vector<T>; using vi = V<int>;
using ll = long long; using pii=pair<int,int>;

void solve(int cs) {
    string s; cin >> s;
    int n = sz(s);

    int ans = 0;
    auto chk = [&](int i, int j, int len) -> bool {
        int n = i + len, m = i + 2 * len;
        while (i < n && j < m) {
            if ((s[i] == '?' || s[j] == '?' || s[i] == s[j])) i++, j++;
            else return false;
        }
        return true;
    };
    for (int len = n / 2; len >= 1; len--) {
        for (int i = 0; i < n; i++) {
            if (i + 2 * len > n) continue;
            if (chk(i, i + len, len)) {
                cout << 2 * len << endl;
                return;
            }
        }
    }
    cout << 0 << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
