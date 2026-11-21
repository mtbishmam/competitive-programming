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
    int q; cin >> q;
    string s; cin >> s;
    V<pii> Q(q); for (auto& [l, r] : Q) cin >> l >> r;
    string t = "abc"; int j = 0;
    V<V<int>> pre(6, V<int>(n));
    do {
        rep(i, 0, n) pre[j][i] = (i ? pre[j][i - 1] : 0) + (s[i] != t[i % sz(t)]);
        j++;
    } while (next_permutation(all(t)));
    for (auto& [l, r] : Q) {
        int ans = n; l--, r--;
        rep(i, 0, 6) ans = min(ans, pre[i][r] - (l ? pre[i][l - 1] : 0));
        cout << ans << endl;
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