#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) {
        int n, m, s, d;
        cin >> n >> m >> s >> d;
        --s;
        --d;

        vector<int> u(m), v(m);
        for (int& x : u) { cin >> x; --x; }
        for (int& x : v) { cin >> x; --x; }

        vector<vector<int>> graph(n);
        for (int i = 0; i < m; ++i) {
            graph[u[i]].push_back(v[i]);
            graph[v[i]].push_back(u[i]);
        }

        for (auto& neighbors : graph)
            sort(neighbors.begin(), neighbors.end());

        vector<int> dist(n, -1), parent(n, -1);
        queue<int> q;

        dist[s] = 0;
        parent[s] = s;
        q.push(s);

        while (!q.empty()) {
            int cur = q.front();
            q.pop();

            for (int next : graph[cur]) {
                if (dist[next] == -1) {
                    dist[next] = dist[cur] + 1;
                    parent[next] = cur;
                    q.push(next);
                }
            }
        }

        if (dist[d] == -1) {
            cout << -1 << '\n';
            continue;
        }

        vector<int> path;
        for (int node = d; node != s; node = parent[node])
            path.push_back(node);
        path.push_back(s);
        reverse(path.begin(), path.end());

        cout << dist[d] << '\n';
        for (int node : path)
            cout << node + 1 << ' ';
        cout << '\n';
    }
}