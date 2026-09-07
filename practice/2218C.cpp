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
    n *= 3;
    vi a(n);
    if (n == 3) cout << "3 1 2" << endl;
    else if (n & 1 ^ 1) {
        int x = 1;
        for (int i = 0; i < n; i += 3) a[i] = x++;
        int y = x;
        for (int i = 1; i < n; i += 3) a[i] = y, y += 2;
        for (int i = 2; i < n; i += 3) a[i] = a[i - 1] + 1;
        for (int i = 0; i < n; i++) cout << a[i] << " ";
    }
    else {
        int x = 1;
        for (int i = 0; i < n; i += 3) a[i] = x++;
        int y = x;
        for (int i = 1; i < n; i += 3) a[i] = y, y += 2;
        for (int i = 2; i < n; i += 3) a[i] = a[i - 1] + 1;
        for (int i = 0; i < n; i++) cout << a[i] << " ";
   }
   cout << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
