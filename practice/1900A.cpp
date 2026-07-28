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
TT, class U> bool chmin(T&a,U b){return a>b?(a=b,1):0;}
TT, class U> bool chmax(T&a,U b){return a<b?(a=b,1):0;}
TT> using V = vector<T>; using vi = V<int>;
using ll = long long; using pii=pair<int,int>;
using vb = V<bool>; using vvi = V<vi>;
void solve(int cs) {
    int n; cin >> n;
    string s; cin >> s;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '#') continue;
        int j = i + 1;
        while (j < n && s[i] == s[j]) j++;
        if (j - i < 3) ans += j - i;
        else { ans = 2; break; }
        i = j - 1;
    }
    cout << ans << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
