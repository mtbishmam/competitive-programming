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

// template<typename T> using V = vector<T>;
// template<class S> struct segtree {
//     int n; V<S> t;
//     void init(int _) { n = _; t.assign(n + n - 1, S()); }
//     void init(const V<S>& v) {
//         n = sz(v); t.assign(n + n - 1, S());
//         build(0, 0, n - 1, v);
//     } template <typename... T>
//         void upd(int l, int r, const T&... v) {
//         assert(0 <= l && l <= r && r < n);
//         upd(0, 0, n - 1, l, r, v...);
//     }
//     S get(int l, int r) {
//         assert(0 <= l && l <= r && r < n);
//         return get(0, 0, n - 1, l, r);
//     }
// private:
//     inline void push(int u, int b, int e) {
//         if (t[u].lazy == 0) return;
//         int mid = (b + e) >> 1, rc = u + ((mid - b + 1) << 1);
//         t[u + 1].upd(b, mid, t[u].lazy);
//         t[rc].upd(mid + 1, e, t[u].lazy);
//         t[u].lazy = 0;
//     }
//     void build(int u, int b, int e, const V<S>& v) {
//         if (b == e) return void(t[u] = v[b]);
//         int mid = (b + e) >> 1, rc = u + ((mid - b + 1) << 1);
//         build(u + 1, b, mid, v); build(rc, mid + 1, e, v);
//         t[u] = t[u + 1] + t[rc];
//     } template<typename... T>
//         void upd(int u, int b, int e, int l, int r, const T&...v) {
//         if (l <= b && e <= r)  return t[u].upd(b, e, v...);
//         push(u, b, e);
//         int mid = (b + e) >> 1, rc = u + ((mid - b + 1) << 1);
//         if (l <= mid) upd(u + 1, b, mid, l, r, v...);
//         if (mid < r) upd(rc, mid + 1, e, l, r, v...);
//         t[u] = t[u + 1] + t[rc];
//     }
//     S get(int u, int b, int e, int l, int r) {
//         if (l <= b && e <= r) return t[u];
//         push(u, b, e);
//         S res; int mid = (b + e) >> 1, rc = u + ((mid - b + 1) << 1);
//         if (r <= mid) res = get(u + 1, b, mid, l, r);
//         else if (mid < l) res = get(rc, mid + 1, e, l, r);
//         else res = get(u + 1, b, mid, l, r) + get(rc, mid + 1, e, l, r);
//         t[u] = t[u + 1] + t[rc];
//         return res;
//     }
// };
// struct node {
//     ll sum = 0, lazy = 0;
//     node(ll s = 0, ll l = 0) : sum(s), lazy(l) {} // write full constructor
//     node operator+ (const node& obj) {
//         return { sum + obj.sum, 0 };
//     }
//     void upd(int b, int e, ll x) {
//         sum += (e - b + 1) * x, lazy += x;
//     }
// };

template<class T>
struct segtree {
    T unit = 0;
    T f(T& a, T& b) { return a + b; }
    int n; vector<T> t;
    segtree(int _n) { init(_n); }
    void init(int _n) {
        n = 1; while (n < _n) n <<= 1;
        t.assign(2 * n, unit);
    }
    void update(int i, T val) {
        t[i += n] = val;
        for (i >>= 1; i >= 1; i >>= 1)
            t[i] = f(t[i << 1], t[i << 1 | 1]);
    }
    T query(int l, int r) {
        T lc = unit, rc = unit;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) lc = f(lc, t[l++]);
            if (r & 1) rc = f(rc, t[--r]);
        }
        return f(lc, rc);
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
        int q; cin >> q;
        vi a(n); cin >> a;
        segtree<int> tree(n);
        for (int i = 0; i < n; i++) tree.update(i, a[i]);
        while (q--) {
            int t; cin >> t;
            if (t == 1) {
                int k, u; cin >> k >> u;
                tree.update(--k, u);
            }
            else {
                int l, r; cin >> l >> r;
                cout << tree.query(--l, --r) << endl;
            }
        }
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