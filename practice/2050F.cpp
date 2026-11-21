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

struct node { // only change here
    ll x;
    node(ll _ = 0) : x(_) {} // identity elem
    friend node operator+(const node &a, const node &b) {
        return node(gcd(a.x, b.x));
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
    int n, q; cin >> n >> q;
    vi a(n); for (auto& i : a) cin >> i;
    V<pii> Q(q); for (auto& [l, r] : Q) cin >> l >> r;

    vi diff(n); segtree<node> sg(n);
    rep(i, 1, n) diff[i] = a[i] - a[i - 1], sg.update(i, diff[i]);
    for (auto& [l, r] : Q) {
        if (l == r) cout << 0 << ' ';
        else cout << sg.query(l, r - 1).x << ' ';
    }
    cout << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
