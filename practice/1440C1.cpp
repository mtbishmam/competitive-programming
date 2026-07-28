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
        int n, m;
        cin >> n >> m;
        vvi a(n, vi(m));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                char c; cin >> c; a[i][j] = c - '0';
            }
        vvi ans;
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < m; j++) {
                if (j == m - 1) {
                    if (a[i][j]) {
                        a[i][j] ^= 1;
                        a[i + 1][j] ^= 1;
                        a[i + 1][j - 1] ^= 1;
                        ans.push_back({ i, j, i + 1, j, i + 1, j - 1 });
                    }
                }
                else {
                    if (a[i][j]) {
                        a[i][j] ^= 1;
                        a[i][j + 1] ^= 1;
                        a[i + 1][j] ^= 1;
                        ans.push_back({ i, j, i, j + 1, i + 1, j });
                    }
                }
            }
        }
        for (int i = n - 1, j = 0; j < m; j++)
            if (a[i][j]) {
                if (j == m - 1) {
                    a[i][j] ^= 1;
                    ans.push_back({ i, j, i, j - 1, i - 1, j });
                    ans.push_back({ i, j, i - 1, j, i - 1, j - 1 });
                    ans.push_back({ i, j - 1, i - 1, j, i - 1, j - 1 });
                    ans.push_back({ i, j, i, j - 1, i - 1, j - 1 });
                    ans.push_back({ i, j - 1, i - 1, j, i - 1, j - 1 });
                }
                else {
                    a[i][j] ^= 1;
                    ans.push_back({ i, j, i - 1, j, i, j + 1 });
                    ans.push_back({ i, j, i, j + 1, i - 1, j + 1 });
                    ans.push_back({ i, j + 1, i - 1, j + 1, i - 1, j });
                    ans.push_back({ i, j, i - 1, j, i - 1, j + 1 });
                    ans.push_back({ i - 1, j, i - 1, j + 1, i, j + 1 });
                }
            }
        // for (int i = 0; i < n; i++) {
        //     for (int j = 0; j < m; j++) {
        //         cerr << a[i][j] << " ";
        //     }
        //     cerr << endl;
        // }
        cout << sz(ans) << endl;
        for (auto& a : ans) {
            for (int i : a) cout << i + 1 << " ";
            cout << endl;
        }
    }
    return 0;
}

/*

    0 0
    x 0

    1 0
    y 1 (i, j, i - 1, j, i, j + 1)

    1 [1]
    [x 0] (i, j, i, j + 1, i - 1, j + 1)

    0 0
    x 1 (i, j + 1, i - 1, j + 1, i - 1, j)

    1 1
    y 1 (i, j, i - 1, j, i - 1, j + 1)

    0 0
    y 0 (i - 1, j, i - 1, j + 1, i, j + 1)

    ---
    rightmost bottom cell
    0 0
    0 x

    0 [1]
    [1 y] (i, j, i, j - 1, i - 1, j)

    [1 0]
    1 [x] (i, j, i - 1, j, i - 1, j - 1)

    [0 1]
    [0] x (i, j - 1, i - 1, j, i - 1, j - 1)

    [1] 1
    [1 y] (i, j, i, j - 1, i - 1, j - 1)

    [0 0]
    [0] y (i, j - 1, i - 1, j, i - 1, j - 1)

    (n - 1) * m + 5 * m <= 3 * n * m
    nm - m + 5 * m <= 3 * n * m
    nm + 4m <= 3 * n * m
    n + 4 <= 3 * n
    6 <= 6 (as, n >= 2)
*/