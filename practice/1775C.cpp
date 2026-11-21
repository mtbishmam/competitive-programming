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
#define rep(i,a,b) for(int i=a; i<(b); ++i)
TT> using V = vector<T>; using vi = V<int>;
using ll = long long; using pii=pair<int,int>;

void solve(int cs) {
    int n, x; cin >> n >> x;

    // int m = n, cur = n;
    // while (cur > x) cur &= m, m++;
    // if (cur == x) cout << m - 1;
    // else cout << -1;
    // cout << endl;

    if (x > n) { cout << -1 << endl; return; }
    if (x == n) { cout << x << endl; return; }
    int ans = 0, other = 0;
    for (int i = 0; i < 64; i++) {
        if ((n & (1ll << i)) && !(x & (1ll << i))) {
            ans = max(ans, i + 1);
        }
        if ((n & (1ll << i)) && (x & (1ll << i))) {
            other += (1ll << i);
        }
        if (!(n & (1ll << i)) && (x & (1ll << i))) {
            ans = -1;
            break;
        }
    }
    cout << (ans == -1 ? -1 : other + (1ll << ans)) << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
