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
    int n; cin >> n;
    V<pii> a(n); for (auto& [l, r] : a) cin >> l >> r, l--, r--;


    V<V<int>> g(n); V<int> cnt(n);
    rep(i, 0, n) { auto&[x, y] = a[i]; cnt[x]++; cnt[y]++; g[x].push_back(y); g[y].push_back(x); }

    V<bool> vis(n), col(n); int ok = 1;
    rep(i, 0, n) if (cnt[i] > 2) ok = 0;
    auto f = [&](this auto&& f, int u, int c = 0) -> void {
        vis[u] = 1;
        col[u] = c;
        for (auto& v : g[u]) 
            if (!vis[v]) f(v, c ^ 1);
            else if (col[u] == col[v]) ok = 0;
    };
    rep(i, 0, n) if (!vis[i]) f(i);
    cout << (ok ? "YES" : "NO") << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
