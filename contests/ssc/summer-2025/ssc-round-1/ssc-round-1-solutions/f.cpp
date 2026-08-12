#include "bits/stdc++.h"
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
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
TT> using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rand(l, r) uniform_int_distribution<ll>(l, r)(rng)

void solve(int cs) {
    int n, k; cin >> n >> k;
    vi a(n); for (auto& i : a) cin >> i;

    oset<pii> os;
    for (int i = 0; i < k; i++) os.insert({a[i], i});

    if (k % 2 == 0) {
        int mid = k / 2;
        int mid2 = k / 2 - 1;
        auto val = *os.find_by_order(mid);
        auto val2 = *os.find_by_order(mid2);
        cout << min(val.first, val2.first) << " ";
    } else {
        int mid = k / 2;
        auto val = *os.find_by_order(mid);
        cout << val.first << " ";
    }
    for (int i = k; i < n; i++) {
        os.erase({a[i-k], i-k});
        os.insert({a[i], i});
        if (k % 2 == 0) {
            int mid = k / 2;
            int mid2 = k / 2 - 1;
            auto val = *os.find_by_order(mid);
            auto val2 = *os.find_by_order(mid2);
            cout << min(val.first, val2.first) << " ";
            os.erase({a[i-k], 0});
        } else {
            int mid = k / 2;
            auto val = *os.find_by_order(mid);
            cout << val.first << " ";
            os.erase({a[0], 0});
        }
    }
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    #ifdef DeBuG
    cin >> tc;
    #endif
    for(int cs = 1; cs <= tc; cs++) solve(cs);
}