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

const int N = 1000 + 1;
vi fact(N), ifact(N);
const int MOD = 1e9 + 7;
void solve(int cs) {
    int n, k; cin >> n >> k;
    vi a(n);
    rep(i,0,n) cin >> a[i];

    sort(all(a));
    reverse(all(a));
    int mx = 0; rep(i,0,k) mx += a[i];

    map<int, int> mp; rep(i,0,n) mp[a[i]]++;
    int lst = a[k-1];
    int other = 0;
    vi b = a; sort(all(b)); b.erase(unique(all(b)), b.end()); reverse(all(b));
    for (auto& key : b)
        if (key==lst) break;
        else other += mp[key];
    int rem = k - other;
    auto ncr = [&](int n, int r) -> int {
        dbg(n, r);
        dbg(fact[n], ifact[n-r], fact[r]);
        return (fact[n] * ifact[n - r] % MOD * ifact[r]) % MOD;
    };
    int ans = ncr(mp[lst], rem);
    cout << ans << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);

    fact[0] = fact[1] = 1;
    for (int i = 2; i < N; i++) fact[i] = fact[i - 1] * i % MOD;

    auto pw = [&](int a, int b) {
        int ret = 1;
        while (b) {
            if (b & 1) ret = ret * a % MOD;
            a = a * a % MOD;
            b >>= 1;
        }
        return ret;
    };

    ifact[N - 1] = pw(fact[N - 1], MOD - 2);
    for (int i = N - 2; i >= 0; i--) ifact[i] = ifact[i + 1] * (i + 1) % MOD;

    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
