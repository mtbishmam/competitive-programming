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
    int k; cin >> k;
    if (n * n == k + 1) cout << "NO" << endl;
    else {
        V<V<char>> a(n, V<char>(n, 'D'));
        int nk = n * n - k;
        if (nk) {
            a[0][0] = 'R';
            a[0][1] = 'L';
            nk -= 2;
        }
        for (int j = 2; j < n && nk; j++, nk--) a[0][j] = 'L';
        for (int i = 1; i < n && nk; i++)
            for (int j = 0; j < n && nk; j++, nk--)
                a[i][j] = 'U';
        cout << "YES" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                cout << a[i][j];
            cout << endl;
        }
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
