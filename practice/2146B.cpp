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
    int m; cin >> m;

    V<V<int>> a(n);
    map<int, int> mp;
    for (int i = 0; i < n; i++) {
        int l; cin >> l;
        vi v(l); for (auto& i : v) cin >> i, mp[i]++;
        a[i] = v;
    }

    bool x = 1;
    for (int i = 1; i <= m; i++) if (!mp[i]) x = 0;

    int other = 0;
    if (x) for (int i = 0; i < n; i++) {
        auto& v = a[i];

        bool can = 1;
        for (auto& x : v) {
            mp[x]--;
            if (!mp[x]) can = 0;
        }

        if (can) other++;
        for (auto& x : v) mp[x]++;
    }
    if (x && other > 1) cout << "YES" << endl;
    else cout << "NO" << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
