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

 auto chk = [](int x) -> void {
        map<int, int> mp;
        for (int i = 1; i <= x + 1; i++) {
            int y = x % i;
            mp[y]++;
        }
        for (auto [val, cnt] : mp) cout << val << " " << cnt << endl;
        cout << endl;
    };

void solve(int cs) {
    int n; cin >> n;
    vi a(n); for (auto& i : a) cin >> i;
    if (cs == 4) for (auto& i : a) chk(i);    
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    
   
//    for (auto x : {8,9}) find(x);
//    for (int i = 1; i <= 20; i++) find(i);

    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
