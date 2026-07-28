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
    // cin >> T;
    for (int Ti = 1; Ti <= T; Ti++) {
        int n;
        cin >> n;
        vi a(n); cin >> a;
        if (n == 1) {
            cout << "1 1" << endl;
            cout << -a[0] << endl;

            cout << "1 1" << endl;
            cout << 0 << endl;

            cout << "1 1" << endl;
            cout << 0 << endl;
        }
        else if (n == 2) {
            cout << "1 1" << endl;
            cout << -a[0] << endl;

            cout << "2 2" << endl;
            cout << -a[1] << endl;

            cout << "1 1" << endl;
            cout << 0 << endl;
        }
        else {
            cout << "1 1" << endl;
            cout << -a[0] << endl;
            a[0] = 0;

            cout << "2 " << n << endl;
            for (int i = 2; i <= n; i++) {
                cout << (n - 1) * a[i - 1] << " ";
            }
            cout << endl;

            cout << "1 " << n << endl;
            for (int i = 1; i <= n; i++)
                cout << -n * a[i - 1] << " ";
            cout << endl;
        }
    }
    return 0;
}

/* Analysis
    bi % len == 0
    ai + bi = x
    bi = x - ai
    (x - ai) % len == 0
    1 2 3 4 -> len = 4, gcd(ai, len) = 12
    1 + (12) * bi
    2 + (6) * bi
    3 + (4) * bi
    4 + (3) * bi

    1 + (11) * 1
    2 + (5) * 2
    3 + (3) * 3
    4 + (2) * 4


    1 2 3 4 1 -> len = 5, gcd(ai, len) = 60
*/

/* Analysis 2
    Why 3 moves? First move to make equal?
    bi = x - ai
    (x - ai) % len == 0
    (x - ai) = k * len
    x = k * len + ai
    k = (x - ai) / len

*/

/* Analysis 3
    since len = n, we can have atmost n distinct reminaders, if we do we can just pair em with each other


*/

/* Analysis 4
    1 3 2 4
    0 3 2 4
    0 3 6 6
    0 -3 -6 -6


*/


/* Analysis 5
    k * len = bi
    => k * len % bi == 0

    ai + k * len = x
    k * len = x - ai

    get all multiples of len? and then add ai?

*/

/* Analysis 6
    in 3 moves
    2 to n - 1, add -> (n - 1) * ai
                ai = ai + ai(n - 1)
                ai = ai (n)
    1 to n, add -> - ai * n
                ai = ai (n) - ai * n
                ai = 0
*/