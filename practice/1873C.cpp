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
    int n = 10;
    V<V<char>> a(n, V<char>(n));
    rep(i, 0, n) rep(j, 0, n) cin >> a[i][j];
    int ans = 0, cur = 1;
    for (int i1 = 0, i2 = n - 1, j1 = 0, j2 = n - 1; i1 <= i2 && j1 <= j2; i1++, i2--, j1++, j2--, cur++) {
        for (int j = 0; j < n; j++) 
            if (a[i1][j] == 'X') ans += cur, a[i1][j] = '.';
        for (int j = 0; j < n; j++) 
            if (a[i2][j] == 'X') ans += cur, a[i2][j] = '.';
        for (int i = 0; i < n; i++) 
            if (a[i][j1] == 'X') ans += cur, a[i][j1] = '.';
        for (int i = 0; i < n; i++) 
            if (a[i][j2] == 'X') ans += cur, a[i][j2] = '.';
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
