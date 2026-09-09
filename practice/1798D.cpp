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

    vi pos, neg; rep(i, 0, n) (a[i] >= 0 ? pos.push_back(a[i]) : neg.push_back(a[i]));

    sort(all(pos));
    for (auto& i : neg) i *= -1;
    sort(all(neg));
    vi ans(n); int i = 0, j = 0, k = 0, si = 0, sj = 0;
    for (; i < sz(pos) && j < sz(neg); ) {
       int x = pos[i], y = neg[j];
       if (si + x <= y) {
            si += x;
            ans[k++] = x;
            i++;
       } else {
           ans[k++] = -y;
           ans[k++] = x;
           si = x;
           j++;
           i++;
       }
    }
    while (j < sz(neg)) ans[k++] = -neg[j++];
    while (i < sz(pos)) ans[k++] = pos[i++];
    auto chk = [](vi& a) {
        vi b = a; for (auto& i : b) i *= -1;
        int mx = *max_element(all(a)), mn = *min_element(all(a));
        auto kad = [](vi& a) {
            int cur = a[0], mx = a[0];
            rep(i, 1, sz(a)) {
                cur = max(a[i], a[i] + cur);
                mx = max(mx, cur);
            }
            return mx;
        };
        int mxx = max(kad(a), kad(b));
        return mxx < mx - mn;
    };
    if (chk(ans)) {
        cout << "Yes" << endl;
        for (auto& i : ans) cout << i << " ";
        cout << endl;
    } else cout << "No" << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
