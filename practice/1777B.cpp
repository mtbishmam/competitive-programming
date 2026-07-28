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

// Neal Wu
// https://github.com/nealwu/competitive-programming/blob/master/mod/mod_int.cc
template<const int& MOD>
struct _m_int {
    int val;
    _m_int(int64_t v = 0) {
        if (v < 0) v = v % MOD + MOD;
        if (v >= MOD) v %= MOD;
        val = int(v);
    }
    _m_int(uint64_t v) { if (v >= MOD) v %= MOD; val = int(v); }
    _m_int(int v) : _m_int(int64_t(v)) {}
    _m_int(unsigned v) : _m_int(uint64_t(v)) {}

    explicit operator int() const { return val; }
    explicit operator unsigned() const { return val; }
    explicit operator int64_t() const { return val; }
    explicit operator uint64_t() const { return val; }
    explicit operator double() const { return val; }
    explicit operator long double() const { return val; }

    _m_int& operator+=(const _m_int& other) { val -= MOD - other.val; if (val < 0) val += MOD; return *this; }
    _m_int& operator-=(const _m_int& other) { val -= other.val; if (val < 0) val += MOD; return *this; }

    static unsigned fast_mod(uint64_t x, unsigned m = MOD) {
#if !defined(_WIN32) || defined(_WIN64)
        return unsigned(x % m);
#endif
        // Optimized mod for Codeforces 32-bit machines.
        // x must be less than 2^32 * m for this to work, so that x / m fits in an unsigned 32-bit int.
        unsigned x_high = unsigned(x >> 32), x_low = unsigned(x);
        unsigned quot, rem;
        asm("divl %4\n"
            : "=a" (quot), "=d" (rem)
            : "d" (x_high), "a" (x_low), "r" (m));
        return rem;
    }

    _m_int& operator*=(const _m_int& other) { val = fast_mod(uint64_t(val) * other.val); return *this; }
    _m_int& operator/=(const _m_int& other) { return *this *= other.inv(); }

    friend _m_int operator+(const _m_int& a, const _m_int& b) { return _m_int(a) += b; }
    friend _m_int operator-(const _m_int& a, const _m_int& b) { return _m_int(a) -= b; }
    friend _m_int operator*(const _m_int& a, const _m_int& b) { return _m_int(a) *= b; }
    friend _m_int operator/(const _m_int& a, const _m_int& b) { return _m_int(a) /= b; }

    _m_int& operator++() { val = val == MOD - 1 ? 0 : val + 1; return *this; }
    _m_int& operator--() { val = val == 0 ? MOD - 1 : val - 1; return *this; }
    _m_int operator++(int) { _m_int before = *this; ++*this; return before; }
    _m_int operator--(int) { _m_int before = *this; --*this; return before; }
    _m_int operator-() const { return val == 0 ? 0 : MOD - val; }

    friend bool operator==(const _m_int& a, const _m_int& b) { return a.val == b.val; }
    friend bool operator!=(const _m_int& a, const _m_int& b) { return a.val != b.val; }
    friend bool operator<(const _m_int& a, const _m_int& b) { return a.val < b.val; }
    friend bool operator>(const _m_int& a, const _m_int& b) { return a.val > b.val; }
    friend bool operator<=(const _m_int& a, const _m_int& b) { return a.val <= b.val; }
    friend bool operator>=(const _m_int& a, const _m_int& b) { return a.val >= b.val; }

    static const int SAVE_INV = int(1e6) + 5;
    static _m_int save_inv[SAVE_INV];

    static void prepare_inv() {
        // Ensures that MOD is prime, which is necessary for the inverse algorithm below.
        for (int64_t p = 2; p * p <= MOD; p += p % 2 + 1)
            assert(MOD % p != 0);

        save_inv[0] = 0;
        save_inv[1] = 1;
        for (int i = 2; i < SAVE_INV; i++)
            save_inv[i] = save_inv[MOD % i] * (MOD - MOD / i);
    }

