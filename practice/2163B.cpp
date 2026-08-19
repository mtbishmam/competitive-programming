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

struct nodemx { // only change here
	ll x, idx;
	nodemx(ll _ = LLONG_MIN, ll i = 0) : x(_), idx(i) {} // identity elem
	friend nodemx operator+(const nodemx &a, const nodemx &b) {
        nodemx ret;
        if (a.x > b.x) ret.x = a.x, ret.idx = a.idx;
        else ret.x = b.x, ret.idx = b.idx;
        return ret;
	}
};
struct nodemn { // only change here
	ll x, idx;
	nodemn(ll _ = LLONG_MAX, ll i = 0) : x(_), idx(i) {} // identity elem
	friend nodemn operator+(const nodemn &a, const nodemn &b) {
        nodemn ret;
        if (a.x <  b.x) ret.x = a.x, ret.idx = a.idx;
        else ret.x = b.x, ret.idx = b.idx;
        return ret;
	}
};
template <class T> struct segtree {
	int n; V<T> t;
	segtree(int _ = 0) { init(_); }
	void init(int _) {// init-> HLD, Euler tours
		n = 1; while (n < _) n <<= 1;
		t.assign(2 * n, T());
	}
	void update(int i, T v) { // 0 <= i < n
		for (t[i += n] = v; i >>= 1;)
			t[i] = t[i << 1] + t[i << 1 | 1];
	}
	T query(int l, int r) { // [l, r] && l <= r
		T lc, rc;
		for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) lc = lc + t[l++];
			if (!(r & 1)) rc = t[r--] + rc;
		}
		return lc + rc;
	}
};
void solve(int cs) {
    int n; cin >> n;
    vi a(n); for (auto& i : a) cin >> i;
    string s; cin >> s;

    set<pii> st; bool bad = 0;
    for (int i = 0; i < n; i++) if (s[i] == '1') {
        st.insert({a[i], i});
        if (i == 0 or i == n - 1) bad = 1;
     }
     if (bad) { cout << -1 << endl; return; }

    segtree<nodemn> mntree(n);
    segtree<nodemx> mxtree(n);
    for (int i = 0; i < n; i++) {
        mntree.update(i, {a[i], i});
        mxtree.update(i, {a[i], i});
    }
    vb vis(n); V<pii> ans;
    for (auto p : st) {
        auto [x, idx] = p;
        if (vis[x]) continue;
        auto [L, Li] = mntree.query(0, idx - 1);
        auto [R, Ri] = mxtree.query(idx + 1, n - 1);
        if (L < x && x < R) {
            ans.push_back({Li, Ri});
            for (int i = Li + 1; i < Ri; i++) vis[i] = 1;
        } else { bad = 1; break; }
    }
    if (bad || sz(ans) > 5) { cout << -1 << endl; return; }
    cout << sz(ans) << endl;
    for (auto& [l, r] : ans) cout << l + 1 << " " << r + 1 << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
