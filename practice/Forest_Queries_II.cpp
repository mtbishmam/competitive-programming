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
// #define int int64_t

template <typename T> istream& operator>>(istream& is, vector<T>& a) { for (auto& i : a) is >> i; return is; }
template <typename T> ostream& operator<<(ostream& os, vector<T>& a) { for (auto& i : a) os << i << " "; return os; };
template <typename T> ostream& operator<<(ostream& os, set<T>& s) { for (auto i : s) os << i << " "; return os; }
template <typename A, typename B> ostream& operator<<(ostream& os, pair<A, B>& i) { return os << i.ff << " " << i.ss; }
void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#define debug(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

using ll = int;
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

struct FT {
    int n; V<ll> s;
    FT(int n) : n(n), s(n) {}
    void update(int i, ll x) { for (; i < n; i |= i + 1) s[i] += x; }
    ll query(int i, ll r = 0) {
        for (; i > 0; i &= i - 1) r += s[i - 1];
        return r;
    }
    int lower_bound(ll sum) {
        if (sum <= 0) return -1; int pos = 0;
        for (int pw = 1 << __lg(n); pw; pw >>= 1)
            if (pos + pw <= n && s[pos + pw - 1] < sum)
                pos += pw, sum -= s[pos - 1];
        return pos;
    }
};

struct FT2 {
    V<vi> ys; V<FT> ft;
    FT2(int limx) : ys(limx) {}
    void fakeUpdate(int x, int y) {
        for (; x < sz(ys); x |= x + 1) ys[x].pb(y);
    }
    void init() { for (vi& v : ys) sort(all(v)), ft.eb(sz(v)); }
    int ind(int x, int y) { return (int)(lower_bound(all(ys[x]), y) - ys[x].begin()); }
    void update(int x, int y, ll dif) {
        for (; x < sz(ys); x |= x + 1) ft[x].update(ind(x, y), dif);
    }
    ll query(int x, int y) {
        ll sum = 0;
        for (; x; x &= x - 1) sum += ft[x - 1].query(ind(x - 1, y));
        return sum;
    }
};

template<class T>
struct fentree {
    T unit = 0;
    int n, m; V<V<T>> t;
    fentree(int n = 0, int m = 0) : n(n), m(m), t(n, V<T>(m, unit)) {}
    void update(int x, int y, T z) {
        for (int i = x; i < n; i += i & -i)
            for (int j = y; j < m; j += j & -j)
                t[i][j] += z;
    }
    T query(int x, int y, T ret = 0) {
        for (int i = x; i > 0; i -= i & -i)
            for (int j = y; j > 0; j -= j & -j)
                ret += t[i][j];
        return ret;
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
        vvi a(n + 1, vi(n + 1));
        fentree<int> bit(n + 1, n + 1);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                char c; cin >> c;
                if (c == '*') {
                    a[i][j] = 1;
                    bit.update(i, j, 1);
                }
            }
        while (q--) {
            int t; cin >> t;
            if (t == 1) {
                int x, y; cin >> x >> y;
                if (a[x][y]) bit.update(x, y, -1);
                else bit.update(x, y, 1);
                a[x][y] ^= 1;
            }
            else {
                int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
                cout << bit.query(x2, y2) - bit.query(x2, y1 - 1) - bit.query(x1 - 1, y2) + bit.query(x1 - 1, y1 - 1) << endl;
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