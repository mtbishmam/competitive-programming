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
    V<V<char>> a(n, V<char>(m));
    for (auto& ai : a) for (auto& i : ai) cin >> i;

    int ans = 0;
    V<V<bool>> vis(n, V<bool>(m));
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    auto valid = [&](int x, int y) { return (0 <= x && x < n && 0 <= y && y < m && a[x][y] != '#' && !vis[x][y]); };
    auto dfs = [&](this auto&& f, int x, int y) -> int {
        vis[x][y] = 1;
        int ret = a[x][y] == 'D';
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (!valid(nx, ny)) continue;
            ret += f(nx, ny);
        }
        return ret;
    };
    rep(i, 0, n) rep(j, 0, m) if (valid(i, j)) ans = max(ans, dfs(i, j));
    cout << ans << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    #ifdef DeBuG
    cin >> tc;
    #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
