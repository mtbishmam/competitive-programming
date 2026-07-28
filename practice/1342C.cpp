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

    auto brute = [&]() {
        for (int a = 1; a <= 10; a++) {
            for (int b = 1; b <= 10; b++) {
                debug(a, b); int cnt = 0;
                for (int i = 0; i <= 100; i++) {
                    if ((i % a) % b != (i % b) % a) {
                        cerr << i << " " << (i % a) % b << " " << (i % b) % a << endl;
                        cnt++;
                    }
                }
                if (cnt) debug(a, b, cnt);
            }
        }
        };
    // brute();
    auto brute2 = [&](int a, int b, int l, int r) {
        int cnt = 0;
        for (int i = l; i <= r; i++) {
            if ((i % a) % b != (i % b) % a) {
                cnt++;
            }
        }
        return cnt;
        };

    auto get = [&](int d, int a) {
        if (d < a) return 0ll;
        return (d / a) * a - (d / a) / 2 * a;
        };

    int T(1);
    cin >> T;
    for (int Ti = 1; Ti <= T; Ti++) {
        int a, b, q;
        cin >> a >> b >> q;
        if (a < b) swap(a, b);
        while (q--) {
            int l, r; cin >> l >> r;
            int x = brute2(a, b, l, r);
            int y = 0;
            if (gcd(a, b) < b) {
                y = get(r, a) - get(l - 1, a);
                if (x != y) {
                    debug(a, b, l, r);
                    debug(x, y);
                    // debug(a, b);
                }
            }
            else cout << y << " ";
        }
        cout << endl;
    }
    return 0;
}

//

/* Lemmas
    * if either a or b is 1, we won't have any solutions
    * if a == b it won't be possible either
    * if gcd(a, b) isn't 1, it's not possible
    * a + (a + b - 1), where a > b
    * it'll start from b onwards
    * (100/ 7) * 7 - (100/7)/2 * 7
    * d / a * a - (d / a) / 2 * a
*/

/* Solutions

*/

/* Analysis
(a, b): 2 7
7 1 0
8 0 1
9 1 0
10 0 1
11 1 0
12 0 1
13 1 0

21 1 0
22 0 1
23 1 0
24 0 1
25 1 0
26 0 1
27 1 0

35 1 0
36 0 1
37 1 0
38 0 1
39 1 0
40 0 1
41 1 0

49 1 0
50 0 1
51 1 0
52 0 1
53 1 0
54 0 1
55 1 0

63 1 0
64 0 1
65 1 0
66 0 1
67 1 0
68 0 1
69 1 0

77 1 0
78 0 1
79 1 0
80 0 1
81 1 0
82 0 1
83 1 0

91 1 0
92 0 1
93 1 0
94 0 1
95 1 0
96 0 1
97 1 0
(a, b, cnt): 2 7 49
*/
