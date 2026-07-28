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
#define V vector
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
vi a;
template<class T>
struct segtree {
    T f(T& a, T& b) { return a + b; }
    int n; V<T> t;
    segtree(int n) : n(n), t(4 * n, 0) {}
    void update(int pos, T val, int i, int l, int r) {
        if (l == r) return void(t[i] = val);
        int mid = (l + r) >> 1;
        if (pos <= mid) update(pos, val, i << 1, l, mid);
        else update(pos, val, i << 1 | 1, mid + 1, r);
        t[i] = f(t[i << 1], t[i << 1 | 1]);
    }
    void update(int pos, int x) { update(pos, x, 1, 0, n - 1); }
    T query(int pos, int i, int l, int r) {
        if (l == r) {
            t[i] = 0;
            return a[l];
        }
        int ret;
        int mid = (l + r) >> 1;
        if (pos <= t[i << 1]) ret = query(pos, i << 1, l, mid);
        else ret = query(pos - t[i << 1], i << 1 | 1, mid + 1, r);
        t[i] = f(t[i << 1], t[i << 1 | 1]);
        return ret;
    }
    T query(int pos) { return query(pos, 1, 0, n - 1); }

    T query2(int L, int R, int i, int l, int r) {
        if (r < L || R < l || R < L) return T();
        if (L <= l && r <= R) return t[i];
        int mid = (l + r) >> 1;
        T lc = query2(L, R, i << 1, l, mid);
        T rc = query2(L, R, i << 1 | 1, mid + 1, r);
        return f(lc, rc);
    }
    T query2(int l, int r) { return query2(l, r, 1, 0, n - 1); }
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
        a = vi(n); cin >> a;
        segtree<int> tree(n);
        for (int i = 0; i < n; i++) tree.update(i, 1);
        vi b(n); cin >> b;
        // for (int i = 0; i < n; i++) {
        //     int x = b[i];
        //     cout << tree.query(x) << " ";
        // }
        for (int i = 0; i < n; i++) {
            int x = b[i];
            int l = 0, r = n - 1, ans = 0;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (x <= tree.query2(0, mid)) r = mid - 1, ans = mid;
                else l = mid + 1;
            }
            tree.update(ans, 0);
            cout << a[ans] << " ";
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