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
        int n, m;
        cin >> n >> m;
        vvc a(n, vc(m));
        int sx, sy; vpii mons, corns;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> a[i][j];
                if (a[i][j] == 'A') {
                    sx = i, sy = j;
                    if (!i or i == n - 1 or !j or j == m - 1) {
                        cout << "YES";
                        exit(0);
                    }
                }
                else if (a[i][j] == 'M') mons.eb(i, j);
                if (!i or i == n - 1 or !j or j == m - 1) corns.eb(i, j);
            }
        }
        queue<pii> mq;
        vvi mdis(n, vi(m, INF));
        vvb mvis(n, vb(m));
        auto misvalid = [&](int x, int y) { return 0 <= x and x < n and 0 <= y and y < m and !mvis[x][y] and a[x][y] != '#'; };
        for (auto& [x, y] : mons) {
            mvis[x][y] = 1;
            mdis[x][y] = 0;
            mq.push({ x, y });
        }

        while (sz(mq)) {
            auto [x, y] = mq.front();
            mq.pop();
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (misvalid(nx, ny)) {
                    mdis[nx][ny] = mdis[x][y] + 1;
                    mvis[nx][ny] = 1;
                    mq.push({ nx, ny });
                }
            }
        }

        queue<pii> q;
        vvi dis(n, vi(m, INF));
        vvb vis(n, vb(m));
        auto isvalid = [&](int x, int y) { return 0 <= x and x < n and 0 <= y and y < m and !vis[x][y] and a[x][y] != '#'; };
        vpii ap; ap.eb(sx, sy);
        for (auto& [x, y] : ap) {
            vis[x][y] = 1;
            dis[x][y] = 0;
            q.push({ x, y });
        }

        while (sz(q)) {
            auto [x, y] = q.front();
            q.pop();
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (isvalid(nx, ny)) {
                    dis[nx][ny] = dis[x][y] + 1;
                    vis[nx][ny] = 1;
                    if (dis[nx][ny] < mdis[nx][ny]) {
                        q.push({ nx, ny });
                    }
                }
            }
        }

        vis = vvb(n, vb(m));
        for (auto& [x, y] : corns) {
            if (dis[x][y] < mdis[x][y]) {
                cout << "YES" << endl;
                int cx = x, cy = y;
                string ans;
                while (1) {
                    for (int i = 0; i < 4; i++) {
                        int nx = cx + dx[i];
                        int ny = cy + dy[i];
                        if (isvalid(nx, ny) and dis[nx][ny] + 1 == dis[cx][cy]) {
                            if (ny - 1 == cy) ans += 'L';
                            else if (ny + 1 == cy) ans += 'R';
                            else if (nx - 1 == cx) ans += 'U';
                            else ans += 'D';
                            cx = nx;
                            cy = ny;
                        }
                    }
                    if (cx == sx and cy == sy) break;
                }
                reverse(all(ans));
                cout << sz(ans) << endl;
                cout << ans;
                exit(0);
            }
        }
        cout << "NO";
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