#include "bits/stdc++.h"
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

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
template <typename T> using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
void solve(int cs) {
    int n; cin >> n;
    V<pii> a(n); vi points;
    rep(i, 0, n) {
        int x, y; cin >> x >> y;
        a[i] = {x, y};
        points.push_back(x);
        points.push_back(y);
    }
    sort(all(points));
    points.erase(unique(all(points)), points.end());
    auto c = [&](int x) { return lower_bound(all(points), x) - points.begin(); };
    for (auto& [x, y] : a) x = c(x), y = c(y);
    sort(all(a));
    int ans = 0; oset<int> os;
    for (int i = n - 1; i >= 0; i--) {
        auto& [x, y] = a[i];
        ans += os.order_of_key(y);
        os.insert(y);
    }
    cout << ans << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}