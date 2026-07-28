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

template <typename T> istream& operator>>(istream& is, vector<T>& a) { for (auto& i : a) is >> i; return is; }
template <typename T> ostream& operator<<(ostream& os, vector<T>& a) { for (auto& i : a) os << i << " "; return os; };
template <typename T> ostream& operator<<(ostream& os, set<T>& s) { for (auto i : s) os << i << " "; return os; }
// template <typename T> ostream& operator<<(ostream &os, const vector<T>& v) { os << '{'; string s; for (const auto &x : v) os << s << x, s = " "; return os << '}'; }
template <typename A, typename B> istream& operator>>(istream& is, pair<A, B>& i) { return is >> i.ff >> i.ss; }
template <typename A, typename B> ostream& operator<<(ostream& os, pair<A, B>& i) { return os << i.ff << " " << i.ss; }
template <typename A, typename B> ostream& operator<<(ostream& os, map<A, B>& mp) { for (auto i : mp) os << i << ", "; return os; }
// template <typename A, typename B> ostream& operator<<(ostream& os, const pair<A, B>& i) { return os << '{' << i.ff << ", " << i.ss << '}'; }
void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#define debug(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

using ll = long long; using ld = long double; using ull = unsigned ll;
using pii = pair<int, int>; using pli = pair<ll, int>; using pil = pair<int, ll>;
using pll = pair<ll, ll>; using vl = vector<ll>; using vvl = vector<vl>;
using vi = vector<int>; using vb = vector<bool>; using vc = vector<char>;
using vvi = vector<vi>; using vvb = vector<vb>; using vvc = vector<vc>;
using vpii = vector<pii>; using vpll = vector<pll>; using vs = vector<string>;
using vvpii = vector<vpii>; using vvvi = vector<vvi>; using vvvl = vector<vvl>;
using vull = vector<ull>;
using tiii = tuple<int, int, int>; ; using vtiii = vector<tiii>;
template <class A, class B> using umap = unordered_map<A, B>;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define bug cerr << "!Bugged..." << endl
#define add(x, y) (x + y >= MOD ? x + y - MOD : x + y)
#define mul(x, y) (((x % MOD) * (y % MOD)) % MOD)
#define sz(x) (int)(x).size()

const string cq[2] = { "NO", "YES" };
const int dx[8] = { -1,  0, 0, 1, 1,  1, -1, -1 };
const int dy[8] = { 0, -1, 1, 0, 1, -1,  1, -1 };
const int INF = 2147483647;
const ll LINF = 9223372036854775807;
const int MOD = 1e9 + 7;
const int N = 8e3 + 1;

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct dsu {
    int n;
    vi dsu_sz, par, mx, mn;
    dsu(int _n) : n(_n), dsu_sz(n, 1), par(n, -1), mx(n, -1), mn(n, INF) {}
    int find(int x) { return (par[x] == -1 ? x : par[x] = find(par[x])); }
    int unite(int a, int b) {
        int oa = a, ob = b;
        a = find(a), b = find(b);
        if (a != b) {
            if (dsu_sz[a] < dsu_sz[b]) swap(a, b);
            par[b] = a;
            mx[a] = max({ mx[a], ob, oa, mx[b] });
            mn[a] = min({ mn[a], ob, oa, mn[b] });
            dsu_sz[a] += dsu_sz[b];
            return 1;
        }
        return 0;
    }
};

int main()
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
        vector<pair<pair<int, int>, pair<int, int>>> vp;
        for (int i = 0; i < n; i++) {
            int x, y; cin >> x >> y;
            vp.pb({ {y - x, i + 1}, {x, y} });
        }
        sort(all(vp));
        vi ans;
        dsu ds(4 * n);
        while (vp.size()) {
            auto& [p1, p2] = vp.back();
            auto& [diff, idx] = p1;
            auto& [x, y] = p2;
            if (ds.find(x) != ds.find(y)) {
                ds.unite(x, y);
                ans.pb(idx);
            }
            vp.pop_back();
        }
        cout << ans.size() << endl;
        for (auto& i : ans) cout << i << " ";
        cout << endl;
    }
    return 0;
}