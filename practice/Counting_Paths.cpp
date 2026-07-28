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
// #define int int64_t

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
struct segtree {
    int n; V<S> t;
    segtree(int n) : n(n), t(2 * n - 1, S()) {}
    void init(const V<S>& v) {
        n = sz(v); t.assign(n + n - 1, S());
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
}; // Hash upto here = 773c09
/* (1) Declaration :
Create a node class. Now, segtree<node> T;
T.init(10) creates everything as node()
Consider using V<node> leaves to build
(2) update(l, r, ...v) : update range [l,r]
order in ...v must be same as node.update() fn */
struct node {
    int val = 0, lazy = 0;
    node(int s = 0, int lz = 0) : val(s), lazy(lz) {}
    node operator+(const node& obj) const {
        return { val + obj.val, 0 };
    }
    void update(int b, int e, const node& x) {
        val += (e - b + 1) * x.val, lazy += x.val;
    }
};

int32_t main()
{
#ifndef ONLINE_JUDGE
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // freopen("error.txt", "a", stderr);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    // cout.tie(NULL);

    int T(1);
    // cin >> T;
    for (int Ti = 1; Ti <= T; Ti++) {
        int n; cin >> n;
        int m; cin >> m;
        vvi g(n);
        rep(i, 1, n) {
            int a, b; cin >> a >> b;
            g[--a].eb(--b);
            g[b].eb(a);
        }
        // HLD<node, segtree<node>> hld(n, g);
        // while (m--) {
        //     int l, r; cin >> l >> r;
        //     hld.update(--l, --r, node(1));
        // }
        // for (int i = 0; i < n; i++) cout << hld.query(i, i).val << " ";
        vi par(n), lvl(n);
        auto f = [&](auto&& f, int u, int p = -1) -> void {
            par[u] = p;
            for (auto& v : g[u]) if (v != p) {
                lvl[v] = lvl[u] + 1;
                f(f, v, u);
            }
            }; f(f, 0);
        vvi jmp(30, vi(n, -1));
        for (int i = 0; i < n; i++) jmp[0][i] = par[i];
        for (int j = 1; j < 30; j++)
            for (int i = 0; i < n; i++) {
                if (jmp[j - 1][i] == -1) continue;
                jmp[j][i] = jmp[j - 1][jmp[j - 1][i]];
            }

        auto jump = [&](int u, int k) {
            for (int i = 0; i < 30; i++)
                if (k & (1 << i)) {
                    u = jmp[i][u];
                    assert(u != -1);
                }
            return u;
            };

        auto lca = [&](int a, int b) {
            if (lvl[a] < lvl[b]) swap(a, b);
            int diff = lvl[a] - lvl[b];
            a = jump(a, diff);
            if (a == b) return a;
            for (int i = 30 - 1; i >= 0; i--)
                if (jmp[i][a] != jmp[i][b]) {
                    a = jmp[i][a];
                    b = jmp[i][b];
                }
            return jmp[0][a];
            };

        vi path(n);
        while (m--) {
            int a, b; cin >> a >> b;
            path[--a]++, path[--b]++;
            int lc = lca(a, b);
            path[lc]--;
            if (par[lc] != -1) path[par[lc]]--;
        }
        auto f2 = [&](auto&& f2, int u, int p = -1) -> void {
            for (auto& v : g[u]) if (v != p) {
                f2(f2, v, u);
                path[u] += path[v];
            }
            }; f2(f2, 0);
        for (int i = 0; i < n; i++) cout << path[i] << ' ';
    }
    return 0;
}

//

/* Lemmas

*/

/* Solutions

*/

/* Analysis

*/