/**
 * Author: MTB Ishmam
 * Date: 2026-07-01
 * Description: Contest submission template.
 */
#include "bits/stdc++.h" /** keep-include */
using namespace std;
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
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
// TT> using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
// #define rand(l, r) uniform_int_distribution<ll>(l, r)(rng)

struct ob {
    int x, y, z;
};

void solve(int cs) {
    int n, m;
    cin >> n >> m;

    vi a(n), v;
    for (int &x : a) {
        cin >> x;
        v.push_back(x);
    }

    V<ob> r(m);
    for (auto &[x, y, z] : r) {
        cin >> x >> y >> z;
        v.push_back(x);
        v.push_back(y);
        v.push_back(z);
    }

    sort(all(v));
    v.erase(unique(all(v)), v.end());

    auto get = [&](int x) {
        return lower_bound(all(v), x) - v.begin();
    };

    int k = sz(v);
    V<vi> g(k);
    vi need(m, 2), out(m);

    rep(i, 0, m) {
        int x = get(r[i].x);
        int y = get(r[i].y);
        out[i] = get(r[i].z);
        g[x].push_back(i);
        g[y].push_back(i);
    }

    V<char> vis(k);
    queue<int> q;
    int ans = 0;

    for (int x : a) {
        int u = get(x);
        if (!vis[u]) {
            vis[u] = true;
            ++ans;
            q.push(u);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i : g[u]) {
            if (--need[i] == 0) {
                int z = out[i];
                if (!vis[z]) {
                    vis[z] = true;
                    ++ans;
                    q.push(z);
                }
            }
        }
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
