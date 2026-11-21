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
    int n, m, q; cin >> n >> m >> q;
    V<V<int>> g(n);
    rep(i, 0, m) { int x, y; cin >> x >> y; g[--x].push_back(--y); g[y].push_back(x); }

    int id = 0;
    V<int> subid(n); V<bool> vis(n);
    auto dfs = [&](this auto&& f, int u) -> void {
        vis[u] = 1;
        subid[u] = id;
        for (auto& v : g[u]) if (!vis[v]) f(v);
    };
    rep(i, 0, n) if (!vis[i]) dfs(i), id++;
    rep(i, 0, q) { int x, y; cin >> x >> y; cout << (subid[--x] == subid[--y] ? "YES" : "NO") << endl; }
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    #ifdef DeBuG
    cin >> tc;
    #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
