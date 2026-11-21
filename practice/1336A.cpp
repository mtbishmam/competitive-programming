#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, k;
vector<vector<int>> g, h;
vector<int> par, level;
vector<bool> tourist;
ll ans;

void dfs1(int u) {
    for (int v : g[u]) {
        if (v == par[u]) continue;
        par[v] = u;
        level[v] = 1 + level[u];
        dfs1(v);
    }
}

void assignIndustries() {
    h = g;
    priority_queue<pair<int, int>> pq;
    for (int i = 1; i < n; i++) {
        if (h[i].size() == 1) pq.push(make_pair(level[i], i));
    }
    vector<int> ss(n, 0);
    while (k) {
        auto [d, u] = pq.top();
        pq.pop();
        tourist[u] = 0;
        int p = par[u];
        ss[p] += 1 + ss[u];
        h[p].pop_back();
        if (p and h[p].size() == 1) pq.push(make_pair(level[p] - ss[p], p));
        k--;
    }
}

void dfs2(int u, ll c) {
    if (not tourist[u]) ans += c;
    for (int v : g[u]) {
        if (v != par[u]) dfs2(v, c + tourist[u]);
    }
}

int main() {
    cin >> n >> k;
    g.resize(n);
    for (int _ = 0; _ < n - 1; _++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    par.resize(n, -1), level.resize(n, 0);
    dfs1(0);
    tourist.resize(n, 1);
    assignIndustries();
    dfs2(0, 0);
    cout << ans << '\n';
    return 0;
}

