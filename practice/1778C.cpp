#include "bits/stdc++.h"
using namespace std;

#ifndef DeBuG
#define dbg(...)
#define TT template <typename T
#endif

#define int int64_t
#define endl '\n'
#define sz(x) (int) (x).size()
#define all(x) begin(x), end(x)
#define rep(i,a,b) for(int i=a; i<(b); ++i)
TT> using V = vector<T>; using vi = V<int>;
using ll = long long; using pii=pair<int,int>;

void solve(int cs) {
    int n, k; cin >> n >> k;
    string s; cin >> s;
    string t; cin >> t;

    V<pii> segs;
    for (int i = 0; i < n; i++) {
        int j = i;
        while (j < n && s[j] == t[j]) j++;
        if (j - i) segs.push_back({i, j - 1});
        i = j;
    }
    // what if segs empty?
    // multiset<pii> ms; // {delta_inc, cost}
    int best = 0
    auto nc2 = [&](int x) { return x * (x - 1) / 2; };
    for (int i = 0; i < sz(segs) - 1; i++) {
        auto& [l1, r1] = segs[i];
        auto& [l2, r2] = segs[i + 1];
        int len1 = r1 - l1 + 1;
        int len2 = r2 - l2 + 1;
        int len = r2 - l1 + 1;
        int profit = nc2(len) - (nc2(len1) + nc2(len2));
        int cost = max(0ll, l2 - r1 - 1);
    }
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
