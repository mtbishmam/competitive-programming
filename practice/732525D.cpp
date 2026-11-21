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

const int INF = 1e9;
void solve(int cs) {
    int n, m; cin >> n >> m;
    int s, e, k; cin >> s >> e >> k;
    V<V<int>> g(n), rg(n); --s, --e, --k;
    rep(i, 0, m) {
        int x, y; cin >> x >> y;
        g[--x].push_back(--y);
        rg[y].push_back(x);
    }

    auto bfs = [&](int u, V<V<int>>& g) -> vi {
        V<bool> vis(n); vis[u] = 1;
        vi dist(n, INF); dist[u] = 0;
        queue<int> q; q.push(u);
        while (sz(q)) {
            int u = q.front();
            q.pop();
            for (auto& v : g[u]) {
                if (!vis[v]) {
                    vis[v] = 1;
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        return dist;
    };
    vi ktos = bfs(k, rg);
    vi etok = bfs(e, rg);

    vi path;
    bool ok = 1;
    int mn = ktos[s] + etok[k];
    if (mn >= INF) ok = 0;
    else {
        V<bool> vis(n);
        auto dfs = [&](this auto&& f, int u, int end, vi& dist) -> void {
            path.push_back(u);
            if (u == end) return;
            vis[u] = 1;
            for (auto& v : g[u]) {
                if (!vis[v] && dist[u] - 1 == dist[v]) {
                    f(v, end, dist);
                    break;
                }
            }
        }; 
        if (s != k && k != e) {
            vi stoe = bfs(s, g);
            // if (ktos[s] + etok[k] != stoe[e]) ok = 0;
            // else {
                dfs(s, k, ktos);
                path.pop_back(); vis = V<bool>(n);
                dfs(k, e, etok);
            // }
        }
        else if (s == k && k == e) path.push_back(k);
        else if (s == k) dfs(k, e, etok);
        else if (e == k) dfs(s, k, ktos);
    }

    if (!ok) cout << -1;
    else {
        cout << mn << endl;
        for (auto& u : path) cout << u + 1 << " ";
    }
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
