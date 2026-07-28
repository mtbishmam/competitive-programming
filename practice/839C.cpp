#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<long double> prob(n + 1, 0.0L);
    prob[1] = 1.0L;
    long double expected = 0.0L;

    // iterative DFS stack: (node, parent)
    vector<pair<int, int>> st;
    st.emplace_back(1, 0);
    while (!st.empty()) {
        auto [v, p] = st.back();
        st.pop_back();
        int choices = (int)g[v].size();
        if (p != 0) choices--; // exclude parent for non-root
        if (choices == 0) continue; // leaf, no children to propagate to
        for (int u : g[v]) {
            if (u == p) continue;
            prob[u] = prob[v] / (long double)choices;
            expected += prob[u];
            st.emplace_back(u, v);
        }
    }

    cout.setf(std::ios::fixed);
    cout << setprecision(10) << (double)expected << "\n";
    return 0;
}