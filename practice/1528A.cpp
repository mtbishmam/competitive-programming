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
    V<pii> a(n); for (auto& [l, r] : a) cin >> l >> r;
    V<V<int>> g(n); rep(i, 0, n - 1) { int x, y; cin >> x >> y; g[--x].push_back(--y); g[y].push_back(x); }

    V<V<int>> dp(n, V<int>(2, -1));
    auto f = [&](this auto&& f, int u, int j, int p = -1) -> int {
        auto& ret = dp[u][j];
        if (~ret) return ret;

        ret = 0;
        for (auto& v : g[u]) {
            if (v == p) continue;
            int mx, au = (j ? a[u].second : a[u].first);
            mx = abs(au - a[v].first) + f(v, 0, u);
            mx = max(mx, abs(au - a[v].second) + f(v, 1, u));
            ret += mx;
        }
        return ret;
    };
    cout << max(f(0, 0), f(0, 1)) << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
