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
    int n, m; cin >> n >> m;
    vi u(m), v(m);
    rep(i, 0, m) cin >> u[i];
    rep(i, 0, m) cin >> v[i];

    V<V<int>> g(n);
    rep(i, 0, m) g[--u[i]].push_back(--v[i]), g[v[i]].push_back(u[i]);
    V<bool> vis(n);
    auto dfs = [&](this auto&& f, int u) -> void {
        vis[u] = 1; cout << u + 1 << " ";
        for (auto& v : g[u]) if (!vis[v]) f(v);
    }; dfs(0);
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