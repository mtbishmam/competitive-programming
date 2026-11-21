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
    V<pii> a(n); for (auto& [l, r] : a) cin >> l >> r;

    auto chk = [&](int mid) -> bool {
        int ai = mid - 1, bi = 0;
        int cnt = 0;
        rep (i, 0, n) {
            if (a[i].first >= ai && a[i].second >= bi) {
                ai--; bi++;
                cnt++;
            }
        }
        return cnt >= mid;
    };
    int l = 0, r = n, ans = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (chk(mid)) l = mid + 1, ans = mid;
        else r = mid - 1;
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
