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
ll dp[20][2];
// i-th position
// current digit

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
    auto get = [&](int x) {
        memset(dp, -1, sizeof dp);
        string s = to_string(x);
        auto f = [&](auto&& f, int i, int j, int k) -> int {
            if (i == sz(s)) return k;
            auto& ret = dp[i][j];
            if (~ret) return ret;
            ret = 0;
            int lim = (j ? s[i] - '0' : 9);
            for (int d = 0; d <= lim; d++)
                ret += f(f, i + 1, j && (d == lim), k + d);
            return ret;
            };
        return f(f, 0, 1, 0);
        };
    auto get2 = [&](int x) {
        pii dp2[20][2];
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 2; j++)
                dp2[i][j].ff = -1;
        string s = to_string(x);
        auto f2 = [&](auto&& f2, int i, int j) -> pii {
            auto& ret = dp2[i][j];
            if (i == sz(s)) {
                ret.ff = 0; // the sum
                ret.ss = 1; // the contribution
                return ret;
            }
            if (~ret.ff) return ret;
            ret.ff = 0;
            int lim = (j ? s[i] - '0' : 9);
            for (int d = 0; d <= lim; d++) {
                auto cur = f2(f2, i + 1, j && (d == lim));
                ret.ff += cur.ss * d + cur.ff;
                ret.ss += cur.ss;
            }
            return ret;
            };
        return f2(f2, 0, 1).ff;
        };
    for (int Ti = 1; Ti <= T; Ti++) {
        int a, b;
        while (cin >> a >> b) {
            if (a == -1 & b == -1) break;
            cout << get(b) - get(a - 1) << endl;
            // cout << get2(b) - get2(a - 1) << endl;
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