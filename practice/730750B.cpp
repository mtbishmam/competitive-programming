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
    int n, m; cin >> n >> m;
    vi u(m), v(m), w(m);
    for (auto& i : u) cin >> i;
    for (auto& i : v) cin >> i;
    for (auto& i : w) cin >> i;

    V<V<array<int, 2>>> g(n);
    rep(i, 0, m) g[--u[i]].push_back({--v[i], w[i]});
    rep(i, 0, n) {
        cout << (i + 1) << ": ";
        if(sz(g[i])) rep(j, 0, sz(g[i]))  cout << "(" << g[i][j][0] + 1 << "," << g[i][j][1] << ")" << " ";
        cout << endl;
    }
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    #ifdef DeBuG
    cin >> tc;
    #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
