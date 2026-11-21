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
    vi u(m), v(m), d(n);
    V<vi> g(n);
    rep(i, 0, m) cin >> u[i];
    rep(i, 0, m) cin >> v[i];

    rep(i, 0, m) {
        --u[i], --v[i];
        g[u[i]].push_back(v[i]);
        g[v[i]].push_back(u[i]);
        d[u[i]]++, d[v[i]]++;
    }

    int odd = 0, s = -1;
    rep(i, 0, n) {
        odd += d[i] & 1;
        if (s == -1 && d[i]) s = i;
    }

    bool ok = odd == 0 || odd == 2;
    if (s != -1) {
        vi vis(n), st = {s};
        vis[s] = 1;
        while (sz(st)) {
            int x = st.back(); st.pop_back();
            for (int y : g[x]) if (!vis[y]) {
                vis[y] = 1;
                st.push_back(y);
            }
        }
        rep(i, 0, n) if (d[i] && !vis[i]) ok = 0;
    }

    cout << (ok ? "YES" : "NO") << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
