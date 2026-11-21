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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rand(l, r) uniform_int_distribution<ll>(l, r)(rng)

void solve(int cs) {
    int n; cin >> n;
    int k; cin >> k;
    vi a(n), can(n);
    for (int i = 0; i < n; i++) {
        int x, y, z; cin >> x >> y >> z;
        a[i] = x + y + z; int c = 0;
        if (x > y) c = 1;
        if (x > z) c = 1;
        if (y > z) c = 1;
        can[i] = c;
    }
    auto chk = [&](int mid) -> int {
        int have = k;
        rep(i, 0, n) {
            if (a[i] >= mid) continue;
            if (!can[i]) return 0;
            int need = mid - a[i];
            if (need > have) return 0;
            have -= need;
        }
        return 1;
    };
    int mn = *min_element(all(a));
    int l = mn, r = mn + k, ans = mn;
    while (l <= r) {
        int mid = l + r >> 1;
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
