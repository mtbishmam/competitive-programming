#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    long long sx = 0, sy = 0;
    vector<pair<long long, long long>> obs(n), clues(n);
    for (int i = 0; i < n; ++i) {
        cin >> obs[i].first >> obs[i].second;
        sx += obs[i].first;
        sy += obs[i].second;
    }
    long long sa = 0, sb = 0;
    for (int i = 0; i < n; ++i) {
        cin >> clues[i].first >> clues[i].second;
        sa += clues[i].first;
        sb += clues[i].second;
    }
    long long Tx = (sx + sa) / n;
    long long Ty = (sy + sb) / n;
    cout << Tx << " " << Ty << "\n";
    return 0;
}