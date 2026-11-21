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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rand(l, r) uniform_int_distribution<ll>(l, r)(rng)

void solve(int cs) {
    int n; cin >> n;
    vi a(n); rep(i, 0, n) cin >> a[i];

    vi odd, even; map<int, vi> mp1, mp2; 
    multiset<pii> ms1, ms2;
    for (int i = 4, s = a[0] + a[2]; i < n; i += 2) {
        s += a[i];
        mp1[s].push_back(i);
        ms1.insert({s, i});
        s -= a[i - 4];
    }
    for (int i = 5, s = a[1] + a[3]; i < n; i += 2) {
        s += a[i];
        mp2[s].push_back(i);;
        ms2.insert({s, i});
        s -= a[i - 4];
    }
    int ans = 0;
    for (auto [s, vs] : mp1) {
        int sz1 = sz(vs);
        int sz2 = sz(mp2[s]);
        ans += sz1 * sz2;
    }
    for (int i = 4, s = a[0] + a[2]; i < n; i += 2) {
        s += a[i];
        int off = 0;
        auto it1 = ms1.lower_bound({s, i + 2});
        if (it1->first == s && it1->second == i + 2) off++;
        auto it2 = ms1.lower_bound({s, i + 4});
        if (it2->first == s && it2->second == i + 4) off++;
        ans += sz(mp1[s]) - off;
    }
    for (int i = 5, s = a[1] + a[3]; i < n; i += 2) {
        s += a[i];
        int off = 0;
        auto it1 = ms2.lower_bound({s, i + 2});
        if (it1->first == s && it1->second == i + 2) off++;
        auto it2 = ms2.lower_bound({s, i + 4});
        if (it2->first == s && it2->second == i + 4) off++;
        ans += sz(mp2[s]) - off;
    }
    cout << ans << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
