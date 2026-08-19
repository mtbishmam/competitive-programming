#include "bits/stdc++.h" /** keep-include */
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

template<class I> vi lis(const vector<I>& S) {
    if (S.empty()) return {};
    vi prev(sz(S));
    typedef pair<I, int> p;
    vector<p> res;
    rep(i,0,sz(S)) {
        auto it = lower_bound(all(res), p{S[i], 0});
        if (it == res.end()) res.emplace_back(), it = res.end()-1;
        *it = {S[i], i};
        prev[i] = it == res.begin() ? 0 : (it-1)->second;
    }
    int L = sz(res), cur = res.back().second;
    vi ans(L);
    while (L--) ans[L] = cur, cur = prev[cur];
    return ans;
}

void solve(int cs) {
    int n;
    cin >> n;
    vi a(n);
    for (auto& i : a) cin >> i;

    vi dp(n, -1);
    auto f = [&](auto&& f, int i, int need) -> int {
        if (i == n or a[i] != need) return 0;
        auto& ret = dp[i];
        if (~ret) return ret;

        ret = 0;
        if (a[i] == need) ret = 1 + f(f, i + 1, need + 1);
        ret = max(ret, (a[i] == need) + f(f, i + 1, need));
        return ret;
    };
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, f(f, i, a[i]));
    }
    cout << ans << endl;

    // map<int, int> pos;
    // for (int i = 0; i < n; i++) 
    //     if (!pos.count(i)) pos[i] = i;

    // vi b = a;
    // sort(all(b)); 
    // b.erase(unique(all(b)), b.end());
    // map<int, int> vis;

    // auto find = [&](int cur) -> int {
    //     int ret = 1;
    //     int curpos = pos[cur];
    //     int nxt = cur + 1;
    //     while (pos.count(nxt) && curpos < pos[nxt]) {
    //         vis[nxt] = 1;
    //         curpos = pos[nxt];
    //         ret++;
    //         nxt++;
    //     }
    //     return ret;
    // };
    // int ans = 0;
    // for (int& start : b) {
    //     if (vis[start]) continue;
    //     ans = max(ans, find(start));
    //     vis[start] = 1;
    // }
    // cout << ans << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    #ifdef DeBuG
    cin >> tc;
    #endif
    for(int cs = 1; cs <= tc; cs++) solve(cs);
}
