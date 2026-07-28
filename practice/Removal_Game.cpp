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
// #include <cassert>
#include <functional>
#include <chrono>
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
using vs = vector<string>;
using tiii = tuple<int, int, int>; ; using vtiii = vector<tiii>;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define uniq(x) sort(all(x)), (x).erase(unique(all(x)), (x).end())
#define bug cerr << "!Bugged..." << endl
#define add(x, y) (x + y >= MOD ? x + y - MOD : x + y)
#define mul(x, y) (((x % MOD) * (y % MOD)) % MOD)
#define sz(x) (int)(x).size()

const string cq[2] = { "NO", "YES" };
const int dx[8] = { -1,  0, 0, 1, 1,  1, -1, -1 };
const int dy[8] = { 0, -1, 1, 0, 1, -1,  1, -1 };
const int INF = 1e13;
const ll LINF = 9223372036854775807;
const int MOD = 1e9 + 7;
const int N = 1e5 + 1;

// #include<ext/pb_ds/assoc_container.hpp>
// #include<ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

ll dp[2][5000][5000];

int32_t main()
{
#ifndef ONLINE_JUDGE
    // freopen("input6.txt", "r", stdin);
    // freopen("output6.txt", "w", stdout);
    // freopen("error.txt", "a", stderr);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    // cout.tie(NULL);

    int T(1);
    // cin >> T;
    for (int Ti = 1; Ti <= T; Ti++) {
        int n;
        cin >> n;
        vi a(n); cin >> a;
        memset(dp, -1, sizeof(dp));
        auto f = [&](auto&& f, int flag, int i, int j) -> int {
            if (i == j) return (flag ? 0 : a[i]);
            if (i > j) return 0;
            auto& ret = dp[flag][i][j];
            if (~ret) return ret;
            if (flag) {
                ret = INF;
                if (i + 1 < n) ret = min(ret, f(f, flag ^ 1, i + 1, j));
                if (j - 1 >= 0) ret = min(ret, f(f, flag ^ 1, i, j - 1));
            }
            else {
                ret = -INF;
                if (i + 1 < n) ret = max(ret, a[i] + f(f, flag ^ 1, i + 1, j));
                if (j - 1 >= 0) ret = max(ret, a[j] + f(f, flag ^ 1, i, j - 1));
            }
            return ret;
            };
        cout << f(f, 0, 0, n - 1);

        // for (int i = n - 1; i >= 0; i--)
        //     for (int j = 0; j < n; j++) {
        //         for (int flag = 0; flag < 2; flag++) {
        //             auto& ret = dp[flag][i][j];
        //             if (i == j) {
        //                 ret = flag ? 0 : a[i];
        //                 continue;
        //             }
        //             if (i > j) {
        //                 ret = 0;
        //                 continue;
        //             }
        //             if (flag) {
        //                 ret = INF;
        //                 if (i + 1 < n) ret = min(ret, dp[flag ^ 1][i + 1][j]);
        //                 if (j - 1 >= 0) ret = min(ret, dp[flag ^ 1][i][j - 1]);
        //             }
        //             else {
        //                 ret = -INF;
        //                 if (i + 1 < n) ret = max(ret, a[i] + dp[flag ^ 1][i + 1][j]);
        //                 if (j - 1 >= 0) ret = max(ret, a[j] + dp[flag ^ 1][i][j - 1]);
        //             }
        //         }
        //     }
        // cout << dp[0][0][n - 1];
    }
    return 0;
}