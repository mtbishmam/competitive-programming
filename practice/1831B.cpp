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
    int n;
    cin >> n;
    vi a(n), b(n);
    for (auto& i : a) cin >> i;
    for (auto& i : b) cin >> i;
    
    int ans = 0;
    map<int, vi> mpa, mpb;
    for (int i = 0; i < n; i++) {
        int j = i + 1;
        while (j < n && a[i] == a[j]) j++;
        mpa[a[i]].push_back(j - i); chmax(ans, j - i);
        i = j - 1;
    }
    for (int i = 0; i < n; i++) {
        int j = i + 1;
        while (j < n && b[i] == b[j]) j++;
        mpb[b[i]].push_back(j - i); chmax(ans, j - i);
        i = j - 1;
    }
    for (auto& [x, v] : mpa) {
        sort(all(v));
        sort(all(mpb[x]));
        if (sz(mpb[x])) chmax(ans, v.back() + mpb[x].back());
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
