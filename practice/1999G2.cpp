#include "bits/stdc++.h"
using namespace std;

#ifndef DeBuG
#define dbg(...)
#define TT template <typename T
#endif

#define int int64_t
// #define endl '\n'
#define sz(x) (int) (x).size()
#define all(x) begin(x), end(x)
#define rep(i,a,b) for(int i=a; i<(b); ++i)
TT> using V = vector<T>; using vi = V<int>;
using ll = long long; using pii=pair<int,int>;

void solve(int cs) {
    int l = 2, r = 999, ans = -1, t = 7;
    auto ask = [&](int a, int b) -> int {
        cout << "? " << a << " " << b << endl;
        int ret; cin >> ret;
        if (ret == -1) exit(0);
        return ret;
    };
    while (t--) {
        int a = (l + l + r) / 3;
        int b = (l + r + r) / 3;
        int ab = ask(a, b);
        if (ab <= a * b) {
            l = b + 1;
            ans = b + 1;
        } else if (ab >= (a + 1) * (b + 1)) {
            r = a - 1;
            ans = a;
        } else { // ab == a * (b + 1)
            l = a + 1;
            r = b - 1;
            ans = b;
        }
    }
    cout << "! " << ans << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
