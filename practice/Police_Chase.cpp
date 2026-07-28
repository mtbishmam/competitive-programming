#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vi vector<int>
#define vpii vector<pair<int,int>>
#define rep(i,a,b) for(int i=(a); i<(b); ++i)

struct Dinic {
    struct Edge { int to, rev; ll c, oc; ll flow() { return max(oc - c, 0LL); } };
    vi lvl, ptr, q;
    vector<vector<Edge>> adj;
    Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
    void addEdge(int a, int b, ll c, ll rcap = 0) {
        adj[a].push_back({ b, (int)adj[b].size(), c, c });
        adj[b].push_back({ a, (int)adj[a].size() - 1, rcap, rcap });
    }
    ll dfs(int v, int t, ll f) {
        if (v == t || !f) return f;
        for (int& i = ptr[v]; i < (int)adj[v].size(); i++) {
            Edge& e = adj[v][i];
            if (lvl[e.to] == lvl[v] + 1)
                if (ll p = dfs(e.to, t, min(f, e.c))) {
                    e.c -= p; adj[e.to][e.rev].c += p;
                    return p;
                }
        }
        return 0;
    }
    ll calc(int s, int t) {
        ll flow = 0; q[0] = s;
        rep(L, 0, 31) do {
            lvl = ptr = vi(adj.size());
            int qi = 0, qe = (lvl[s] = 1);
            while (qi < qe && !lvl[t]) {
                int v = q[qi++];
                for (auto& e : adj[v])
                    if (!lvl[e.to] && (e.c >> (30 - L))) q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
            }
            while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
        } while (lvl[t]);
        return flow;
    }
    bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    Dinic d(n + 1); // nodes 1..n
    vector<pair<int, int>> edges(m);

    for (int i = 0;i < m;i++) {
        int a, b; cin >> a >> b;
        edges[i] = { a,b };
        d.addEdge(a, b, 1);  // undirected = add both directions
        d.addEdge(b, a, 1);
    }

    int source = 1, sink = n;
    d.calc(source, sink);

    // find min-cut edges
    vpii ans;
    for (auto [a, b] : edges) {
        if (d.leftOfMinCut(a) && !d.leftOfMinCut(b)) ans.push_back({ a,b });
        else if (d.leftOfMinCut(b) && !d.leftOfMinCut(a)) ans.push_back({ b,a });
    }

    cout << ans.size() << "\n";
    for (auto [a, b] : ans) cout << a << " " << b << "\n";
}