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
    V<V<int>> g(n);
    rep(i, 0, m) { int x, y; cin >> x >> y; g[--x].push_back(--y); }
    bool cyc = 0; int id = 1; V<int> vis(n);
    auto dfs = [&](this auto&& f, int u) -> void {
        vis[u] = id;
        for (auto& v : g[u]) {
            if (!vis[v]) f(v);
            else if (vis[v] == id) cyc = 1;
        }
    }; rep(i, 0, n) if (!vis[i]) dfs(i), id++;
    cout << (cyc ? "YES" : "NO") << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    #ifdef DeBuG
    cin >> tc;
    #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
