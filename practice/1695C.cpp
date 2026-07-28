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
// #define int long long

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
        for (auto& ai : a) cin >> ai;
        vvi dpmax(n, vi(m, -MOD)), dpmin(n, vi(m, MOD));
        if ((n + m) % 2 == 0) { cout << "NO" << endl; continue; }
        auto isvalid = [&](int i, int j) { return (0 <= i && i < n && 0 <= j && j < m); };
        auto fmax = [&](auto&& fmax, int i, int j) {
            if (i == n - 1 && j == m - 1) return a[i][j];
            if (i >= n || j >= m) return -MOD;
            auto& ret = dpmax[i][j];
            if (ret != -MOD) return ret;
            ret = max(ret, a[i][j] + fmax(fmax, i, j + 1));
            ret = max(ret, a[i][j] + fmax(fmax, i + 1, j));
            return ret;
            };
        auto fmin = [&](auto&& fmin, int i, int j) {
            if (i == n - 1 && j == m - 1) return a[i][j];
            if (i >= n || j >= m) return MOD;
            auto& ret = dpmin[i][j];
            if (ret != MOD) return ret;
            ret = min(ret, a[i][j] + fmin(fmin, i, j + 1));
            ret = min(ret, a[i][j] + fmin(fmin, i + 1, j));
            return ret;
            };
        int l = fmin(fmin, 0, 0);
        int r = fmax(fmax, 0, 0);
        // debug(l, r);
        if (l <= 0 && 0 <= r) cout << "YES";
        else cout << "NO";
        cout << endl;
    }
    return 0;
}

/*
    solution variations
        1. dp[n][m] as boolean possible?
        1.1. maybe we can use dp to get maximum sum and then minimum sum and any value in between them is possible?
        2. because it's 1's and -1's, we can do something cleaner?
            the number of ones and minus ones need to match
            is there any efficient way to test that?
        3. the path will always be a string of n + m - 1
        4. once we go down, we can't go up anymore

*/