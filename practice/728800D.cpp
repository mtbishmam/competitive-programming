#include "bits/stdc++.h"
using namespace std;

#ifndef DeBuG
#define dbg(...)
#define TT template <typename T
#endif

#define int int64_t
#define endl '\n'
#define sz(x) (int) (x).size()
#define all(x) begin(x), end(x)
#define rep(i,a,b) for(int i=a; i<(b); ++i)
TT> using V = vector<T>; using vi = V<int>;
using ll = long long; using pii=pair<int,int>;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rand(l, r) uniform_int_distribution<ll>(l, r)(rng)

const int MOD = 1e9 + 7;
const int n = 2;
using ob = array<array<int, n>, n>;
void solve(int cs) {
    ob a{};
    rep(i, 0, n) rep(j, 0, n) cin >> a[i][j];
    int x; cin >> x;

    auto mul = [&](const ob& a, const ob& b) -> ob {
        ob ret{};
        rep(i, 0, n) rep(j, 0, n) rep(k, 0, n) ret[i][j] = (ret[i][j] + 1ll * a[i][k] * b[k][j] % MOD) % MOD;
        return ret;
    };
    auto pw = [&](ob a, int b) -> ob {
        ob ret{};
        rep(i, 0, n) ret[i][i] = 1;
        while (b) {
            if (b & 1) ret = mul(ret, a);
            a = mul(a, a);
            b >>= 1;
        }
        return ret;
    };

    ob ans = pw(a, x);
    rep(i, 0, n) rep(j, 0, n) cout << ans[i][j] << " \n"[j + 1 == n];
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}

