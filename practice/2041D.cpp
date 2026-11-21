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

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
const int INF = 1e9;
void solve(int cs) {
    int n, m; cin >> n >> m;
    V<V<char>> a(n, V<char>(m));
    for (auto& ai : a) for (auto& i : ai) cin >> i;

    int sx, sy, ex, ey;
    rep(i, 0, n) rep(j, 0, m)
        if (a[i][j] == 'S') sx = i, sy = j;
        else if (a[i][j] == 'T') ex = i, ey = j;

    using state = array<array<int, 4>, 4>;
    V<V<state>> dp(n, V<state>(m));
    rep(i, 0, n) rep(j, 0, m) rep(k, 0, 4) rep(l, 0, 4) dp[i][j][k][l] = INF;
    // int dp[n][m][4][4];
    // memset(dp, -1, sizeof dp);
    auto valid = [&](int x, int y) -> bool { 
        if (0 <= x && x < n && 0 <= y && y < m) {
            if (a[x][y] != '#') return true;
        }
        return false;
    };

    struct node { int x, y, i, j; };
    
    queue<node> q;
    q.push({sx, sy, 0, 0});

    dp[sx][sy][0][0] = 0;

    while (sz(q)) {
        auto [x, y, i, j] = q.front();
        q.pop();

        rep(k, 0, 4) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (!valid(nx, ny)) continue;

            if (i == k) {
                if (j < 3) {
                    if (dp[nx][ny][k][j + 1] <= dp[x][y][i][j] + 1) continue;
                    dp[nx][ny][k][j + 1] = dp[x][y][i][j] + 1;

                    if (nx == ex && ny == ey) continue;
                    q.push({nx, ny, k, j + 1});
                }
            }
            else {
                if (dp[nx][ny][k][1] <= dp[x][y][i][j] + 1) continue;
                dp[nx][ny][k][1] = dp[x][y][i][j] + 1;

                if (nx == ex && ny == ey) continue;
                q.push({nx, ny, k, 1});
            }
        }
    }
    int ans = INF;
    rep(i, 0, 4) rep(j, 0, 4) ans = min(ans, dp[ex][ey][i][j]);
    cout << (ans == INF ? -1 : ans) << endl;

    // auto f = [&](this auto&& f, int x, int y, int i, int j) -> int {
    //     if (x == ex && y == ey) return 0;
    //     auto& ret = dp[x][y][i][j];
    //     if (~ret) return ret;

    //     ret = INF;
    //     rep(k, 0, 4) {
    //         int nx = x + dx[k];
    //         int ny = y + dy[k];
    //         if (!valid(nx, ny)) continue;
    //         if (i == k) {
    //             if (j < 3) {
    //                 ret = min(ret, 1 + f(nx, ny, k, j + 1));
    //             }
    //         }
    //         else {
    //             ret = min(ret, 1 + f(nx, ny, k, 1));
    //         }
    //     }
    //     return ret;
    // };
    // int ans = f(sx, sy, 0, 0);
    // cout << (ans == INF ? -1 : ans) << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    #ifdef DeBuG
    cin >> tc;
    #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
