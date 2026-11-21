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
    int n, k, z; cin >> n >> k >> z;
    vi a(n); rep(i, 0, n) cin >> a[i];

    vi pre(n); rep(i, 0, n) pre[i] = (i ? pre[i - 1] : 0) + a[i];
    int ans = a[0];
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= min(z, k - i); j++) {
            int cur1, cur2; cur1 = cur2 = pre[i];
            int left = j;
            int right = j - 1;
            if (left + right > k - i) continue;
            cur1 += left * a[i - 1] + right * a[i];
            int rem = k - i - (left + right);
            if (rem) cur1 += pre[i - 1 + rem] - pre[i - 1];
            ans = max(ans, cur1);
        }
        ans = max(ans, pre[i]);
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
