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
#define int long long

template <typename T> istream& operator>>(istream& is, vector<T>& a) { for (auto& i : a) is >> i; return is; }
template <typename T> ostream& operator<<(ostream& os, vector<T>& a) { for (auto& i : a) os << i << " "; return os; };
template <typename T> ostream& operator<<(ostream& os, set<T>& s) { for (auto i : s) os << i << " "; return os; }
template <typename A, typename B> ostream& operator<<(ostream& os, pair<A, B>& i) { return os << i.ff << " " << i.ss; }
void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#define debug(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

using ll = long long;
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

// Static hashing for 0-indexed string. Intervals are [l,r]. 
template<const ll M, const ll B>
struct Hashing {
    int n; vi h, pw;
    Hashing(const string& s) : n(sz(s)), h(n + 1), pw(n + 1) {
        pw[0] = 1; //^^ s i s 0 indexed
        for (int i = 1; i <= n; ++i)
            pw[i] = (pw[i - 1] * B) % M,
            h[i] = (h[i - 1] * B + s[i - 1]) % M;
    }
    ll eval(int l, int r) {
        // assert(l <= r);
        return (h[r + 1] - ((h[l] * pw[r - l + 1]) % M) + M) % M;
    }
};
struct Double_Hash {
    using H1 = Hashing<916969619, 101>;
    using H2 = Hashing<285646799, 103>;
    H1 h1; H2 h2;
    Double_Hash(const string& s) :h1(s), h2(s) {}
    pii eval(int l, int r) {
        return { h1.eval(l,r), h2.eval(l,r) };
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
        string s, t;
        cin >> s >> t;
        int n = sz(s);
        // Double_Hash sh(s), th(t);
        // auto f = [&](auto&& f, pii& a, pii& b) -> bool {
        //     auto& [l1, r1] = a;
        //     auto& [l2, r2] = b;
        //     int len = r1 - l1 + 1;
        //     if (len % 2) return sh.eval(l1, r1) == th.eval(l2, r2);
        //     if (sh.eval(l1, r1) == th.eval(l2, r2)) return 1;
        //     else {
        //         pii a1 = { l1, l1 + len / 2 - 1 };
        //         pii a2 = { l1 + len / 2, r1 };
        //         pii b1 = { l2, l2 + len / 2 - 1 };
        //         pii b2 = { l2 + len / 2, r2 };
        //         return (f(f, a1, b1) && f(f, a2, b2)) || (f(f, a1, b2) && f(f, a2, b1));
        //     }
        //     };
        // pii a = { 0, n - 1 };
        // pii b = { 0, n - 1 };
        // cout << ny[f(f, a, b)];

        auto f = [&](auto&& f, string s) {
            int n = sz(s);
            if (n & 1) return s;
            string s1 = f(f, s.substr(0, n / 2));
            string s2 = f(f, s.substr(n / 2));
            if (s1 > s2) swap(s1, s2);
            return s1 + s2;
            };
        cout << ny[f(f, s) == f(f, t)];
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