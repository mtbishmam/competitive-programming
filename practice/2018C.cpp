#include "bits/stdc++.h"
#include <cassert>
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

const int INF = 1e9;
void solve(int cs) {
    int n; cin >> n;
    V<V<int>> g(n); rep(i, 0, n - 1) { int x, y; cin >> x >> y; g[--x].push_back(--y); g[y].push_back(x); }

    V<V<int>> lvl(n);
    vi dep(n), sub(n); 
    V<bool> vis(n), leaf(n);
    auto dfs1 = [&](this auto&& f, int u, int d = 0, int p = -1) -> void {
        vis[u] = 1;
        dep[u] = d;
        sub[u] = 1;
        lvl[d].push_back(u);
        for (auto& v : g[u]) {
            if (vis[v]) continue;
            f(v, d + 1, u);
            sub[u] += sub[v];
        }
        if (sub[u] == 1) leaf[u] = 1;
    }; dfs1(0);

    V<set<int>> vs(n);
    rep(i, 0, n) for (auto& v : g[i]) vs[i].insert(v);
    auto bfs = [&](int nd) -> int {
        int ret = 1;
        queue<int> q; q.push(nd);
        while (sz(q)) {
            int u = q.front();
            q.pop();

            for (auto v : vs[u]) {
                vs[v].erase(u);
                if (sz(vs[v]) == 1 && v != 0) ret++, q.push(v);
            } 
            vs[u].clear();
        }
        return ret;
    };

    vi cost(n, INF), pre(n);
    rep(i, 0, n) {
        cost[i] = 0;
        if (i) {
            for (auto& p : lvl[i - 1]) {
                if (leaf[p]) pre[i] += bfs(p);
            }
            pre[i] += pre[i - 1];
            cost[i] += pre[i];
        }
        if (i + 1 < n) for (auto& v : lvl[i + 1]) cost[i] += sub[v];
    }
    int ans = *min_element(all(cost));
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
