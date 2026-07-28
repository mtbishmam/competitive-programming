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
    string s; cin >> s;
    long long pos; cin >> pos;

    int n = sz(s);
    int del = 0;
    int len = n;

    while (pos > len) {
        pos -= len;
        len--;
        del++;
    }

    string st;

    for (char c : s) {
        while (del > 0 && sz(st) && st.back() > c) {
            st.pop_back();
            del--;
        }
        st.push_back(c);
    }

    while (del > 0) {
        st.pop_back();
        del--;
    }

    cout << st[pos - 1];
}
void solve2(int cs) {
    string s; cin >> s;
    int p; cin >> p;
    int n = sz(s);
    int l = 1, r = n, ans = 0;
    auto get = [&](int m) {
        return (n * (n + 1)) / 2 - (m * (m + 1)) / 2;
    };
    while (l <= r) {
        int m = (l + r) >> 1;
        if (get(m) < p) r = m - 1, ans = m;
        else l = m + 1;
    }
    cout << s[p - get(ans) - 1]; 
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
