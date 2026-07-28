// author: mtbishmam
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <bitset>
#include <algorithm>
#include <numeric>
#include <math.h>
#include <iomanip>
#include <cstring>
#include <cassert>
#include <functional>
#include <chrono>
#include <climits>
using namespace std;

#define endl "\n"
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define lb lower_bound
#define ub upper_bound
#define em emplace
#define V vector
#define int int64_t

template <typename T> istream& operator>>(istream& is, vector<T>& a) { for (auto& i : a) is >> i; return is; }
template <typename T> ostream& operator<<(ostream& os, vector<T>& a) { for (auto& i : a) os << i << " "; return os; };
template <typename T> ostream& operator<<(ostream& os, set<T>& s) { for (auto i : s) os << i << " "; return os; }
template <typename A, typename B> ostream& operator<<(ostream& os, pair<A, B>& i) { return os << i.ff << " " << i.ss; }
void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#define debug(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

using ll = int64_t;
using ld = long double;
using ull = unsigned long long;
using vi = vector<int>; using vvi = vector<vi>;
using vl = vector<ll>; using vvl = vector<vl>;
using vb = vector<bool>; using vvb = vector<vb>;
using vc = vector<char>; using vvc = vector<vc>;
using pii = pair<int, int>; using vpii = vector<pii>;
using pll = pair<ll, ll>; using vpll = vector<pll>;
using vs = vector<string>;
using tiii = tuple<int, int, int>; ; using vtiii = vector<tiii>;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define uniq(x) sort(all(x)), (x).erase(unique(all(x)), (x).end())
#define bug cerr << "!Bugged..." << endl
#define add(x, y) (x + y >= MOD ? x + y - MOD : x + y)
#define mul(x, y) (((x % MOD) * (y % MOD)) % MOD)
#define sz(x) (int)(x).size()

const string ny[] = { "NO", "YES" };
const int dx[8] = { -1,  0, 0, 1, 1,  1, -1, -1 };
const int dy[8] = { 0, -1, 1, 0, 1, -1,  1, -1 };
// const int INF = 2147483647;
// const ll LINF = 9223372036854775807;
const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;
// const int MOD = 998244353;
const double EPS = 1e-9;
const double PI = acos(-1);
const int N = 1e5 + 1;

// #include<ext/pb_ds/assoc_container.hpp>
// #include<ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template<class T, class HLDSegTree>
class HLD {
    int n;
    vector<int> par, heavy, level, root, tree_pos;
    HLDSegTree tree;
private:
    int dfs(const V<V<int>>& graph, int u);
    template<class BinOp>
    void process_path(int u, int v, BinOp op);
public:
    HLD(int n_, const V<V<int>>& graph)
        : n(n_), par(n), heavy(n, -1), level(n), root(n), tree_pos(n), tree(n) {
        par[0] = -1;
        level[0] = 0;
        dfs(graph, 0);
        int ii = 0;
        for (int u = 0; u < n; u++) {
            if (par[u] != -1 && heavy[par[u]] == u) continue;
            for (int v = u; v != -1; v = heavy[v]) {
                root[v] = u;
                tree_pos[v] = ii++;
            }
        }
    }
    void update(int u, int v, T val) {
        process_path(u, v, [this, val](int l, int r) {
            tree.update(l, r, val); });
    }
    T query(int u, int v) {
        T res = T();
        process_path(u, v, [this, &res](int l, int r) {
            res = res + tree.query(l, r); });
        return res;
    }
};
template<class T, class HLDSegTree>
int HLD<T, HLDSegTree>::dfs(const V<V<int>>& graph, int u) {
    int cc = 1, max_sub = 0;
    for (int v : graph[u]) {
        if (v == par[u]) continue;
        par[v] = u;
        level[v] = level[u] + 1;
        int sub = dfs(graph, v);
        if (sub > max_sub) {
            max_sub = sub;
            heavy[u] = v;
        }
        cc += sub;
    }
    return cc;
}
template<class T, class HLDSegTree>
template<class BinOp>
void HLD<T, HLDSegTree>::process_path(int u, int v, BinOp op) {
    for (; root[u] != root[v]; v = par[root[v]]) {
        if (level[root[u]] > level[root[v]]) swap(u, v);
        op(tree_pos[root[v]], tree_pos[v]);
        assert(v != -1);
    }
    if (level[u] > level[v]) swap(u, v);
    op(tree_pos[u], tree_pos[v]);
}

