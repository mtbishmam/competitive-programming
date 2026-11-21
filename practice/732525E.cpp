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
    int n, r; cin >> n >> r; --r;
    V<V<int>> g(n);
    rep(i, 0, n - 1) {
        int x, y; cin >> x >> y;
        g[--x].push_back(--y);
        g[y].push_back(x);
    }
    int q; cin >> q;
    vi Q(q); for (auto& i : Q) cin >> i, i--;

    V<bool> vis(n); V<int> sub(n);
    auto dfs = [&](this auto&& f, int u) -> void{
        vis[u] = 1;
        sub[u] = 1;
        for (auto& v : g[u]) if (!vis[v]) f(v), sub[u] += sub[v];
    }; dfs(r);
    rep(i, 0, q) cout << sub[Q[i]] << endl;
    cout << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    #ifdef DeBuG
    cin >> tc;
    #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
