#include <bits/stdc++.h>
using namespace std;

const long long NEG = -4e18;
int n;
vector<long long> a;
vector<vector<long long>> dp;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    dp.assign(n + 1, vector<long long>(n + 1, LLONG_MIN));
    auto f = [&](auto&& f, int i, int j) {
        if (i == n) return (j == 0 ? 0 : NEG);

        auto& ret = dp[i][j];
        if (ret != LLONG_MIN) return ret;

        ret = NEG;

        // Case 1: skip potion i
        ret = max(ret, f(f, i + 1, j));

        // Case 2: drink potion i
        long long nxt = f(f, i + 1, j - 1);
        if (j > 0 && nxt != NEG && nxt + a[i] >= 0)
            ret = max(ret, nxt + a[i]);

        return ret;
        };

    int ans = 0;
    for (int j = n; j >= 0; j--) {
        if (f(f, 0, j) >= 0) {
            ans = j;
            break;
        }
    }

    cout << ans << "\n";
}