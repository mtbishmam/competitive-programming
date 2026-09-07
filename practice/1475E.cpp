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

const int MOD = 1e9 + 7;
void solve(int cs) {
    int n, k; cin >> n >> k;
    vi a(n);
    rep(i,0,n) cin >> a[i];

    vi b = a; sort(all(b));
    reverse(all(b));
    int mx = 0; for (int i = 0; i < k; i++) mx += b[i];

    vvi dp(n, vi(k+1, -1));
    auto f = [&](this auto f, int i, int j, int cur) -> int {
        if (i == n) return 0;
        if (cur == 0) return 1;
        auto& ret = dp[i][j];
        if (~ret) return ret;
        ret = f(i+1, j, cur);
        if (j && cur-a[i]>=0) ret = (ret + f(i+1, j-1, cur-a[i])) % MOD;
        return ret;
    };
    int ans = 0;
    for (int i = 0; i < n; i++) ans = (ans + f(i, k, mx)) % MOD;
    cout << ans << endl;
    // cout << f(0, k, mx) << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
