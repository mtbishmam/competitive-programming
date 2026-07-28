#include "bits/stdc++.h"
using namespace std;
// 	#include <ext/pb_ds/assoc_container.hpp>
//	#include <ext/pb_ds/tree_policy.hpp>
//	using namespace __gnu_pbds;

#ifndef DeBuG
#define dbg(...)
#define TT template <typename T
#endif

#define int int64_t
#define endl '\n'
#define sz(x) (int) (x).size()
#define all(x) begin(x), end(x)
#define rep(i,a,b) for (int i = a; i < (b); ++i)
TT, class U> bool chmin(T&a,U b){return a>b?(a=b,1):0;}
TT, class U> bool chmax(T&a,U b){return a<b?(a=b,1):0;}
TT> using V = vector<T>; using vi = V<int>;
using ll = long long; using pii=pair<int,int>;
using vb = V<bool>; using vvi = V<vi>;
template <class T> using V = vector<T>;
// template <typename T> using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
void solve(int cs) {
    int n; cin >> n;
    vi a(n); map<int, int> mp;
    rep (i, 0, n) {
        cin >> a[i]; mp[a[i]]++;
    }
    if (sz(mp) == 1) cout << "YES";
    else if (sz(mp) == 2) {
        auto [x, c1] = *mp.begin();
        auto [y, c2] = *mp.rbegin();
        if (abs(c1 - c2) <= 1) cout << "YES";
        else cout << "NO";
    } else cout << "NO";
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
