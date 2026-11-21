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

void solve(int cs) {
    string s; cin >> s;
    int n = sz(s), x; cin >> x;

    int N = n, del = 0; while (x > N) x -= N, N--, del++;
    V<char> v; 
    for (int i = 0; i < n; i++) {
        while (del > 0 && sz(v) && v.back() > s[i]) {
            v.pop_back();
            del--;
        }
        v.push_back(s[i]);
    }
    while (del > 0) v.pop_back(), del--;
    cout << v[x-1];
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
