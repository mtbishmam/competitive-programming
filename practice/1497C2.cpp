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
        int n, k;
        cin >> n >> k;

    }
    return 0;
}

/* Analysis
    ones = n - k;
    min_add = ones / k;
    if (min_add > n / 2) impossible

    10 5
    2 2 2 2 2

    10 4 -> ones = 6, min_add = 1
    1 1 1 1 (2, 3)
    so, 1 3 3 3
    or, 1 1 4 4 -> [get all divisors and proceed from there?]

    11 4 -> ones = 7, min_add = 1
    1 1 1 1
    2 3 3 3, lcm = 6, wrong answer
    1 2 4 4, lcm = 4

    11 3 -> ones = 8, min_add = 2, lim = 5
    3 4 4, lcm = 12, wrong answer
    1 5 5, lcm = 5
*/

/*
    10- 10
        5 5
        1 4 1 4

    10-
        2x1 4x2, k = 3
        2x3 4, k = 4
        2x5, k = 5
        1x2 2x4, k = 6
        1x4 2 2 2, k = 7
        1x6 2 2, k = 8
        1x8 2, k = 9
        1x10, k = 10

    11- 1 10
        1 5 5
        1 1 4 1 4

    12- 12
        6 6, k = 2
        3 3 3 3, k = 4
        3 3 3 1 2, k = 5
        1 2 1 2 1 2 1 2, k = 8

    18- 18, k = 1
        9 9, k = 2
        2 8 8, k = 3
        1 8 1 8, k = 4
        2 4 4 4 4, k = 5
        1 4 4 1 4 4, k = 6
        2 2 2 2 2 4 4, k = 7
        2 2 2 2 2 2 2 4, k = 8
        2 2 2 2 2 2 2 2 2, k = 9
        1 2 2 2 2 1 2 2 2 2, k = 10

    18- 18, k = 1
        9 9, k = 2
        2 8 8, k = 3
        2 4 4 8, k = 4, lcm = 8 // 4 4 4 6, lcm = 12
        2 4 4 4 4, k = 5
        2 2 2 4 4 4, k = 6
        2 2 2 2 2 4 4, k = 7
        2 2 2 2 2 2 2 4, k = 8
        2 2 2 2 2 2 2 2 2, k = 9
        1 2 2 2 2 1 2 2 2 2, k = 10

    15-
        1 2x1 4x3 -> 15, k = 5
        1 2x3 4x2 -> 15, k = 6
        1 2x5 4 -> 15, k = 7
        1 2x7 -> 15, k = 8
        1 1 1 1... 2 -> 15
        1 1 1 1 1... -> 15, k = 15

    21- 1 20
        1 10 10
        1 5 5 5 5



*/
// if n is odd and k = 2, then it's impossible