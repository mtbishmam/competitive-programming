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

void solve(int cs) {
    int a, n, m; cin >> a >> n >> m;
    auto pw = [&](this auto&& pw, int a, int n) -> pii {
        if (n == 0) return {1 % m, 0};
        auto [lstterm, sum] = pw(a, n / 2);
        pii ret = {lstterm * lstterm % m, sum * (1 + lstterm) % m};
        if (n & 1) ret = {ret.first * a % m, (ret.second + ret.first * a % m) % m};
        return ret;
    };
    cout << pw(a, n).second << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
