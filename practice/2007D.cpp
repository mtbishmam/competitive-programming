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
    V<V<int>> g(n);
    rep(i, 0, n - 1) { int x, y; cin >> x >> y; g[--x].push_back(--y); g[y].push_back(x); }
    string s; cin >> s;

    vi leafs;
    auto dfs = [&](this auto&& f, int u, int p = -1) -> void {
        int cnt = 0;
        for (auto& v : g[u]) {
            if (v == p) continue;
            f(v, u); cnt++;
        }
        if (cnt == 0) leafs.push_back(u);
    }; dfs(0);

    int o, z, moves; o = z = moves = 0;
    for (auto& l : leafs) {
        if (s[l] == '1') o++;
        else if (s[l] == '0') z++;
        else moves++;
    }

    dbg(o, z, moves);

    int ans = 0, start = 1;
    if (s[0] == '0') ans = o;
    else if (s[0] == '1') ans = z;
    else ans = max(o, z), start = 0, moves--;
    if (moves && moves & 1) (start ? ans++ : ans--);
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
