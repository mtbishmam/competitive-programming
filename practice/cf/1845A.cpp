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
    int n, k, x; cin >> n >> k >> x;
    chmin(k, 3);
    if (x == 1) {
        if (k >= 3) {
            int t = 0;
            if (n % 2 == 0) t = n / 2;
            else t = n / 2 - 1;
            int r = n % 2;
            cout << "YES" << endl;
            cout << t + r << endl;
            while (t--) cout << 2 << " ";
            if (r) cout << 3 << " ";
            cout << endl;
        } else if (k >= 2) {
            if (n % 2 == 0) {
                int t = n / 2;
                cout << "YES" << endl;
                cout << t << endl;
                while (t--) cout << 2 << " ";
                cout << endl;
            } else cout << "NO" << endl;
        } else cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        cout << n << endl;
        while (n--) cout << 1 << " ";
        cout << endl;
    }
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
