#include "bits/stdc++.h" /** keep-include */
using namespace std;
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
#ifndef DeBuG
#define dbg(...)
#define TT template <typename T
#endif
#define TU TT, typename U>

#define int int64_t
#define endl '\n'
#define sz(x) (int) (x).size()
#define all(x) begin(x), end(x)
#define rep(i,a,b) for(int i=a; i<(b); ++i)
TU bool chmin(T&a,U b){return a>b?(a=b,1):0;}
TU bool chmax(T&a,U b){return a<b?(a=b,1):0;}
TT> using V = vector<T>; using vi = V<int>;
using ll = long long; using pii=pair<int,int>;
using vb = V<bool>; using vvi = V<vi>;
// TT> using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rand(l, r) uniform_int_distribution<ll>(l, r)(rng)

void solve(int cs) {
    int n; cin >> n;
    vvi c(n, vi(2));
    rep(i,0,n) cin >> c[i][0] >> c[i][1];
    vvi g(n);
    rep(i,0,n-1) {
        int x, y;
        cin >> x >> y; x--, y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    vvi dp(n, vi(2, -1));
    auto f = [&](this auto f, int u, int j, int p) -> int {
        if (u == n) return 0;
        auto& ret = dp[u][j];
        if (~ret) return ret;
        ret = 0;
        for (auto& v : g[u]) {
            if (v == p) continue;
            int mx = 0;
            mx = max(mx, abs(c[u][j] - c[v][0]) + f(v, 0, u));
            mx = max(mx, abs(c[u][j] - c[v][1]) + f(v, 1, u));
            ret += mx;
        }
        return ret;
    };
    cout << max(f(0, 0, 0), f(0, 1, 0)) << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for(int cs = 1; cs <= tc; cs++) solve(cs);
}
