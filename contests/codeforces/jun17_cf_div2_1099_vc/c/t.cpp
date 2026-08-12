#include "bits/stdc++.h"
using namespace std;

#ifndef DeBuG
    #define dbg(...)
#endif

#define int int64_t

#define sz(x) (int) (x).size()
#define all(x) begin(x), end(x)
#define rep(i,a,b) for(int i=a;i<(b);++i)
using ll = long long; using pii = pair<int,int>;
using pll = pair<ll,ll>; using vi = vector<int>;
template<class T> using V = vector<T>;

void solve(int cs) {
    int n; cin >> n;
    vi a(n); for (auto& i : a) cin >> i;
    sort(all(a));
    // int mx = a[0] + 10;
    vi unq = {1};
    for (int i = 0; i < n; i++) {
        int x = a[i];
        unq.push_back(x);
        while (x > 1) {
            if (x & 1) x++;
            else x /= 2;
            unq.push_back(x);
        }
    }
    sort(all(unq));
    unq.erase(unique(all(unq)), unq.end());
    int ans = 1e9;
    for (int k = 0; k < sz(unq); k++) {
        int x = unq[k];

        int cur = 0; bool can = 1;
        for (int i = 0; i < n; i++) {
            int y = a[i];
            while (y != x) {
                if (y & 1) y++;
                else y /= 2;
                cur++;
                if (cur > ans) {
	can = 0;
	break;
                }
                if (x > y && x - y > 1) {
	can = 0;
	break;
                }
            }
            if (!can || y != x || cur > ans) {
	can = 0;
	break;
            }
        }
        if (can)
            ans = min(ans, cur);
    }
    cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int tc = 1;
// #ifdef DeBuG
    cin >> tc;
// #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
    return 0;
}