#include "bits/stdc++.h"
using namespace std;

#ifndef DeBuG
#define dbg(...)
#define TT template <typename T
#endif

#define int int64_t
// #define endl '\n'
#define sz(x) (int) (x).size()
#define all(x) begin(x), end(x)
#define rep(i,a,b) for(int i=a; i<(b); ++i)
TT> using V = vector<T>; using vi = V<int>;
using ll = long long; using pii=pair<int,int>;

void solve(int cs) {
    int n; cin >> n;
    auto ask = [&](int i, int j) -> int {
        cout << "? " << i << " " << j << endl;
        int x; cin >> x;
        return x;
    };
    vi ans(n + 1, -1);
    int j = 1;
    for (int i = 2; i <= n; i++) {
        int x = ask(j, i);
        int y = ask(i, j);
        if (x < y) ans[i] = y;
        else ans[j] = x, j = i;
    }
    rep(i, 1, n + 1) if (ans[i] == -1) ans[i] = n; 

    cout << "! ";
    rep(i, 1, n + 1) cout << ans[i] << " ";
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
