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
    V<int> u(m), v(m);
    rep(i, 0, m) cin >> u[i];
    rep(i, 0, m) cin >> v[i];

    V<int> in(n), out(n);
    rep(i, 0, m) out[--u[i]]++, in[--v[i]]++;
    rep(i, 0, n) cout << in[i] - out[i] << " ";
    cout << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    #ifdef DeBuG
    cin >> tc;
    #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
