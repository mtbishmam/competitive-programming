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

const int MXA = 1e3 + 1;
void solve(int cs) {
    int n, k; cin >> n >> k;
    vi a(n), b(n);
    rep(i, 0, n) cin >> a[i];
    rep(i, 0, n) cin >> b[i];

    vi cost(MXA, 1e9);
    cost[0] = cost[1] = 0;
    for (int i = 1; i < MXA; i++) {
        for (int x = 1; x <= i; x++) {
            if (i + i / x >= MXA) continue;
            cost[i + i / x] = min(cost[i + i / x], cost[i] + 1);
        }
    }

    int MXK = n * *max_element(all(cost)) + 1;
    V<V<int>> dp(n, V<int>(MXK, -1));
    auto f = [&](this auto&& f, int i, int j) -> int {
        if (i == n) return 0;
        auto& ret = dp[i][j];
        if (~ret) return ret;

        ret = 0;
        ret = max(ret, f(i + 1, j));
        if (j - cost[a[i]] >= 0) ret = max(ret, b[i] + f(i + 1, j - cost[a[i]]));
        return ret;
    };
    cout << f(0, min(MXK - 1, k)) << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
