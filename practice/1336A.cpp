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
    int n, k; cin >> n >> k;
    V<vi> g(n);
    rep(i,0,n-1) {
        int x, y; cin >> x >> y; x--, y--;
        g[x].push_back(y); g[y].push_back(x);
    }
    vi con(n), sub(n), dep(n);
    auto f = [&](this auto f, int u, int l, int p) -> void {
        sub[u] = 1;
        dep[u] = l;
        for (auto& v : g[u]) {
            if (v == p) continue;
            f(v, l+1, u);
            sub[u] += sub[v];
        }
        con[u] = sub[u] * dep[u] - (sub[u] - 1) * (dep[u] + 1);
    };
    f(0, 0, 0);
    int ans = 0;
    sort(all(con)); reverse(all(con));
    for (int i = 0; i < k; i++) ans += con[i];
    cout << ans << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    #ifdef DeBuG
    cin >> tc;
    #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
