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
const int N = 3e5 + 1;
const int MOD = 998244353;
void solve(int cs) {
    int n; cin >> n;
    V<vi> a(n/3, vi(3));
    rep(i, 0, n/3) rep(j, 0, 3) cin >> a[i][j];

    int ans = 0, tri = 1;
    rep(i, 0, n/3) {
        sort(all(a[i]));
        dbg(a[i]);
        vi b = a[i];
        b.erase(unique(all(b)), b.end());
        if (sz(b) == 1) tri = tri * 3 % MOD;
        else if (sz(b) == 2) {
            dbg(a[i][0], a[i][1]);
            if (a[i][0] == a[i][1]) tri = tri * 2 % MOD;
            else tri = tri * 1 % MOD;
        } else tri *= 1;
    }
    dbg(tri);
    auto pw = [](int a, int b) {
        int ret = 1;
        while (b) {
            if (b & 1) ret = ret * a % MOD;
            a = a * a % MOD;
            b >>= 1;
        }
        return ret;
    };
    int nn = n / 3;
    ans = tri;
    vi fact(N), ifact(N); fact[0] = fact[1] = 1;
    for (int i = 2; i < N; i++) fact[i] = fact[i - 1] * i % MOD;
    ifact[N - 1] = pw(fact[N - 1], MOD - 2);
    for (int i = N - 2; i >= 0; i--) ifact[i] = ifact[i + 1] * (i + 1) % MOD;
    auto ncr = [&](int n, int r) { return (fact[n] * ifact[n-r] % MOD) * ifact[r] % MOD; };
    ans = ans * ncr(nn, nn / 2) % MOD;
    //ans = (tri * ((nn * (nn - 1)) / 2)) % MOD;
    //ans = ((tri * (nn * (nn - 1) % MOD) % MOD) % MOD * pw(2, MOD - 2)) % MOD;
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
