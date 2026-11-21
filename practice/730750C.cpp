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
    int n; cin >> n;
    V<V<int>> a(n, V<int>(n));
    rep(i, 0, n) {
        int k; cin >> k;
        rep(j, 0, k) {
            int x; cin >> x;
            a[i][x] = 1;
        }
    }
    rep(i, 0, n) rep(j, 0, n) cout << a[i][j] << " \n"[j + 1 == n];
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    #ifdef DeBuG
    cin >> tc;
    #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
