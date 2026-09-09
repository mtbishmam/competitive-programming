#include "bits/stdc++.h"
using namespace std;
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
#ifndef DeBuG
#define dbg(...)
#define TT template <typename T
#endif
#define TU TT, typename U>

#define int int64_t
#define endl '\n'
#define sz(x) (int) (x).size()
#define all(x) begin(x), end(x)
#define rep(i,a,b) for(int i=a; i<(b); ++i)
TU bool chmin(T&a,U b){return a>b?(a=b,1):0;}
TU bool chmax(T&a,U b){return a<b?(a=b,1):0;}
TT> using V = vector<T>; using vi = V<int>;
using ll = long long; using pii=pair<int,int>;
using vb = V<bool>; using vvi = V<vi>;
// TT> using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rand(l, r) uniform_int_distribution<ll>(l, r)(rng)

void solve(int cs) {
    int n; cin >> n;
    string s; cin >> s;
    vi div;
    for (int i = 1; i * i <= n; i++)
        if (n % i == 0) {
            div.push_back(n / i);
            if (i != n / i) div.push_back(i);
        }
    map<int, int> mp; rep(i, 0, n) mp[s[i]]++;
    string t = s; sort(all(t)); t.erase(unique(all(t)), t.end());
    sort(all(t), [&](auto& a, auto& b) { return mp[a] > mp[b]; });
    int ans = n;
    for (int& freq : div) {
        int ex = 0, cur = 0; bool ok = true;
        set<char> st; for (char i = 'a'; i <= 'z'; i++) st.insert(i);
        for (auto& c : t) {
            if (mp[c] < freq) {
                int req = freq - mp[c];
                if (req > ex) { ok = false; break; }
                else req -= ex;
            } else ex += mp[c] - freq, cur += mp[c] - freq;
            st.erase(c);
        }
        int rem = sz(st);
        if (rem * freq >= ex);
        else ok = false;
        if (ok) ans = min(ans, cur);
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
