#include <bits/stdc++.h>
using namespace std;


int main() {
    int n, w, h;
    cin >> n >> w >> h;
    struct ob { int w, h, idx; };
    vector<ob> env;
    for (int i = 0; i < n; i++) {
        int wi, hi;
        cin >> wi >> hi;
        if (wi > w && hi > h) env.push_back({ wi, hi, i + 1 });
    }

    if (env.empty()) {
        cout << 0 << endl;
        return 0;
    }

    sort(env.begin(), env.end(), [](ob& a, ob& b) { return (a.w == b.w ? a.h < b.h : a.w < b.w); });

    int m = env.size();
    vector<int> dp(m, 1), prev(m, -1);
    int best = 0, best_idx = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < i; j++) {
            if (env[j].w < env[i].w && env[j].h < env[i].h && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }
        if (dp[i] > best) {
            best = dp[i];
            best_idx = i;
        }
    }
    cout << best << endl;
    vector<int> ans;
    while (best_idx != -1) {
        ans.push_back(env[best_idx].idx);
        best_idx = prev[best_idx];
    }
    reverse(ans.begin(), ans.end());
    for (int x : ans) cout << x << " ";
    cout << endl;
    return 0;
}

/* Gains
    get a really really good understanding of the memory complexity and especially why my n^2 dp wouldn't work
    finalize your understanding of this O(n^2) LIS with O(n) memory
    do this problem again with O(nlogn) LIS with O(n) memory
*/