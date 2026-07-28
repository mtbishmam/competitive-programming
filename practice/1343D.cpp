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
        vi a(n); cin >> a;
        vi sums_gk, sums_lk;
        map<int, int> mp1, mp2; int lk, gk; lk = gk = 0;
        for (int i = 0; i < n / 2; i++) {
            int sum = (a[i] + a[n - i - 1]);
            if (sum <= k) {
                mp1[sum]++;
                sums_lk.eb(sum);
                lk++;
            }
            else {
                mp2[sum]++;
                sums_gk.eb(sum);
                gk++;
            }
        }
        int ans = INF; sort(all(sums_gk)); sort(all(sums_lk));
        for (auto& [sum, cnt] : mp1) {
            ans = min(ans, (lk - cnt) + 2 * gk);
        }
        for (auto& [sum, cnt] : mp2) {
            // int less = lb(all(sums_gk), sum) - sums_gk.begin();
            int big = sz(sums_gk) - (ub(all(sums_gk), sum) - sums_gk.begin());
            int lbb = sum - (k - 1);
            // int less = (n / 2 - (ub(all(sums_gk), lbb) - sums_gk.begin()));
            int idx = ((ub(all(sums_lk), lbb) - sums_lk.begin()));
            int one_move = sz(sums_lk) - idx;
            int two_move = idx;
            ans = min(ans, big + 2 * two_move + one_move);
            /*
            k = 8
            3 2 9 9 10 10 10 16 16

            k + 1 <= k + k
            k + 1 <= k + k - (k - 1)
            k + 1 <= k + 1

            */
            // ans = min(ans, (big - cnt) / 2 + 2 * less);
        }
        cout << ans << endl;
    }
    return 0;
}

//

/* Lemmas
    1. If k wasn't a factor, we'd count the sum of all a[i] + a[j] and go with the maximum
        but, because k is a factor, some pair of a[i] & a[j] which isn't the maximum might require 2 replacements as opposed to one
    2. Maybe we'll have two answers?
        Maybe need to check for two things?
            For the values where a[i] + a[j] <= k
            & for the values where a[i] + a[j] > k
*/

/* Solutions

*/

/* Analysis
    mx(a[i] + a[j]) = 2 * k
    mn(a[i] + a[j]) = 2
    k = 7,
        111 7777 111,   ak = 7, ans = 6
                        ak = 2, ans = 4

    k = 7,
        777 1111 777,   ak = 7, ans = 4
                        ak = 2, ans = 6

    k = 6,
        5 2 6 1 3 4,
        (2 + 3) = 5     ak = 5, ans = 2
        (5 + 4) = 9
        (6 + 1) = 7
*/