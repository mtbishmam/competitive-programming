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
        int n, en, tn; cin >> n >> en >> tn;
        struct ob { int vi, ei, ti; };
        vector<ob> a(n);
        rep(i, 0, n) {
            int vi, ei, ti;
            cin >> vi >> ei >> ti;
            a[i] = { vi, ei, ti };
        }
        vi ans;
        V<V<V<int>>> dp(n, V<V<int>>(en + 1, vi(tn + 1, -1)));
        auto f = [&](auto&& f, int i, int en, int tn) -> int {
            if (i == n) return 0;
            auto& ret = dp[i][en][tn];
            if (~ret) return ret;

            ret = 0;
            auto& [vi, ei, ti] = a[i];
            int o1 = -INF, o2 = -INF;
            if (en - ei >= 0 && tn - ti >= 0) {
                o1 = vi + f(f, i + 1, en - ei, tn - ti);
            }
            o2 = f(f, i + 1, en, tn);
            ret = max(o1, o2);
            return ret;
            };
        int mx = f(f, 0, en, tn);
        cout << mx << endl;
        if (mx == 0) {
            continue;
        }
        auto f2 = [&](auto&& f2, int i, int en, int tn, int mx) -> int {
            if (i == n) return 0;

            auto& [vi, ei, ti] = a[i];
            int o1 = -INF;
            if (en - ei >= 0 && tn - ti >= 0) o1 = vi + f(f, i + 1, en - ei, tn - ti);
            int o2 = f(f, i + 1, en, tn);
            if (o1 == mx) {
                ans.eb(i);
                f2(f2, i + 1, en - ei, tn - ti, mx - vi);
                return o1;
            }
            else {
                f2(f2, i + 1, en, tn, mx);
                return o2;
            }
            return -1;
            }; f2(f2, 0, en, tn, mx);
        for (auto& i : ans) cout << i + 1 << " ";
        cout << endl;
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