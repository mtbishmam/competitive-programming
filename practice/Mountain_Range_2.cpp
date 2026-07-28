// author: mtbishmam
#include <bits/stdc++.h>
using namespace std;

#define endl "\n"
#define eb emplace_back
#define ff first
#define ss second
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;

const int N = 2e5 + 1;
int n, a[N], dp[N];
vi idxs[N];
map<int, int> comp;

int lg2_table[N + 1];
int st[20][N]; // st[k][i] = max on [i, i+2^k-1]

void build_sparse_table(int n) {
    // log table
    lg2_table[1] = 0;
    for (int i = 2; i <= n; i++) lg2_table[i] = lg2_table[i / 2] + 1;

    // build base
    for (int i = 0; i < n; i++) st[0][i] = a[i];

    // build up
    for (int k = 1; (1 << k) <= n; k++) {
        for (int i = 0; i + (1 << k) <= n; i++) {
            st[k][i] = max(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
        }
    }
}

inline int range_max(int L, int R) {
    if (L > R) return 0; // invalid
    int len = R - L + 1;
    int k = lg2_table[len];
    return max(st[k][L], st[k][R - (1 << k) + 1]);
}

int f(int i, int l, int r) {
    if (i < 0 || i >= n || l < 0 || l >= n || r < 0 || r >= n || l > r) return 0;
    auto& ret = dp[i];
    if (~ret) return ret;
    ret = 1;

    // Left
    if (i - 1 >= 0) {
        int nl = l, nr = i - 1;
        int mxL = range_max(l, i - 1);
        auto& aL = idxs[mxL];
        for (int j = 0, ll = l, rr = i - 1; j < (int)aL.size(); j++) {
            if (nl <= aL[j] && aL[j] <= nr) {
                if (j + 1 == (int)aL.size()) ret = max(ret, 1 + f(aL[j], max(nl, ll), min(nr, rr)));
                else {
                    rr = aL[j + 1] - 1;
                    ret = max(ret, 1 + f(aL[j], max(nl, ll), min(nr, rr)));
                    ll = aL[j] + 1;
                }
            }
        }
    }

    // Right
    if (i + 1 < n) {
        int nl = i + 1, nr = r;
        int mxR = range_max(i + 1, r);
        auto& aR = idxs[mxR];
        for (int j = 0, ll = i + 1, rr = r; j < (int)aR.size(); j++) {
            if (nl <= aR[j] && aR[j] <= nr) {
                if (j + 1 == (int)aR.size()) ret = max(ret, 1 + f(aR[j], max(nl, ll), min(nr, rr)));
                else {
                    rr = aR[j + 1] - 1;
                    ret = max(ret, 1 + f(aR[j], max(nl, ll), min(nr, rr)));
                    ll = aR[j] + 1;
                }
            }
        }
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i], comp[a[i]] = 1;
    int timer = 0;
    for (auto& [x, y] : comp) y = ++timer;
    for (int i = 0; i < n; i++) a[i] = comp[a[i]], idxs[a[i]].eb(i);

    // Build sparse table
    build_sparse_table(n);

    memset(dp, -1, sizeof(dp));
    int ans = 1, mx = range_max(0, n - 1);
    auto& start = idxs[mx];
    for (int i = 0, ll = 0, rr = n - 1; i < (int)start.size(); i++) {
        if (i + 1 == (int)start.size()) ans = max(ans, f(start[i], ll, n - 1));
        else {
            rr = start[i + 1] - 1;
            ans = max(ans, f(start[i], ll, rr));
            ll = start[i] + 1;
        }
    }
    cout << ans << endl;
    return 0;
}