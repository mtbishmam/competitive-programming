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
const int MOD = 998244353;
void solve(int cs) {
    int n; cin >> n; 
    int sm, other; sm = other = 0; set<int> s;
    rep(i, 0, n / 3) {
        int x, y, z; cin >> x >> y >> z;
        s.insert(x);
        s.insert(y);
        s.insert(z);
        if (sz(s) == 1) sm++;
        else other++;
        s.clear();
    }
    int ans = (n * (n - 1)) / 2;
    ans = (ans % MOD * sm * 6) % MOD;
    ans = (ans * other * 2) % MOD;
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
