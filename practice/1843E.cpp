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
    int n, m; cin >> n >> m;
    vi l(m), r(m);
    rep(i, 0, m) cin >> l[i] >> r[i];
    int q; cin >> q; vi x(q);
    rep(i, 0, q) cin >> x[i];

    vi a(n + 1);
    auto chk = [&](int q) -> int {
        rep(i, 0, q) a[x[i]]++;
        vi pre(n + 1);
        rep(i, 1, n + 1) pre[i] = pre[i - 1] + a[i];
        bool ok = false;
        rep(i, 0, m) {
            int o = pre[r[i]] - pre[l[i] - 1];
            int z = r[i] - l[i] + 1 - o;
            if (o > z) { ok = true; break; }
        }
        rep(i, 0, q) a[x[i]]--;
        return ok;
    };

    int lo = 1, hi = q, ans = -1;
    while (lo <= hi) {
        int mid = (lo + hi) >> 1;
        if (chk(mid)) hi = mid - 1, ans = mid;
        else lo = mid + 1;
    }
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
