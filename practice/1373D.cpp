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
const int N = 2e5 + 1;
ll dp[N][3][2];

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
    cin >> T;
    for (int Ti = 1; Ti <= T; Ti++) {
        int n;
        cin >> n;
        vi a(n); cin >> a;
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 2; k++)
                for (int i = 0; i < n; i++)
                    dp[i][j][k] = -LINF;
        auto f = [&](auto&& f, int i, int j, int k) -> int {
            if (i == n) {
                if (j == 1) return -LINF;
                return 0;
            }
            auto& ret = dp[i][j][k];
            if (ret != -LINF) return ret;
            if (j == 0) { // reversals haven't started
                ret = max(ret, (i % 2 == 0 ? a[i] : 0) + f(f, i + 1, 0, 0));
                ret = max(ret, (i % 2 == 1 ? a[i] : 0) + f(f, i + 1, 1, i % 2));
            }
            else if (j == 1) { // reversals have started
                ret = max(ret, (i % 2 == 1 ? a[i] : 0) + f(f, i + 1, 1, k));
                if (i % 2 != k)
                    ret = max(ret, (i % 2 == 1 ? a[i] : 0) + f(f, i + 1, 2, k));
            }
            else if (j == 2) { // reversals have ended
                ret = max(ret, (i % 2 == 0 ? a[i] : 0) + f(f, i + 1, 2, k));
            }
            return ret;
            }; cout << f(f, 0, 0, 0) << endl;
    }
    return 0;
}

//

/* Lemmas

*/

/* Solutions

*/

/* Analysis
    // if we start at partity x and end at parity x then there's no benefit
    // so if we start reversals at parity x, we'll have to end it at the other parity
    dp[N][3][2]
    [3] -> 0 -> reversals haven't started
         1 -> reversals have started
         2 -> reversals have ended
    [2] -> 0 -> reversals started at even position
           1 -> reversals started at odd position
*/