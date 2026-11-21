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
    vi a(n), b(n), ans;
    rep(i, 0, n) cin >> a[i], b[i] = a[i];
    rep(i, 0, n) rep(j, 0, n - 2) if (a[j] > a[j + 2]) {
        int t = a[j];
        a[j] = a[j + 2];
        a[j + 2] = t;
        ans.push_back(j + 1);
    }
    rep(i, 0, n) rep(j, 0, n - 1) if (b[j] > b[j + 1]) swap(b[j], b[j + 1]);
    bool ok = 1; rep(i, 0, n) ok &= a[i] == b[i];
    if (ok) {
        cout << "YES" << endl;
        cout << sz(ans) << endl;
        for (auto& i : ans) cout << i << " " << i + 2 << endl;
    } else cout << "NO" << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    #ifdef DeBuG
    cin >> tc;
    #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
