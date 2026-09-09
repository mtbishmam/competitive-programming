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

const int N = 1e6;
vvi g(N*2+1);
vi dp(N*2+1, -1);
void solve(int cs) {
    int n; cin >> n;
    auto f = [&](this auto f, int u) -> int {
        if (u == 1) return dp[1] = 1;
        auto& ret = dp[u];
        if (~ret) return ret;

        ret = u * u;
        for (auto& v : g[u]) {
            ret += f(v);
        }
        if (g[u].size() == 2) {
            int a = g[u][0];
            int b = g[u][1];
            for (auto v : g[a]) {
                if (find(g[b].begin(), g[b].end(), v) != g[b].end()) {
                    ret -= f(v);
                    break;
                }
            }
        }
        return ret;
    };
    cout << f(n) << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);

    int off = 0, lim = 1, n = 2;
    for (int i = 1; i < N; i++, off++) {
        int p = i;
        int lc = 2 * i - off;
        int rc = 2 * i - off + 1;
        g[lc].push_back(p);
        g[rc].push_back(p);

        //dbg(p, lc, rc);
        if (i == lim) {
            off--;
            lim += n;
            n++;
        }
    }

    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