    _m_int inv() const {
        if (save_inv[1] == 0) prepare_inv();
        if (val < SAVE_INV) return save_inv[val];
        _m_int product = 1;
        int v = val;
        do {
            product *= MOD - MOD / v;
            v = MOD % v;
        } while (v >= SAVE_INV);
        return product * save_inv[v];
    }

    _m_int pow(int64_t p) const {
        if (p < 0) return inv().pow(-p);
        _m_int a = *this, result = 1;
        while (p > 0) {
            if (p & 1) result *= a;
            p >>= 1;
            if (p > 0) a *= a;
        }
        return result;
    }
    friend ostream& operator<<(ostream& os, const _m_int& m) { return os << m.val; }
};

template<const int& MOD> _m_int<MOD> _m_int<MOD>::save_inv[_m_int<MOD>::SAVE_INV];

// const int MOD = 998244353;
// const int MOD = int(1e9) + 7;
using mod_int = _m_int<MOD>;



vector<mod_int> _factorial = { 1 }, _inv_factorial = { 1 };

void prepare_factorials(int64_t maximum) {
    static int64_t prepared_maximum = 0;

    if (maximum <= prepared_maximum)
        return;

    // Prevent increasing maximum by only 1 each time.
    maximum += maximum / 100;
    _factorial.resize(maximum + 1);
    _inv_factorial.resize(maximum + 1);

    for (int64_t i = prepared_maximum + 1; i <= maximum; i++)
        _factorial[i] = i * _factorial[i - 1];

    _inv_factorial[maximum] = _factorial[maximum].inv();

    for (int64_t i = maximum - 1; i > prepared_maximum; i--)
        _inv_factorial[i] = (i + 1) * _inv_factorial[i + 1];

    prepared_maximum = maximum;
}

mod_int factorial(int64_t n) {
    if (n < 0) return 0;
    prepare_factorials(n);
    return _factorial[n];
}

mod_int inv_factorial(int64_t n) {
    if (n < 0) return 0;
    prepare_factorials(n);
    return _inv_factorial[n];
}

mod_int choose(int64_t n, int64_t r) {
    if (r < 0 || r > n) return 0;
    prepare_factorials(n);
    return _factorial[n] * _inv_factorial[r] * _inv_factorial[n - r];
}

mod_int permute(int64_t n, int64_t r) {
    if (r < 0 || r > n) return 0;
    prepare_factorials(n);
    return _factorial[n] * _inv_factorial[n - r];
}

mod_int inv_choose(int64_t n, int64_t r) {
    assert(0 <= r && r <= n);
    prepare_factorials(n);
    return _inv_factorial[n] * _factorial[r] * _factorial[n - r];
}

mod_int inv_permute(int64_t n, int64_t r) {
    assert(0 <= r && r <= n);
    prepare_factorials(n);
    return _inv_factorial[n] * _factorial[n - r];
}

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

    auto brute = [&](int n) {
        vi a(n); iota(all(a), 1);
        auto inv = [](vi& a) {
            int ret = 0;
            for (int i = 0; i < sz(a); i++)
                for (int j = i + 1; j < sz(a); j++)
                    if (a[i] > a[j]) ret++;
            return ret;
            };
        int ans = 0;
        do {
            vi b = a;
            for (int i = sz(a) - 1; i >= 0; i--) b.eb(a[i]);
            ans += inv(b);
        } while (next_permutation(all(a)));
        return ans;
        };
    auto fact = [&](int n) {
        int ret = 1;
        for (int i = 2; i <= n; i++) ret *= i;
        return ret;
        };

    // for (int i = 1; i <= 8; i++)
        // cout << i << " " << brute(i) << " " << (i - 1) * fact(i) << endl;
        // cout << i << " " << brute(i) << " " << i * fact(i) << endl;
        // cout << i << " " << brute(i) << " " << fact(i) * (i * (i - 1)) << endl;

    int T(1);
    cin >> T;
    for (int Ti = 1; Ti <= T; Ti++) {
        int n; cin >> n;
        mod_int nn = n;
        mod_int ans = factorial(nn.val) * (nn * (nn - 1));
        cout << ans.val << endl;
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

/* Gains

    wrote wrong brute force
*/