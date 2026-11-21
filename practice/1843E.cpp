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
    V<pii> a(m); rep(i, 0, m) cin >> a[i].first >> a[i].second;
    int q; cin >> q;
    vi Q(q); rep(i, 0, q) cin >> Q[i];

    vi s(n + 1);
    auto chk = [&](int qi) -> bool {
        rep(i, 0, qi) s[Q[i]] = 1;
        vi pre(n + 1); rep(i, 1, n + 1) pre[i] = pre[i - 1] + s[i];
        bool ok = 0;
        for(auto&[l, r] : a) ok |= (pre[r] - pre[l - 1] > (r - l + 1) / 2);
        rep(i, 0, qi) s[Q[i]] = 0;
        return ok;
    };
    int l = 1, r = q, ans = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (chk(mid)) r = mid - 1, ans = mid;
        else l = mid + 1;
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
