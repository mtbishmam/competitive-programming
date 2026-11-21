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

const int N = 1e3 + 1;
const int K = 1e3 + 1;
const int MOD = 1e9 + 7;
int dp[N][K][2];
void solve(int cs) {
    int n; cin >> n;
    int k; cin >> k;
    memset(dp, -1, sizeof dp);
    auto f = [&](this auto&& f, int i, int k, int j, int n) -> int {
//        dbg(i, k, j);
        if (i < 0 || i >= n) return 0;

        auto& ret = dp[i][k][j];
        if (~ret) return ret;

        ret = 0;
        if (k > 1) ret = ((j == 1 ? 1 : 0) + f(i + 1, k - (j == 1 ? 1 : 0), 0, n)) % MOD;
        if (k > 1) ret = (ret + (j == 0 ? 1 : 0) + f(i - 1, k - (j == 0 ? 1 : 0), 1, n)) % MOD;
        return ret;
    };
    cout << (1 + f(0, k, 0, n)) % MOD << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
