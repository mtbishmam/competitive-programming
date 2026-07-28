#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        long long q;
        cin >> n >> q;
        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        string ans(n, '0');
        long long iq = q;

        for (int i = n - 1; i >= 0; i--) {
            if (a[i] <= iq) {
                ans[i] = '1';
            }
            else if (iq > 0) {
                ans[i] = '1';
                iq--;
            }
        }
        cout << ans << "\n";
    }
}