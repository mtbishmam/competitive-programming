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

}
signed main() {
    cin.tie(0)->sync_with_stdio(0);

    const int N = 1e6;
    V<V<int>> g(2 * N);
    int nxt = 1, diff = 1, off = 0;
    for (int i = 1; i <= N; i++) {
        if (i == nxt) {
            off--;
            nxt += diff;
            diff++;
        }
        off++;
        // cout << i << " -> " << i * 2 - off << " " << i * 2 + 1 - off << endl;
        int u = i;
        int v1 = i * 2 - off;
        int v2 = i * 2 + 1 - off;
        g[v1].push_back(u);
        g[v2].push_back(u);
    }
    V<int> dp(2 * N);
    for (int v = 1; v <= N; v++) {
        dp[v] = v * v;
        map<int, int> mp;
        for (auto& u : g[v]) {
            dp[v] += dp[u];
            for (auto& u2 : g[u]) {
                mp[u2]++;
            }
        }
        for (auto& [u2, cnt] : mp) {
            if (cnt == 2) dp[v] -= dp[u2];
        }
    }

    int tc = 1;
    cin >> tc;
    for (int cs = 1; cs <= tc; cs++) {
        int n; cin >> n;
        cout << dp[n] << endl;
    }
}