template<class S>
struct lazy_segtree {
    int n; V<S> t;
    lazy_segtree(int n = 0) : n(n), t(2 * n, S()) {}
    void init(const V<S>& v) {
        n = sz(v); t.assign(2 * n, S());
        build(0, 0, n - 1, v);
    } template <typename... T>
        void update(int l, int r, const T&... v) {
        assert(0 <= l && l <= r && r < n);
        update(0, 0, n - 1, l, r, v...);
    }
    S query(int l, int r) {
        assert(0 <= l && l <= r && r < n);
        return query(0, 0, n - 1, l, r);
    }
private:
    inline void push(int u, int b, int e) {
        if (t[u].lazy == 0) return;
        int mid = (b + e) >> 1;
        int rc = u + ((mid - b + 1) << 1);
        t[u + 1].update(b, mid, t[u].lazy);
        t[rc].update(mid + 1, e, t[u].lazy);
        t[u].lazy = 0;
    }
    void build(int u, int b, int e, const V<S>& v) {
        if (b == e) return void(t[u] = v[b]);
        int mid = (b + e) >> 1;
        int rc = u + ((mid - b + 1) << 1);
        build(u + 1, b, mid, v); build(rc, mid + 1, e, v);
        t[u] = t[u + 1] + t[rc];
    } template<typename... T>
        void update(int u, int b, int e, int l, int r, const T&... v) {
        if (l <= b && e <= r) return t[u].update(b, e, v...);
        push(u, b, e);
        int mid = (b + e) >> 1;
        int rc = u + ((mid - b + 1) << 1);
        if (l <= mid) update(u + 1, b, mid, l, r, v...);
        if (mid < r) update(rc, mid + 1, e, l, r, v...);
        t[u] = t[u + 1] + t[rc];
    }
    S query(int u, int b, int e, int l, int r) {
        if (l <= b && e <= r) return t[u];
        push(u, b, e);
        S res;
        int mid = (b + e) >> 1;
        int rc = u + ((mid - b + 1) << 1);
        if (r <= mid) res = query(u + 1, b, mid, l, r);
        else if (mid < l) res = query(rc, mid + 1, e, l, r);
        else res = query(u + 1, b, mid, l, r) + query(rc, mid + 1, e, l, r);
        t[u] = t[u + 1] + t[rc];
        return res;
    }
};
struct node {
    int val = 0, lazy = 0;
    node(int s = 0, int lz = 0) : val(s), lazy(lz) {}
    node operator+(const node& obj) const {
        return { max(val, obj.val), 0 };
    }
    void update(int b, int e, const node& x) {
        val += (e - b + 1) * x.val, lazy += x.val;
    }
};

int32_t main() {
    int n; cin >> n;
    int m; cin >> m;
    vi a(n); cin >> a;
    vvi g(n);
    rep(i, 1, n) {
        int a, b; cin >> a >> b;
        g[--a].eb(--b);
        g[b].eb(a);
    }
    HLD<node, lazy_segtree<node>> hld(n, g);
    rep(i, 0, n) hld.update(i, i, a[i]);
    while (m--) {
        int t; cin >> t;
        if (t == 1) {
            int s; cin >> s; --s;
            int x; cin >> x;
            int p = hld.query(s, s).val;
            hld.update(s, s, x - p);
        }
        else {
            int a, b; cin >> a >> b; --a, --b;
            cout << hld.query(a, b).val << " ";
        }
    }
    return 0;
}