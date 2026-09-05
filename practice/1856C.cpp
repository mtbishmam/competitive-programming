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
    vi a(n); for (auto& i : a) cin >> i;
    vi b = a;
    int mx = *max_element(all(a));
    auto chk = [&](int x, int j) {
        int ck = k - (x - a[j]);
        for (int i = j + 1; i < n - 1; i++) {
            if (a[i] + 1 >= x) return true;
            int nw = x - 1;
            int req = max((int)0, nw - a[i]);
            if (req == 0) return true;
            if (ck < req) return false;
            ck -= req;
            x = nw;
        }
        return a[n - 1] + 1 >= x;
    };
    for (int i = 0; i < n - 1; i++) {
        int l = a[i], r = a[i] + k, bst = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (chk(mid, i)) bst = mid, l = mid + 1;
            else r = mid - 1;
        }
        mx = max(mx, bst);
    }
    cout << mx << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
