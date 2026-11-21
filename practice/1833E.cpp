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
    vi a(n); for (auto& i : a) cin >> i;

    V<V<int>> g(n);
    rep(i, 0, n) g[i].push_back(--a[i]), g[a[i]].push_back(i);

    int id = 0;
    vi sub(n), subid(n); V<bool> vis(n);
    auto dfs = [&](this auto&& f, int u) -> void {
        vis[u] = 1;
        sub[u] = 1;
        subid[u] = id;
        for (auto& v : g[u]) {
            if (vis[v]) continue;
            f(v);
            sub[u] += sub[v];
        }
    };
    int cc = 0, ccg2 = 0;
    rep(i, 0, n) if (!vis[i]) {
        dfs(i); cc++; id++;
    }
    int len2 = 0; V<bool> vis2(n);
    rep(i, 0, n) {
        if (vis2[subid[i]]) continue;
        if (a[a[i]] == i) {
            len2++;
            vis2[subid[i]] = 1;
        }
    }
    int other = 0;
    rep(i, 0, n) if (!vis2[subid[i]]) {
        other++;
        vis2[subid[i]] = 1;
    }
    int mx = cc;
    int mn = other + (len2 ? 1 : 0);
    cout << mn << " " << mx << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
