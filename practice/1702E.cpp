#include "bits/stdc++.h"
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
    vvi g(n + 1); vi cnt(n + 1);
    bool ok = 1;
    for (int i = 1; i <= n; i++) {
        int x, y; cin >> x >> y;
        g[x].push_back(y); g[y].push_back(x);
        cnt[x]++, cnt[y]++;
        if (x == y) ok = 0;
    }
    vb vis(n + 1), col(n + 1);
    auto f = [&](this auto&& f, int u, int j) -> int {
        vis[u] = 1;
        col[u] = j;
        for (auto& v : g[u]) {
            if (!vis[v]) return f(v, j ^ 1);
            else if (col[u] == col[v]) return 0;
        }
        return 1;
    };
    for (int i = 1; i <= n; i++) {
        if (cnt[i] > 2) ok = 0;
        if (!vis[i])  ok &= f(i, 0);
    }
    cout << (ok ? "YES" : "NO") << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
