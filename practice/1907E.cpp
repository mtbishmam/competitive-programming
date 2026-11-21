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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rand(l, r) uniform_int_distribution<ll>(l, r)(rng)

const int N = 1e7 + 10;
int ans[N];
void solve(int cs) {
    int n; cin >> n;
    cout << ans[n] << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);

    vi d(10);
    rep(a, 0, 10) rep(b, 0, 10) rep(c, 0, 10) if (a + b + c <= 9) d[a + b + c]++;
    ans[0] = d[0];
    rep(i, 1, N) {
        int x = i, cur = 1;
        while (x) cur *= d[x % 10], x /= 10;
        ans[i] = cur; 
    }

    auto dsum = [](int x) {
        int s = 0;
        while (x) s += x % 10, x /= 10;
        return s;
    };
//    rep(a, 0, 100)
//        rep(b, 0, 100)
//            rep(c, 0, 100)
//                if (dsum(a) + dsum(b) + dsum(c) == dsum(a + b + c))
//                    cout << a + b + c << " = " << a << " " << b << " " << c << endl;              

    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
