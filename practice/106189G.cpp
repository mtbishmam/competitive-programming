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
    vi a(n), b(n), idx(n); iota(all(a), 0);
    b = a;
    rep(i, 0, n) idx[a[i]] = i;
    int cyc = 0, rem = n; vi lst(n, -1);
    dbg(b);
    while (rem) {
        cyc++;
        vi cur[k];
        rep (i, 0, n) cur[i % k].push_back(a[i]);
        int l = 0; bool same = 1;
        rep (i, 0, k) for (int j = sz(cur[i]) - 1; j >= 0; j--) { 
            a[l] = cur[i][j];
            if (a[idx[b[l]]] == b[l] && lst[b[l]] == -1) lst[b[l]] = cyc, rem--;
            same &= b[i] == a[i];
            l++;
        }
        dbg(a);
        if (same) break;
    }
    int ans = 1;
    rep(i, 0, n) ans = lcm(ans, lst[i]);
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
