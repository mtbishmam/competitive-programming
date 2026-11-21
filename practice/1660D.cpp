#include "bits/stdc++.h"
using namespace std;

#ifndef DeBuG
#define dbg(...)
#define TT template <typename T
#endif

#define int int64_t
#define endl '\n'
#define sz(x) (int) (x).size()
#define all(x) begin(x), end(x)
#define rep(i,a,b) for(int i=a; i<(b); ++i)
TT> using V = vector<T>; using vi = V<int>;
using ll = long long; using pii=pair<int,int>;

void solve(int cs) {
    int n; cin >> n;
    vi a(n); for (auto& i : a) cin >> i;

    if (count(all(a), 0) == n) {
        cout << 0 << " " << n << endl;
        return;
    }
    V<pii> segs;
    for (int i = 0; i < n; i++) {
        int j = i;
        while (j < n && a[j]) j++;
        if (j - i) segs.push_back({i, j - 1});
        i = j;
    }
    V<pair<int, pii>> score;
    for (auto& [l, r] : segs) {
        int cnt2 = count_if(a.begin() + l, a.begin() + r + 1, [](int x) { return abs(x) == 2; });
        int neg = count_if(a.begin() + l, a.begin() + r + 1, [](int x) { return x < 0; });
        dbg(neg);
        if (neg & 1) {
            int L = l, cost1 = 0;
            while (L <= r) {
                cost1 += abs(a[L]) == 2;
                if (a[L] < 0) {
                    L++;
                    break;
                } else L++;
            }
            int R = r, cost2 = 0;
            while (R >= 0){
                cost2 += abs(a[R]) == 2;
                if (a[R] < 0) {
                    R--;
                    break;
                } else R--;
            }
            if (cost1 < cost2) {
                score.push_back({cnt2 - cost1, {L, r}});
            } else {
                score.push_back({cnt2 - cost2, {l, R}});
            }
        } else {
            score.push_back({cnt2, {l, r}});
        }
    }
    dbg(score);
    sort(all(score));
    reverse(all(score));
    auto& [sc, p] = score.front();
    auto& [L, R] = p;
    cout << L << " " << (n - 1) - R << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
