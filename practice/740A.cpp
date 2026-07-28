#include <bits/stdc++.h>
using namespace std;
#define int int64_t

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> c(4);
    cin >> c[1] >> c[2] >> c[3];

    int need = (4 - n % 4) % 4;
    if (need == 0) { cout << 0 << "\n"; return 0; }

    const int INF = (int)4e18;
    vector<int> dist(4, INF);
    using P = pair<int, int>;
    priority_queue<P, vector<P>, greater<P>> pq;

    dist[0] = 0;
    pq.push({ 0, 0 });
    while (!pq.empty()) {
        auto [d, v] = pq.top(); pq.pop();
        if (d > dist[v]) continue;
        if (v == need) break;    // optional early stop
        for (int j = 1; j <= 3; ++j) {
            int u = (v + j) % 4;
            if (dist[u] > dist[v] + c[j]) {
                dist[u] = dist[v] + c[j];
                pq.push({ dist[u], u });
            }
        }
    }

    cout << dist[need] << "\n";
    return 0;
}