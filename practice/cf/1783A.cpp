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
    vi a(n); for (auto& i : a) cin >> i;
    sort(all(a)); reverse(all(a));
    vi b = a; b.erase(unique(all(b)), b.end());
    if (sz(b) == 1) {
        cout << "NO" << endl;
        return;
    }
    if (a[0] == a[1]) 
        for (int i = 2; i < n; i++) {
            if (a[i] != a[1]) {
                swap(a[i], a[1]);
                break;
            }
        }
    
    bool f = 1; int s = 0;
    for (int i = 0; i < n; i++) {
        if (s == a[i]) f = 0;
        s += a[i];
    }
    if (f) {
        cout << "YES" << endl;
        for (auto& i : a) cout << i << " ";
        cout << endl;
    } else cout << "NO" << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
