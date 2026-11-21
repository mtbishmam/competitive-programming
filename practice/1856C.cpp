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
    int n, k; cin >> n >> k;
    vi a(n); rep(i, 0, n) cin >> a[i];

    auto chk = [&](int mx) -> bool {
        if (a.back() >= mx) return true;
        for (int i = 0; i < n - 1; i++) {
            if (a[i] >= mx) return true;
            int have = k, cmx = mx;
            for (int j = i; j < n; j++) {
                if (a[j] >= cmx) return true;
                else if (j < n - 1) {
                    int need = cmx - a[j];
                    if (need <= have) have -= need, cmx--;
                    else break; 
                }
            }
        }
        return false;
    };

    int l = *min_element(all(a)), r = *max_element(all(a)) + k, ans = 0;
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
