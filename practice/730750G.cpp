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

int dx[] = {-1, -2, -1, -2, 1, 2, 1, 2};
int dy[] = {-2, -1, 2, 1, -2, -1, 2, 1};

void solve(int cs) {
    int n, m, k; cin >> n >> m >> k;
    V<pii> a(k); for (auto& [x, y] : a) cin >> x >> y;

    sort(all(a)); bool ok = 0;
    for (auto& [x, y] : a)
        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            auto it = lower_bound(all(a), pii{nx, ny});
            if (it != a.end() && it->first == nx && it->second == ny) ok = 1;
        }
    cout << (ok ? "YES" : "NO") << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    #ifdef DeBuG
    cin >> tc;
    #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}