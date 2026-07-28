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
        int m; cin >> m;
        int n; cin >> n;
        int N = n * 2;
        vvi g(N), rg(N);
        for (int i = 0; i < m; i++) {
            int x, y;
            string s1, s2;
            cin >> s1 >> x >> s2 >> y;
            x--, y--;
            x *= 2; y *= 2; // Visualize adding an extra bit
            if (s1 == "-") x ^= 1;
            if (s2 == "-") y ^= 1;

            // x ∨ y  ⇒  ¬x → y and ¬y → x
            g[x ^ 1].eb(y);
            g[y ^ 1].eb(x);
            rg[y].eb(x ^ 1);
            rg[x].eb(y ^ 1);
        }

        vb vis(N);
        stack<int> topo;
        auto f1 = [&](auto&& f1, int u) -> void {
            vis[u] = 1;
            for (auto& v : g[u]) if (!vis[v]) f1(f1, v);
            topo.push(u);
            };
        for (int i = 0; i < N; i++) if (!vis[i]) f1(f1, i);

        int cid = 0;
        vi comp(N, -1);
        auto f2 = [&](auto&& f2, int u) -> void {
            comp[u] = cid;
            for (auto& v : rg[u]) if (comp[v] == -1) f2(f2, v);
            };
        while (sz(topo)) {
            int u = topo.top(); topo.pop();
            if (comp[u] == -1) f2(f2, u), cid++;
        }

        bool f = 1;
        for (int i = 0; i < N; i += 2) // basically checking if x -> ~x (contradiction)
            if (comp[i] == comp[i ^ 1]) f = 0;

        // if comp[x] > comp[x ^ 1] -> variable x is true
        if (f) for (int i = 0; i < N; i += 2) cout << (comp[i] > comp[i ^ 1] ? "+" : "-") << " ";
        else cout << "IMPOSSIBLE";
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