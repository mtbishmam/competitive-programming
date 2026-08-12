#include "bits/stdc++.h"
using namespace std;
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
    vi a(n);
    rep(i, 0, n) {
        cin >> a[i];
    }
    vi divs;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            int x = i, y = n / i;
            divs.push_back(x);
            if (x != y)
                divs.push_back(y);
        }
    }
    int ans = 0;
    for (auto& x : divs) {
        int g = 0;
        for (int i = 0; i < x; i++) {
            for (int j = i; j < n; j += x) {
                g = gcd(g, abs(a[i] - a[j]));
            }
        }
        ans += g != 1;
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