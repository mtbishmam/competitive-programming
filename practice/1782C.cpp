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
    string s; cin >> s;

    vi div;
    for (int i = 1; i * i <= n; i++) if (n % i == 0) {
        div.push_back(i);
        if (n / i != i) div.push_back(n / i);
    }

    vi freq(26), cnts; rep(i, 0, n) freq[s[i] - 'a']++;
    rep(i, 0, 26) if (freq[i]) cnts.push_back(freq[i]);
    sort(all(cnts));

    int ans = n;
    for (auto& cnt : div) {
        int cur = 0;
        auto ub = upper_bound(all(cnts), cnt);
        auto lb = lower_bound(all(cnts), cnt);
        int len = sz(cnts) - (ub - lb);
        if (ub != cnts.end()) {
            while (ub != cnts.end() && len > 0) cur += *ub - cnt, ub++, len--;
            while (ub != cnts.end()) cur += *ub;
        }
        if (lb == cnts.begin());
        else {
            lb--;
            while (len > 0) {
                cur += cnt - *lb, len--;
                if (lb == cnts.begin()) break;
                lb--;
            }
            if (lb != cnts.begin()) {
                while (lb != cnts.begin()) {
                    lb--;
                    cur += *lb;
                }
            }
        }
        ans = min(ans, cur);
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
